/* 用户系统 */


void point_paper_arr(int *point_paper,int point,int bushu,int LEN){
	int j,k,i,temp;
	for (j=0;j<8;j++){
		for (k=j+1;k<8;k++){
			if ( *(point_paper+1*8 +j) < *(point_paper+1*8+k)){
				for (i=0;i<7;i++){
					temp = *(point_paper+i*8+j);
					*(point_paper+ i*8+j) = *(point_paper+i*8+k);
					*(point_paper+ i*8+k) = temp;
				}
			}
		}
	}
	*(point_paper+0*8+7) = 0;
	*(point_paper+1*8+7) = point;
	*(point_paper+2*8+7) = bushu;
	*(point_paper+3*8+7) = LEN;
	for (j=0;j<8;j++){
		for (k=j+1;k<8;k++){
			if ( *(point_paper+1*8 +j) < *(point_paper+1*8+k)){
				for (i=0;i<7;i++){
					temp = *(point_paper+i*8+j);
					*(point_paper+ i*8+j) = *(point_paper+i*8+k);
					*(point_paper+ i*8+k) = temp;
				}
			}
		}
	}
}
