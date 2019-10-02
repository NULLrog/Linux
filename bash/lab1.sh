#!/bin/bash
# Название директорий и маска имени вводится через read,
# а i - кол-во папок, j - кол-во папок в папках,
# k - кол-во файлов в тех самых папках задаются как параметры
echo "Введите наименование стартовой директории: ";
read dir;
echo "Ввудите маску имени: ";
read mask;
i=$1;
while [ "$i" -gt 0 ]
do
	j=$2;
	mkdir "$dir/$mask""$i";
	cd "$dir/$mask""$i";
	while [ "$j" -gt 0 ]
	do
		mkdir "$mask""$j";
		cd "$mask""$j";
		k=$3;
		while [ "$k" -gt 0 ]
		do
			touch "$mask""$k";
			let "k=k-1";
		done
		cd ..;
		let "j=j-1";
	done
	cd ..;
	let "i=i-1";
done

