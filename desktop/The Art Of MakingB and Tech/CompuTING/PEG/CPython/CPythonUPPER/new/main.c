/*************************************/
/*       CPythonDATAii Build         */
/*   user system && point recorder   */
/*  this code is from eczn@OSB       */
/*    any ways,any time you could    */
/*   make use of this code without   */
/*      OSB's any permissions        */
/*    compilered in DEVCPP 5.9.2     */
/*                                   */
/*************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/* #include <CPython.h> */
#define inix	5
#define iniy	2
#define drawx	1
#define drawy	1
#define extra_speed 75

unsigned long point = 0;
int  d[64][64] = { 0 };			/* map_buffer */
int  LEN = 2;					/* �߳��ȡ� lenth */
char vector  = 'd';				//vector  ָ���������ߵ����ƻ���
char control = 'd';				//control ָ���ǲ����ߵĿ���ָ��
char b[25] = {'\0'};

/* �û�ϵͳ */
FILE *fp_in_main = NULL;
char user_exist = 0;
char user_name[8] = {'\0'};
int point_paper[8][8] = { 0 };
int bushu = 0;

struct history_point {
	int point;
	char user[8];
	char game_mode;				/* 0 ������ͨģʽ  1 ����extraģʽ */
};

/* ���Ʊ��� */
int j,k;
int i,o;

int  _time = 300;				/* ��ͨ�Ѷ��µ� _sleepʱ�� ���ٶȣ�  */
int  all_time = 0;				/* ��Ϸ����ʱ�� */
int  deathmark = 0;				/****   ���� ~ deathmark ~ ���   ****/

/* ��ӭ����Ŀ��Ʒ� */

char foodcreate_flag = 0;		/* ʳ������_��־ */
int win = 0;					/* װ��ʤ����־ */
int extra_button = 0;			/*  extra����   */

int eat( int jk , char contro );					/* ����control����ͷ���ݱ� */
void gotoxy(int x,int y); 							/* �ƶ���굽 x��y ��һ����Ϊ 0��0   windows.h */

void cprint(const char *sen,int hang,int xh);		/* �ڵ� hang+iniy �д�ӡ�ַ��� sen �� xh��־�Ƿ��ӡ �ڼ��� */

void inid();
void hlt();


/****  �浵  ****/
char map_save[255*2] = {'\0'};

int num = 1;
struct node {                   //��������
	int x;
	int y;
	int number;
	struct node *up;
	struct node *down;
};

struct Food {                   
	int x;
	int y;
	int type;
};

/* run this program using the console pauser or add your own getch,
 *				system("pause") or input loop 
 */
int main(int argc, char *argv[])  {                //����ʲô�ġ�
	struct node *head;
	struct node *temA;
	struct node *temB;
	struct node *temAA;
	struct Food food = {6,6};
    char control_temp;
    int temp = 77;

	system("title CPythonUPPERi ");//���ñ���
//	system("mode con cols=63 lines=32");//���ô��ڴ�С
	system("color 70");//������ɫ

	srand((unsigned)time(NULL));
	head = (struct node *) malloc( sizeof(struct node) );
	temA = (struct node *) malloc( sizeof(struct node) );
	temB = (struct node *) malloc( sizeof(struct node) );
	temAA= (struct node *) malloc( sizeof(struct node) );
	
    temA->up   = head;
    temA->down = NULL;
    temA->x    = 4;
    temA->y    = 8;
	head->down = temA;
	head->up   = NULL;
	head->x    = 5;
	head->y    = 8;

	num = 1;
	head->number = num;
	head->down->number = ++num;
	
	fp_in_main = fopen("CPythonSAVE","r");
	fread(&user_exist,1,1,fp_in_main);
	fread(user_name,8,1,fp_in_main);
	fread(point_paper,4,64,fp_in_main);
	fclose(fp_in_main);
	if ( user_exist == 0 ){
		printf("\n\n\t impress your name:");
		scanf("%s",user_name);
		user_exist = 1;
		system("cls");
		fp_in_main = fopen("CPythonSAVE","w+");

		user_exist = 1;
		fwrite(&user_exist,1,1,fp_in_main);
		fwrite(user_name,1,8,fp_in_main);
		fwrite(point_paper,4,64,fp_in_main);
	}

	deathmark = memu(user_name,&extra_button);
	if (deathmark == -1)
		return 0;

start:
	inid();


    while ( 1 ) {           //��ѭ����
        if ( kbhit() ){
        	control_temp = control;
            control = getch();
            if ( control != 'a' && control != 's' && control != 'd' && control != 'w' && control != 'w' ){
            	control = getch();
				control = control_temp;
			}
        }
		if (control == 'p'){
			hlt();
			continue;
		}

        temA = head;                //ָ�붨λ������β��
        while ( temA->down != NULL )
            temA = temA->down;
        temAA = temA;
        while ( temA->up   != NULL ){  //������������ǰһ���ڵ��ƶ�
            j = temA->x;
            k = temA->y;
            temA->x = (temA->up)->x;
            temA->y = (temA->up)->y;
            temA = temA->up;
		}
        if (foodcreate_flag == 1){
            temB->x = j;
            temB->y = k;
            temAA ->down = temB;
            foodcreate_flag = 0;
s:
            food.x = rand()%16;
            food.y = rand()%16;

            temA = head->down;
	        while (temA->down != NULL){
            if ((food.x == temA->x)&&(food.y == temA->y))
				goto s;
    	        temA = temA->down;
            }
        	if ((food.x == temA->x)&&(food.y == temA->y))
            	goto s;

            if ( (food.x == 0) || (food.y == 0) )
                goto s;
            
            point = point + (300-_time);
        }
                                      //��ֹ�������˶�
        if ((control-vector==3)||(control-vector==-3))
            control = vector;

        if ((control-vector==4)||(control-vector==-4))
            control = vector;

                                    //head����
        if (control == 'a' || control == 'd')
            head->x = eat(head->x,control);
        if (control == 's' || control == 'w')
            head->y = eat(head->y,control);

        if ((food.x == head->x) && (food.y == head->y)){
        	
            temB = (struct node *) malloc( sizeof(struct node) );
            temA = head;                //ָ�붨λ������β��
            while ( temA->down != NULL )
                temA = temA->down;

            	temB->x    = temA->x;
            	temB->y    = temA->y;
            	temB->up   = temA;
            	temB->down = NULL;
            	_time = _time - 10;
            	foodcreate_flag = 1;
            	LEN++;
            	temB->number = ++num;
            	gotoxy(2,20);
        }

                        //��ά�����ͼ׼��

        temA = head;
        while (temA->down != NULL){
            d[temA->x+drawx][temA->y+drawy] = 1;
            temA = temA->down;
        }
        d[temA->x+drawx][temA->y+drawy] = 1;
        d[food.x+drawx][food.y+drawy]   = 2;
        d[head->x+drawx][head->y+drawy] = 3;



        if (LEN < 14){
        	all_time = all_time + _time;
            _sleep(_time);
    	}
        if (LEN >= 14){
        	if ( extra_button == 1){
        		point = point + LEN/10;
        		all_time = all_time + _time;
        		_sleep(extra_speed);
        	} else {
        		all_time = all_time + _time;
            	_sleep(150);
        	}
    	}


        temA = head->down;
        while (temA->down != NULL){
            if ((head->x == temA->x)&&(head->y == temA->y))
                deathmark = 1;
            temA = temA->down;
            }
        if ((head->x == temA->x)&&(head->y == temA->y))
            deathmark = 1;

		draw((const int *)d);

        temA = head;
        while (temA->down != NULL){
            d[temA->x+drawx][temA->y+drawy] = 0;
            temA = temA->down;
		}
        d[temA->x+drawx][temA->y+drawy] = 0;

        vector = control;

        printf(" point: %d",point);
        printf("\n LEN: %d  ",LEN);

tail:
        if (LEN <15)
            printf("SPEED = %2d\n",LEN);
        else {
            printf("-MAXIMUM SPEED-\n");
		}
		if (extra_button == 1){
			printf("**********************************  \n");
			printf("         -������װ��֮��-           \n");
			printf("         ~ ��֮����֮�� ~           \n");
			printf("        ******************          \n");
			printf("********* EATRA  WARNING ********     ");
		}
        if (deathmark){
			if (LEN >= 15*15){
				win = 1;
			}
			system("color B0");
			Sleep(30);
			system("color 70");
            break;
		}
		bushu++;
    }
    
	point_paper_arr((int *)point_paper,point,bushu,LEN);
	point_records_save();
	win_judge(&win,&LEN);

    while (1) {
    	if (kbhit())
        	control = getch();
        if (control == 27){
        	gotoxy(5,8);
            return 0;
    	}
    	if (control == 'r'){
    		_time = 300; 
    		all_time = 0;
    		point = 0;
    		inid();
    		deathmark = 0;
    		temA = head;
    		while (temA->down != NULL){
				temAA = temA;
				temA = temA->down;
				free(temAA);
			}
			free(temA);
			control = 'd';
			vector = 'd';
			LEN = 2;

			head = (struct node *) malloc( sizeof(struct node) );
			temA = (struct node *) malloc( sizeof(struct node) );
			temB = (struct node *) malloc( sizeof(struct node) );
			temAA= (struct node *) malloc( sizeof(struct node) );

    		food.x = 6; food.y = 6;
	    	temA->up   = head;
    		temA->down = NULL;
    		temA->x    = 4;
    		temA->y    = 8;
			head->down = temA;
			head->up   = NULL;
			head->x    = 5;
			head->y    = 8;
			system("cls");
			goto start;
		}
    }


	return 0;
}

void gotoxy(int x,int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int eat( int jk , char contro ){	//����Ǵ���ͷ�� xy �ĺ����� ���Ը���
    switch ( contro ) {				//control��xy�������档
    case 'w'     :      jk-- ;
                        break;
    case 'd'     :      jk++ ;
                        break;
    case 's'     :      jk++ ;
                        break;
    case 'a'     :      jk-- ;
                        break;
    default      :      break;
	}
    if ( jk >= 16 )
          jk = jk -15;
    if ( jk <= 0 )
    		jk = jk + 15;
    return jk;
}

void inid(){
	for (i=0;i<48;i++){
		for (j=0;j<60;j++)
			d[j][i] = 0;
	}
	for (i=1;i<=15+drawy;i++){
		d[i][1] = 4;
	}
	for (i=1;i<=15+drawy;i++){
		d[i][17] = 5;
	}
	for (i=1;i<=15+drawy;i++){
		d[1][i] = 6;
	}
	for (i=1;i<=15+drawy;i++){
		d[17][i] = 7;
	}
	d[1][1] = 0;
	d[1][17] = 0;
	d[17][1] = 0;
	d[17][17] = 0;
}


int point_records_save(){
	int j,k,temp;
	int bytes = 0;
	int temp_paper[8][8] = {0};
	FILE *fp = NULL;

	fp = fopen("CPythonSAVE","r+");
	fread(&temp,1,1,fp);
	fread(user_name,1,8,fp);
	fread(temp_paper,4,64,fp);
	fclose(fp);
	
	temp = 1;
	fp = fopen("CPythonSAVE","w+");
	fwrite(&temp,1,1,fp);
	fwrite(user_name,1,8,fp);
	bytes = fwrite(point_paper,4,64,fp);
	
	fclose(fp);
	if (fp != NULL )
		return bytes;
	else 
		return bytes;
}

void output_point_records(){
	int j,k,i;
	int temp;
	FILE *fp = NULL;
	fp = fopen("CPythonSAVE","r+");
	fread(&user_exist,1,1,fp);
	fread(user_name,1,8,fp);
	fread(point_paper,4,64,fp);
	fclose(fp);
	point_records_save();
	system("cls");
	for (i=0;i<16;i++)
		printf(" ");
	printf("%s��������ɱ \n",user_name);
	printf("_________________________________________________\n");
	printf("|        NO.      point      bushu        LEN   |\n");
	for (j=0;j<7;j++){
		if ( point_paper[1][j] != 0 ){
			printf("|");
			for(k=0;k<4;k++){
				printf("%11d",point_paper[k][j]);
			}
			printf("   |\n");
		}
	}
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\npress space to get back.");
	while (kbhit()==0) {
		
	}
	system("cls");
}

