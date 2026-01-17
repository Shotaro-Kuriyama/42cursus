#!/bin/bash

# Architecture
arch=$(uname -a)

# Physical CPU
cpuf=$(grep "physical id" /proc/cpuinfo | uniq | wc -l)

# Virtual CPU
cpuv=$(nproc)

# MEMORY USAGE
ram_total=$(free -m | grep Mem | awk '{print $2}')
ram_use=$(free -m | grep Mem | awk '{print $3}')
ram_percent=$(free -m | grep Mem | awk '{print $3/$2 * 100}')

#DISK USAGE
disk_total=$(df -h / | tail -n 1 | awk '{print $2}')
disk_use=$(df -h / | tail -n 1 | awk '{print $3}')
disk_percent=$(df -h / | tail -n 1 | awk '{print $5}')

#CPU LOAD
cpu_load=$(vmstat 1 4 | tail -1 | awk '{print $13 + $14}')

#LAST BOOT
last_boot=$(uptime -s | cut -c 1-16)

#LVM USE
lvm_active=$(lsblk -o TYPE | grep -q lvm && echo "yes" || echo "no")

#TCP
tcp_estab=$(ss -H -tn state established | wc -l)

#User login
usr_cnt=$(who | wc -l)

#Network IP(MAC)
ip_a=$(hostname -I)
mac_a=$(ip a | grep 'link/ether' | awk '{print $2}')

#SUDO
sudo_cnt=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

message="
#Architecture: $arch
#CPU physical: $cpuf
#vCPU: $cpuv
#Memory Usage: $ram_use/${ram_total}MB ($ram_percent%)
#Disk Usage: $disk_use/${disk_total} ($disk_percent%)
#CPU load: $cpu_load%
#Last boot: $last_boot
#LVM use: $lvm_active
#Connections TCP: $tcp_estab ESTABLISHED
#User log: $usr_cnt
#Network: IP $ip_a ($mac_a)
#Sudo: $sudo_cnt cmd
"

echo "$message" > /etc/motd
wall /etc/motd
