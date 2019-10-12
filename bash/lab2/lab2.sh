#! /bin/bash
while true
do
CHOOSED=$(kdialog --menu "Выберите действие:" 1 Добавить 2 Будильник 3 Удалить 4 Выход); 
if [ $? -eq 1 ]
then
	break;
fi
case $CHOOSED in
1)
TIME=$(kdialog --title "Будильники" --inputbox "Введите время");
if [ $? -eq 0 ]
then
	m=$(echo $TIME | cut -d':' -f2);
	h=$(echo $TIME | cut -d':' -f1);
	RESULT="Выберите музыку.\n";
	MUSIC=$(kdialog --getopenfilename /usr/share/sounds/ '*.ogg');
	if [ $? -eq 0 ]
	then
		RESULT="Выберите дни.\n";
		DATE=$(kdialog --inputbox "Введите дни недели");
		if [ $? -eq 0 ]
		then
			if [ $? -eq 0 ]
			then
				crontab -l > temp;
				echo -e "$m $h * * $DATE  clementine $MUSIC" >> temp;
				crontab temp;
				rm temp;
				kdialog --msgbox "Будильник был добавлен.";
			else
				kdialog --error "Будильник не был добавлен.";
			fi
		else
			kdialog --error "Будильник не был добавлен.";
		fi
	else
		kdialog --error "Будильник не был добавлен.";
	fi
else
	kdialog --error "Будильник не был добавлен.";
fi
;;
2)
echo "ЧЧ:ММ    ДД" > temp;
i=2;
count=$(crontab -l | wc -l);
let "count=count+1";
while [ "$i" -ne "$count" ]
do
	m=$(crontab -l | head -n"$i" | tail -n1 | cut -d' ' -f1);
	h=$(crontab -l | head -n"$i" | tail -n1 | cut -d' ' -f2);
	d=$(crontab -l | head -n"$i" | tail -n1 | cut -d' ' -f5);
	echo -e "$h:$m         $d" >> temp;
	let "i=i+1";
done
kdialog --textbox temp;
rm temp;
;;
3)
NUMBER=$(kdialog --inputbox "Введите номер будильника для удаления");
count=$(crontab -l | wc -l);
if [ $? -eq 0 ]
then
	if [ "$NUMBER" -lt "$count" ]
	then
		let "NUMBER=NUMBER+1";
		crontab -l > temp;
		sed "$NUMBER"d temp > newcron;
		crontab -r;
		crontab newcron;
		rm temp;
		rm newcron;
		kdialog --msgbox "Будильник удален успешно."
	else
		kdialog --error "Будильник не удален."
	fi
else
	kdialog --error "Будильник не удален"
fi
;;
4)
break;
;;
esac
done
