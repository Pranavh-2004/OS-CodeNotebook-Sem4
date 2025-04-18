// Write a C program to truncate files in a directory created after a certain date to half its original size.
// Inputs to the program directory and date as runtime arguments
// Example: a.out /home/Ubuntu 31-Mar-2025

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    DIR *directory;
    struct dirent *dir_entry;
    struct stat file_info;
    char file_path[1024];
    time_t cutoff_time;
    struct tm date_components;

    if (argc != 3)
    {
        printf("Usage: %s <directory> <date(DD-MMM-YYYY)>\n", argv[0]);
        return 1;
    }

    memset(&date_components, 0, sizeof(struct tm));

    if (strptime(argv[2], "%d-%b-%Y", &date_components) == NULL)
    {
        printf("Error: Date must be in DD-MMM-YYYY format (e.g., 31-Mar-2025)\n");
        return 1;
    }

    cutoff_time = mktime(&date_components);
    if (cutoff_time == -1)
    {
        printf("Error: Invalid date\n");
        return 1;
    }

    directory = opendir(argv[1]);
    if (directory == NULL)
    {
        printf("Error: Cannot open directory '%s'\n", argv[1]);
        return 1;
    }

    while ((dir_entry = readdir(directory)) != NULL)
    {
        if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(file_path, sizeof(file_path), "%s/%s", argv[1], dir_entry->d_name);

        if (stat(file_path, &file_info) == -1)
        {
            printf("Error: Cannot get information for file '%s'\n", file_path);
            continue;
        }

        if (S_ISREG(file_info.st_mode) && file_info.st_mtime > cutoff_time)
        {
            long original_size = file_info.st_size;
            long new_size = original_size / 2;

            printf("Processing: %s (modified after cutoff date)\n", dir_entry->d_name);

            if (truncate(file_path, new_size) != 0)
            {
                printf("Error: Failed to truncate file '%s'\n", file_path);
            }
            else
            {
                printf("Success: Truncated '%s' from %ld to %ld bytes\n",
                       dir_entry->d_name, original_size, new_size);
            }
        }
    }

    closedir(directory);
    printf("Finished processing all files.\n");

    return 0;
}