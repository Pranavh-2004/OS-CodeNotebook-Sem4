#!/opt/homebrew/bin/bash

for i in {1..5}
do
    if [ $i -eq 3 ]; then
        break
    fi

    for j in {1..3}
    do
        echo "i = $i" and "j = $j"
    done
done