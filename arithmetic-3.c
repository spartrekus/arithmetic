
//////////////////////////////////////////
#include <stdio.h>
#if defined(__linux__) //linux
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__) 
#define MYOS 4  // freebsd
#define PATH_MAX 2500
#else
#define MYOS 0
#endif

int counter_right = 0;
int counter_wrong  = 0;


#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <limits.h>
//#include <time.h>
//#include <math.h>

#include <signal.h>

#define	MAX	100

char	types[10];
int	right[MAX];
int	left[MAX];
int	rights;
int	wrongs;
long	stvec;
long	etvec;
long	dtvec;



getlinex( char *s )
{
	register char	*rs;

	rs = s;

	while((*rs = getchar()) == ' ');
	while(*rs != '\n')
		if(*rs == 0)
			exit(0);
		else if(rs >= &s[99]) {
			while((*rs = getchar()) != '\n')
				if(*rs == '\0')	exit(0);
		}
		else
			*++rs = getchar();
	while(*--rs == ' ')
		*rs = '\n';
}


getnum(char *s)
{
	int	a;
	char	c;

	a = 0;
	while((c = *s++) >= '0' && c <= '9') {
		a = a*10 + c - '0';
	}
	return(a);
}


randomnik(range)
{
	return(rand()%range);
}

skrand(range){
int temp;
	temp = randomnik(range) + randomnik(range);
	if(temp > range - 1) temp = 2*range - 1 - temp;
	return(temp);
	}




int score()
{
	time(&etvec);

	printf("\n\nRights %d; Wrongs %d; Score %d%%\n", rights, wrongs,
		(rights * 100)/(rights + wrongs));

	if(rights == 0)	return 0;
	printf("Total time %ld seconds; %.1f seconds per problem\n\n\n",
		etvec - stvec,
		(etvec - stvec) / (rights + 0.));

	sleep(3);
	time(&dtvec);
	stvec += dtvec - etvec;
}

int delete()
{
	if(rights + wrongs == 0.) {
		printf("\n");
		exit(0);
	}
	score();
	exit(0);
}


int main(argc,argv)
char	*argv[];
{
	int range, k, dif, l;
	char line[100];
	int ans,pans,i,j,t;
	extern	delete();

	signal(SIGINT, delete);

	range = 11;
	dif = 0;
	while(argc > 1) {
		switch(*argv[1]) {
		case '+':
		case '-':
		case 'x':
		case '/':
			while(types[dif] = argv[1][dif])
				dif++;
			break;

		default:
			range = getnum(argv[1]) + 1;
		}
		argv++;
		argc--;
	}
	if(range > MAX) {
		printf("Range is too large.\n");
		exit(0);
	}

	if(dif == 0) {
		types[0] = '+';
		types[1] = '-';
		dif = 2;
	}

	for(i = 0; i < range; i++) {
		left[i] = right[i] = i;
	}
	time(&stvec);
	k = stvec;
	srand(k);
	k = 0;
	l = 0;
	goto start;

loop:
	if(++k%20 == 0)
		score();

start:
	i = skrand(range);
	j = skrand(range);
	if(dif > 1)
		l = randomnik(dif);


	switch(types[l]) {
		case '+':
		default:
			ans = left[i] + right[j];
			printf("%d + %d =   ", left[i], right[j]);
			break;

		case '-':
			t = left[i] + right[j];
			ans = left[i];
			printf("%d - %d =   ", t, right[j]);
			break;

		case 'x':
			ans = left[i] * right[j];
			printf("%d x %d =   ", left[i], right[j]);
			break;

		case '/':
			while(right[j] == 0)
				j = randomnik(range);
			t = left[i] * right[j] + randomnik(right[j]);
			ans = left[i];
			printf("%d / %d =   ", t, right[j]);
			break;
	}



loop1:
	getlinex(line);
	dtvec += etvec - stvec;
	if(line[0]=='\n') goto loop1;
	pans = getnum(line);
	if(pans == ans) {
		printf("Right!\n");
		rights++;
                counter_right++;
                printf( "|Your Results now: [Right=%d] [Wrong=%d]|\n", counter_right, counter_wrong );
                printf( "\n" );
		goto loop;
	}
	else {
		printf("What?\n");
		wrongs++;
                counter_wrong++;
		if(range >= MAX)	goto loop1;
		left[range] = left[i];
		right[range++] = right[j];
                printf( "|Your Results now: [Right=%d] [Wrong=%d]|\n", counter_right, counter_wrong );
                printf( "\n" );
		goto loop1;
	}

}





