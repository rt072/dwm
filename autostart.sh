#!/bin/bash 
/home/rt072/.scripts/chwall &


if ! pgrep 'pulseaudio'; then 
pulseaudio --daemonize &
fi

if ! pgrep 'compton'; then 
compton --config ~/.config/compton/compton.conf &
fi

if ! pgrep 'pasystray'; then 
pasystray &
fi

dte(){
  dte="$(date +"%a, %d %B |  %k:%M%p")"
  echo -e " $dte        "
}

#upd(){
#  upd=`checkupdates | wc -l`
#  echo -e "⟳  $upd updates"
#}

freeroot(){
  freeroot=`df -lh / | grep cryptroot | awk '{print $4}'`
  echo -e " $freeroot"
}

mem(){
  mem=`free | awk '/Mem/ {printf "%d MiB\n", $3 / 1024.0}'`
  echo -e " $mem"
}

cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 1
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo -e " $cpu%"
}

bat(){
  bat=$(acpi -b | cut -d"," -f2 | cut -d" " -f2)
  echo -e " $bat"
}


while true; do
    xsetroot -name "$(cpu) | $(bat) | $(mem) | $(freeroot) | $(dte)"
     sleep 5s    # Update time every ten seconds
done &
