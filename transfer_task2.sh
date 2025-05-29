#!/bin/bash
# Перенос файлов task2 на суперкомпьютер используя rsync
rsync -av --progress /Users/annaalikina/Downloads/laba2_sk/task2/sequential_2.c alikinaan8.yandex.ru:~/task2/
rsync -av --progress /Users/annaalikina/Downloads/laba2_sk/task2/parallel_2.c alikinaan8.yandex.ru:~/task2/ 