#!/bin/bash

# ежедневная очистка журнала логов 

cur_day=$(date +"%d") # получение сегодняшнего дня

file_log="../../my_prog.log" # путь к журналу с логами

log_last_day=$(tail -n 1 "${file_log}" | grep -oP '\d{4}-\d{2}-\d{2}' | awk -F'-' '{print $3}') # получаем из журнала день 
                                                                                                # последнего обновления

#echo "log_last_day = ${log_last_day}"

if ((cur_day != log_last_day)); # если дни не совпадают -> журнал чиститься
then 
    echo > ${file_log}
fi