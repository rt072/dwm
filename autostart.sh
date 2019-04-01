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

xkb(){
  xkb=`xkblayout`
  echo -e " $xkb        "
}

dte(){
  dte="$(date +"%a, %d %B |  %k:%M%p")"
  echo -e " $dte"
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

#!/bin/bash

getBattery() {
    perc=$(acpi -b | awk '/Battery/ {print $4}' | cut -d% -f1)
    time=$(acpi -b | awk '/Battery/ {print " (" substr($5,1,5)")"}')
    is_charging=$(acpi -a | awk '/Adapter/ {print $3}')

    if [ "${is_charging}" == "on-line" ]; then
      bat_icons=("" "" "" "" "" "")
    else
      bat_icons=("" "" "" "" "")
    fi

    if [ ${perc} -lt "20" ]; then
        echo -ne "${bat_icons[4]} ${perc}% ${time}"
    elif [ ${perc} -lt "35" ]; then
        echo -ne "${bat_icons[3]} ${perc}%"
    elif [ ${perc} -lt "75" ]; then
        echo -ne "${bat_icons[2]} ${perc}%"
    elif [ ${perc} -lt "90" ]; then
        echo -ne "${bat_icons[1]} ${perc}%"
    elif [ ${perc} -lt "100" ]; then
        echo -ne "${bat_icons[0]} ${perc}%"
    elif [ ${perc} -eq "100" ]; then
        echo -ne "${bat_icons[0]} ${perc}%"
    fi
}

getSound() {
    volume=$(pactl list sinks | grep 'Громкость:' | awk '{print $5}')
    is_muted=$(amixer get Master | awk '/%/ {gsub(/[\[\]]/,""); print $6}' | tail -1)
    cur_device=$(pactl list sinks | awk '/Активный порт:/ {print substr($3,15)}' | grep -v "^$")
    if [ ${cur_device} == "headphones" ]; then
        out_device=(" " " ")
    else
        out_device=(" " " ")
    fi

    if [ ${is_muted} == "on" ]; then
        echo -ne "${out_device[0]}${volume}"
    else
        echo -ne "${out_device[1]}${volume}"
    fi
}

while true; do
    xsetroot -name "$(cpu) | $(getSound) | $(getBattery) | $(mem) | $(freeroot) | $(dte) | $(xkb)"
     sleep 5s    # Update time every ten seconds
done &
