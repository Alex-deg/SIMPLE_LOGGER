#!/bin/bash

cur_day=$(date +"%d")

file_log="../../my_prog.log"

log_last_day=$(tail -n 1 "${file_log}" | grep -oP '\d{4}-\d{2}-\d{2}' | awk -F'-' '{print $3}')

echo "log_last_day = ${log_last_day}"

if ((cur_day != log_last_day));
then 
    echo > ${file_log}
fi