#define inix	5
#define iniy	2
#define drawx	1
#define drawy	1

void draw(const int* d){
	int i,j;
	gotoxy(0,0);
	for (i=1;i<=16+drawy;i++){
		for (j=1;j<=16+drawx;j++){
			if ( 0 == *( d+j*64+i )) printf("  ");
			if ( 1 == *( d+j*64+i )) printf("¡õ");
			if ( 2 == *( d+j*64+i )) printf("@@");
			if ( 3 == *( d+j*64+i )) printf("¡ö");
			if ( 4 == *( d+j*64+i )) printf("__");
			if ( 5 == *( d+j*64+i )) printf("~~");
			if ( 6 == *( d+j*64+i )) printf(" |");
			if ( 7 == *( d+j*64+i )) printf("| ");
		}
		putchar('\n');
	}
}

void hlt() {
	gotoxy(8+drawx,8+drawy);
	while ((kbhit()==0)){
		
	}
}


