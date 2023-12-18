#!/bin/bash
k=0
for((i=0;i<10;i++)); do
echo "Running"
sleep 1;
echo "Ending"
k=$((k+1))
done
echo "$k" > 1.txt
