#! /bin/bash
CHOOSED=$(kdialog --menu "Выберите действие:" 1 Добавить 2 Будильник 3 Удалить 4 Изменить)
 

case $CHOOSED in
1)
TIME=$(kdialog --title "Будильники" --inputbox "Введите время")
if [ $? -eq 0 ]
then
	m=$(echo $TIME | cut -d':' -f2)
	h=$(echo $TIME | cut -d':' -f1)
	RESULT+="Выберите дни.\n"
	DATE=$(kdialog --inputbox "Введите дни недели")
	if [ $? -eq 0 ]
	then
		echo "DISPLAY=:0 
		$m $h * * $DATE  clementine /home/gleb/Linux/bash/lab2/04_Rocket\ Man.wav" |crontab -
		RESULT="Будильник был добавлен.\n"
	else
		RESULT="Будильник не был добавлен.\n"
	fi
else
	RESULT+="Будильник не был добавлен.\n"
fi
;;
2)
if [ $? -eq 0 ]
then
RESULT+="Бэкап прошел успешно.\n"
else
RESULT+="Бэкап не удался.\n"
fi
;;
3)
if [ $? -eq 0 ]
then
RESULT+="Бэкап прошел успешно.\n"
else
RESULT+="Бэкап не удался.\n"
fi
;;
4)
if [ $? -eq 0 ]
then
RESULT+="Бэкап прошел успешно.\n"
else
RESULT+="Бэкап не удался.\n"
fi
;;
esac
kdialog --msgbox "$RESULT"
