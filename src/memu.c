/* 欢迎界面233 */
#define inix	5
#define iniy	2
#define extra_speed 75

char shaonv[sizeof("          少女祈祷中。。。      ")] = "          少女祈祷中。。。      ";
int  ctrl = 0;
char cont = '\0';

/* 欢迎界面里 打印光标 ‘* ’*/
void printx(int yy){
	gotoxy(inix,yy+iniy);
	printf("*");
}

int memu(const char* user_name,int* extra_button){
	int i = 0;
	int restart = 0;
	while (1) {
		printf("     hello~~  %s,",user_name);
		printf(" Welcome to CPythonCharX  press s&w to move '*'\n");
		printf("     You'd better press win+space to switch english  ");
	
		cprint("start the game                  开始装逼  ",1-1,1);
		cprint("/****************************************/",2-1,1);
		cprint("get point records               查看装逼榜",3-1,1);
		cprint("exit                            退出装逼  ",4-1,1);

		cprint("  ______________________________________  ",5-1,0);
		cprint("  →5,    ~  你， 渴望力量吗？ ~          ",6-1,0);
		cprint("       极制extra以献给渴望力量的人        ",7-1,0);
		
		printx(ctrl);
		getcontrol();
		if ((13 == cont && ctrl == 1-1) || '1' == cont ){
			gotoxy(4,2);
			break;	
		}
		if ((13 == cont && ctrl == 2-1) || '2' == cont ){
			
//			break;
		}
		if ((13 == cont && ctrl == 3-1) || '3' == cont ){
			gotoxy(4,4);
			output_point_records();
		}
		if ((13 == cont && ctrl == 4-1) || '4' == cont ){
			gotoxy(0,15);
			return -1;
		}
		if ((13 == cont && ctrl == 6-1) || '5' == cont ){
			gotoxy(4,7);
			*extra_button = 1;
			break;
		}
		system("cls");
	}

	i = 0;
    while (*(shaonv+i) != '\0'){
        printf("%c",*(shaonv+i));
        _sleep(extra_speed-25);
        i++;
    }
	system("cls");
}

void getcontrol(){
	cont = getch();
	gotoxy(inix,ctrl+iniy);
	printf(" ");

	if ('s' == cont)
		ctrl++;
	if ('w' == cont){
		if (ctrl-- <= 0 )
			ctrl = 0 ;
	}
}

void cprint(const char *sen,int hang,int xh){
	int i = 0;
	gotoxy(inix,iniy+hang);
	if (xh == 1)
		printf("    %d,",hang+1);

	while ( *(sen+i) != '\0'){
		printf("%c",*(sen+i));
		i++;
	}
	return;
}

void win_judge(int *win,int *LEN){
	if (*win){
		printf("\nyou win!!!!");
	} else {
		printf("\n you died.");
		if (  0<=*LEN && *LEN<  48 )
			printf("\n 太短啦!你个大辣鸡！ you a big big rubbish");

		if ( 48<=*LEN && *LEN< 108 )
			printf("\n 卧槽，高手！fu*k，Python Master！");

		if (108<=*LEN && *LEN< 160 ){
			printf("\n 屌，我曾经以\"我不帅\"赢得了世界性的撒谎大赛，相信你也行!");
			printf("\n i have won a worldwide match for t");
		}
		if (160<=*LEN && *LEN<=225 ){
			printf("\n 屌，Python Ghost！\n 不得不承认，还是你比较屌\n 装逼力量get");
			printf("\n 额，巅峰挑战者? 会极限装逼不?  右转 OSB 装逼模式的设计 466317372");
		}

		printf("\n press ESC to exit.");
		printf("\n press  r  to restart.");
		
	}

}

