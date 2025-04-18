#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

volatile sig_atomic_t running = 1;

void handle_signal(int sig)
{
    running = 0;
}

void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("| ");
    }
}

void print_process_info(pid_t pid, int depth)
{
    char stat_path[256];
    char cmdline_path[256];
    char status_path[256];
    FILE *fp;
    char buffer[1024];
    char name[256] = "<unknown>";
    pid_t ppid = 0;
    unsigned long vm_size = 0;
    unsigned long stack_size = 0;

    // Read process name and parent PID
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
    fp = fopen(stat_path, "r");
    if (!fp)
    {
        printf("Process %d no longer exists\n", pid);
        return;
    }

    if (fscanf(fp, "%*d (%[^)]) %*c %d", name, &ppid) != 2)
    {
        fclose(fp);
        return;
    }
    fclose(fp);

    // Read memory info
    snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);
    fp = fopen(status_path, "r");
    if (fp)
    {
        while (fgets(buffer, sizeof(buffer), fp))
        {
            if (strncmp(buffer, "VmSize:", 7) == 0)
            {
                sscanf(buffer, "VmSize: %lu", &vm_size);
            }
            if (strncmp(buffer, "VmStk:", 6) == 0)
            {
                sscanf(buffer, "VmStk: %lu", &stack_size);
            }
        }
        fclose(fp);
    }

    // Print process info with tree structure
    print_indent(depth);
    printf("├─ Process: %s[%d] (Parent: %d)\n", name, pid, ppid);
    print_indent(depth);
    printf("   ├─ Virtual Memory: %lu KB\n", vm_size);
    print_indent(depth);
    printf("   └─ Stack Size: %lu KB\n", stack_size);

    // Find and print children
    DIR *dir = opendir("/proc");
    if (!dir)
    {
        perror("Failed to open /proc");
        return;
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) && running)
    {
        if (ent->d_type == DT_DIR)
        {
            pid_t cpid = atoi(ent->d_name);
            if (cpid > 0)
            {
                char cstat_path[256];
                snprintf(cstat_path, sizeof(cstat_path), "/proc/%d/stat", cpid);
                fp = fopen(cstat_path, "r");
                if (fp)
                {
                    int parent;
                    if (fscanf(fp, "%*d %*s %*c %d", &parent) == 1 && parent == pid)
                    {
                        print_process_info(cpid, depth + 1);
                    }
                    fclose(fp);
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <target_pid>\n", argv[0]);
        return 1;
    }

    pid_t target_pid = atoi(argv[1]);
    if (target_pid <= 0)
    {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        return 1;
    }

    // Set up signal handling
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("Monitoring process tree for PID %d. Press Ctrl+C to stop.\n", target_pid);

    while (running)
    {
        printf("\n=== Process Tree and Memory Info (Parent PID: %d) ===\n", target_pid);
        print_process_info(target_pid, 0);
        sleep(1);
        printf("\033[2J\033[H"); // Clear screen and move cursor to top
    }

    printf("\nMonitoring stopped.\n");
    return 0;
}