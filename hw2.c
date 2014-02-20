
#include <stdio.h>
#include <stdlib.h>
#include "Timers.h"

int main(int argc, char *argv[]){

	DECLARE_TIMER(NewTimer);

	START_TIMER(NewTimer);
	int count1;
	int count2;
	int a;
	int b;
	for(count1=0;count1<10000;count1++){
		a+=count1;
		for(count2=0;count2<100000;count2++){
			b=b*a;
		}

	}
	printf("A: %d\n", a);

	STOP_TIMER(NewTimer);

	PRINT_TIMER(NewTimer);

	RESET_TIMER(NewTimer);
}
