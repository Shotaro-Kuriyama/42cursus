monitoring.sh


#!/bin/bash

# 1) ARCH
arch=$(uname -a)

# 2) CPU PHYSICAL (unique physical id)
cpuf=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)

# 3) CPU VIRTUAL (vCPU)
cpuv=$(grep "processor" /proc/cpuinfo | wc -l)

# 4) RAM
ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

# 5) DISK
disk_total=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_t += $2} END {printf ("%.1fGb"), disk_t/1024}')
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} END {print disk_u}')
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" \
  | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')

# 6) CPU LOAD
cpul=$(vmstat 1 2 | tail -1 | awk '{printf $15}')
cpu_op=$(expr 100 - $cpul)
cpu_fin=$(printf "%.1f" $cpu_op)

# 7) LAST BOOT
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')

# 8) LVM USE
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)

# 9) TCP CONNEXIONS
tcpc=$(ss -ta | grep ESTAB | wc -l)

# 10) USER LOG
ulog=$(users | wc -w)

# 11) NETWORK
ip=$(hostname -I | awk '{print $1}')
mac=$(ip link show | awk '/link\/ether/ {print $2; exit}')

# 12) SUDO
cmnd=$(journalctl _COMM=sudo 2>/dev/null | grep COMMAND | wc -l)

wall "	Architecture: $arch
	CPU physical: $cpuf
	vCPU: $cpuv
	Memory Usage: $ram_use/${ram_total}MB ($ram_percent%)
	Disk Usage: $disk_use/${disk_total} ($disk_percent%)
	CPU load: $cpu_fin%
	Last boot: $lb
	LVM use: $lvmu
	Connections TCP: $tcpc ESTABLISHED
	User log: $ulog
	Network: IP $ip ($mac)
	Sudo: $cmnd cmd"


/etc/pam.d/common-password

# --- for non-root users (apply difok=7) ---
password	[success=1 default=ignore]	pam_succeed_if.so user = root
password	requisite	pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7 

# --- for root (same rules but WITHOUT difok=7) ---
password	[success=1 default=ignore]	pam_succeed_if.so user != root
password	requisite	pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 reject_username enforce_for_root


/etc/sudoers.d/sudo_config


Defaults passwd_tries=3
Defaults badpass_message="Wrong password. Try again."
Defaults  logfile="/var/log/sudo/sudo_config"
Defaults  log_input, log_output
Defaults  iolog_dir="/var/log/sudo"
Defaults  requiretty
Defaults  secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

sudo -crontab -e

@reboot /usr/local/bin/monitoring.sh
*/10 * * * * sh /usr/local/bin/monitoring.sh








