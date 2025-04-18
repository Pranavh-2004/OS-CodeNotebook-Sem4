FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    linux-headers-generic \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /workspace

# Copy all files
COPY . /workspace

# Build the kernel module and parent process
RUN make && gcc -o parent_process parent_process.c

# Default command
CMD ["/bin/bash"]