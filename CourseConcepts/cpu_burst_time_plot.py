import time
import psutil
import subprocess
import matplotlib.pyplot as plt

# Function to start a CPU-intensive process
def start_process():
    return subprocess.Popen(["python3", "-c", "while True: pass"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

# Function to monitor CPU usage over time
def monitor_cpu_usage(pid, duration=5, interval=0.1):
    process = psutil.Process(pid)
    cpu_usage = []
    timestamps = []
    start_time = time.time()

    while time.time() - start_time < duration:
        cpu_usage.append(process.cpu_percent(interval=interval))  # Get CPU usage
        timestamps.append(time.time() - start_time)

    process.terminate()  # Stop the process
    return timestamps, cpu_usage

# Main function
if __name__ == "__main__":
    process = start_process()  # Start the process
    time.sleep(1)  # Let it stabilize

    timestamps, cpu_usage = monitor_cpu_usage(process.pid)

    # Plot the CPU burst time
    plt.figure(figsize=(8, 5))
    plt.plot(timestamps, cpu_usage, marker="o", linestyle="-", color="b")
    plt.xlabel("Time (seconds)")
    plt.ylabel("CPU Usage (%)")
    plt.title("CPU Burst Time of Process")
    plt.grid(True)
    plt.show()