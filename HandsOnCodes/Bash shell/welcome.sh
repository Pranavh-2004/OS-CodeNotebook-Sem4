#!/opt/homebrew/bin/bash

if [ -f welcome.txt ]; then
    echo "welcome.txt exists"
else
    echo "welcome.txt does not exists"
fi

if [ -f welcome.sh ]; then
    echo "welcome.sh exists"
else
    echo "welcome.sh does not exists"
fi