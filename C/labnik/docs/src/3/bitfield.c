#include <stdio.h>
#define YEAR0 2016
struct date
{
	unsigned short day   :5;//0-31 
	unsigned short month :4;//0-15  
	unsigned short year  :7;//0-127
};
int main( int argc, char* argv[] ) {
  struct date today;
  today.day = 2;
  today.month = 2;
  today.year = 2017 - YEAR0;
  
  printf("Сегодня %u.%u.%u \n", today.day, today.month, today.year+YEAR0);
  printf("Размер структуры today: %d байт\n", sizeof(today));
  printf("Значение элемента today = %hu = %hx шестн.", today, today);
 
  return 0;
}








