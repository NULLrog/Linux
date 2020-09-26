#include <stdio.h>
char *months[] = {
        "Неверный месяц",
        "Январь","Февраль","Март","Апрель","Май","Июнь", 
        "Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"
};

char *months_en[] = {
	"Invalid month",
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};         
/* month_name: возвращает имя n-го месяца */
char *month_name(char *name[], int n){
    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(int argc, char **argv){
	printf("Введите номер месяца:");
	int n = 0;
	scanf("%d", &n);
	printf("Месяц:%s\n", month_name(months, n));
	printf("Month:%s\n", month_name(months_en, n));
}

