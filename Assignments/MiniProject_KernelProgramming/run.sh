#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Change to the script directory
cd "$SCRIPT_DIR"

function setup_containers() {
    echo "Setting up containers..."
    docker-compose down || true
    docker-compose build
    docker-compose up -d
    sleep 2
}

function show_help() {
    echo "Usage: $0 [command]"
    echo "Commands:"
    echo "  setup    - Build and start containers"
    echo "  monitor  - Run process monitor"
    echo "  parent   - Run parent process"
    echo "  clean    - Stop and remove containers"
    echo "  help     - Show this help message"
}

case "$1" in
    "setup")
        setup_containers
        ;;
    "monitor")
        echo "Starting process monitor..."
        # Wait for parent process to start and get its PID
        echo "Waiting for parent process..."
        PARENT_PID=""
        while [ -z "$PARENT_PID" ]; do
            # Look specifically for the parent_process executable
            PARENT_PID=$(docker exec parent_process ps -ef | grep "[p]arent_process" | awk '{print $2}' || echo "")
            if [ -z "$PARENT_PID" ]; then
                echo "Waiting for parent process to start..."
                sleep 1
            fi
        done
        echo "Found parent process with PID: $PARENT_PID"
        docker exec parent_process ./process_monitor "$PARENT_PID"
        ;;
    "parent")
        echo "Running parent process..."
        docker exec -it parent_process ./parent_process
        ;;
    "clean")
        echo "Cleaning up containers..."
        docker-compose down
        ;;
    "help"|"")
        show_help
        ;;
    *)
        echo "Unknown command: $1"
        show_help
        exit 1
        ;;
esac 