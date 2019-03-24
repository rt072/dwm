#!/bin/bash 
compton --config ~/.config/compton/compton.conf &
#nitrogen --restore &
#pasystray &
#urxvtd -q -o -f &
/home/rt072/.scripts/chwall &

dte(){
  dte="$(date +"%A, %d %B |  %l:%M%p")"
  echo -e " $dte"
}

#upd(){
#  upd=`checkupdates | wc -l`
#  echo -e "⟳  $upd updates"
#}

mem(){
  mem=`free | awk '/Mem/ {printf "%d MiB\n", $3 / 1024.0}'`
  echo -e " $mem"
}

cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 1
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo -e " $cpu% cpu"
}

bat(){
  bat=$(acpi -b | cut -d"," -f2 | cut -d" " -f2)
  echo -e " $bat"
}


while true; do
    xsetroot -name "$(cpu) | $(bat) | $(mem) | $(dte)      "
     sleep 5s    # Update time every ten seconds
done &
