1. Find the PID, Priority, Nice value (NI), etc
   when a process is running, use the following command to visualize the above details after finding corresponding PID with get_pid:

```bash
ps -l <PID>
```

2. To find vruntime:

```bash
top
```

3. To display content of file in terminal:

```bash
ps -l | more
```

4. To get more details:

```bash
ps -l | less
```
