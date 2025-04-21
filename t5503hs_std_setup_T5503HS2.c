#include <stdio.h>

int sitenum=0;
int penum=0;
int penumall[9];

char site1buf[64];
char site2buf[64];
char site3buf[64];
char site4buf[64];
char site5buf[64];
char site6buf[64];
char site7buf[64];
char site8buf[64];
char commandall[1024];
char commandheader[64];
char rev[8]="1.00";
char getsbuf[64];

void dutselect(){
	for(sitenum=1;sitenum<=8;sitenum++){
	penum=9;
penuminput:
		printf("Input Site%d's PE number [0,3,4,6,8]___",sitenum);
//ori		scanf("%d",&penum);
		gets(getsbuf);
		sscanf(getsbuf,"%d",&penum);
		if(penum!=0 && penum!=3 && penum!=4 && penum!=6 && penum!=8){
			printf("PE number is wrong. Please input[0,3,4,6,8]\n");
			goto penuminput;
		}
	printf("	Site%d's PE number is %d\n\n",sitenum,penum);
	penumall[sitenum]=penum;
	}
}

void dutsetup(){
	for(sitenum=1;sitenum<=8;sitenum++){
		switch(sitenum){
			case 1:
			if (penumall[sitenum]==0) strcpy(site1buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site1buf,"3 4 7 8 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site1buf,"1-8 ");
			break;
			case 2:
			if (penumall[sitenum]==0) strcpy(site2buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site2buf,"11 12 15 16 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site2buf,"9-16 ");
			break;
			case 3:
			if (penumall[sitenum]==0) strcpy(site3buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site3buf,"19 20 23 24 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site3buf,"17-24 ");
			break;
			case 4:
			if (penumall[sitenum]==0) strcpy(site4buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site4buf,"27 28 31 32 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site4buf,"25-32 ");
			break;
			case 5:
			if (penumall[sitenum]==0) strcpy(site5buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site5buf,"35 36 39 40 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site5buf,"33-40 ");
			break;
			case 6:
			if (penumall[sitenum]==0) strcpy(site6buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site6buf,"43 44 47 48 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site6buf,"41-48 ");
			break;
			case 7:
			if (penumall[sitenum]==0) strcpy(site7buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site7buf,"51 52 55 56 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site7buf,"49-56 ");
			break;
			case 8:
			if (penumall[sitenum]==0) strcpy(site8buf," ");
			if (penumall[sitenum]==3 || penumall[sitenum]==4) strcpy(site8buf,"59 60 63 64 ");
			if (penumall[sitenum]==7 || penumall[sitenum]==8) strcpy(site8buf,"57-64 ");
			break;
		}
	}

	strcpy(commandheader,"fssdut --enable ");
	strcat(commandall,commandheader);	
	strcat(commandall,site1buf);	
	strcat(commandall,site2buf);	
	strcat(commandall,site3buf);	
	strcat(commandall,site4buf);	
	strcat(commandall,site5buf);	
	strcat(commandall,site6buf);	
	strcat(commandall,site7buf);	
	strcat(commandall,site8buf);	
printf("command=%s\n",commandall);

	system("fsfk --off 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 > /dev/null");
	system("fsfk --on 1,5,6");

	system("fstmode --auto > /dev/null");

	system("fssdut --disable-all > /dev/null");
	system(commandall);
}

int main(){

	system("clear");
	printf("**********************************************************\n");
	printf("**********************************************************\n");
	printf("T5511 STD DEVICE PROGRAM FUNCTION KEY & DUT SET UP PROGRAM\n");
//	printf("rev %s\n",rev);
	printf("**********************************************************\n");
	printf("**********************************************************\n\n");

	printf("**********************************************************\n");
	printf("IF TARGET SITE DONES NOT HAVE SOCKET BOARD, PLESE INPUT 0 \n");
	printf("**********************************************************\n\n");
	dutselect();
	dutsetup();

	printf("\n\n");
	printf("**********************************************************\n");
	printf("**********************************************************\n");
	printf("T5511 STD DEVICE PROGRAM FUNCTION KEY & DUT SET UP FINISH!\n");
	printf("PLEASE SET UP LOG SETTING THEN RUN PROGRAM.               \n");
//	printf("rev %s\n",rev);
	printf("**********************************************************\n");
	printf("**********************************************************\n\n");
	printf("\n\n");
	return 0;

}

