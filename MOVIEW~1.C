#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

struct Userdata{
    int total_users;
	char username[31];
	char password[11];
};

FILE *user;
struct  Userdata u;

int nextUserID();
void SignIn();
void SignUp_SignIn();
void SignUp();
void PrintLayout(char seat1[],int movie,int slot,char mobile[]);
void outline(int c1, int r1, int c2, int r2,int color);
void singleline(int c1, int r1, int c2, int r2,int color);
void singleline1(int c1, int r1, int c2, int r2);
void outline1(int c1, int r1, int c2, int r2);
void box(int size,int color);
void title(char *title, int row, int color);
int UpdateBookedSeats(char seat1[]);
int nextCustomerId();
void ResetAudi();
void setup();
void booking();
void CancelTicket();
void UpdateTicket();
int isValidMobile(char *mobile);

int isValidMobile(char *mobile){
	int i=0;
	if(atoi(mobile)==0)
	{
		return 0;
	}
	while(mobile[i]){
		if(!isdigit(mobile[i])){
			return 0;			
		}
		i++;
	}
	
	return 1;
}

struct Customer{
	int CusId,column,number,movie,slot;
	char datetime[20];
	char mobile[12];
	char row;

};
FILE *fp1,*fp2;
struct Customer c;

struct Cancel{
	int CanId;
};
struct Cancel ca;

int nextCustomerId(){int counter=0;
	rewind(fp1);
	rewind(fp1);
	while(fread(&c,sizeof(c),1,fp1)){
		counter++;
	}//fclose(fp1);
	return (counter+1);
}

int nextUserID(){
	int counter=0;
	rewind(user);
	while(fread(&u,sizeof(u),1,user))
		counter++;
	return (counter+1);
}
char seat[72];
FILE *fp;

void main()
{
	int i;

	clrscr();
	for(i=0;i<72;i++)
	seat[i]='0';
	textbackground(BLACK);
       //PrintLayout(seat,1,1);
       //setup();
       //booking();
	 SignUp_SignIn();
	getch();

	//for(i=0;i<72;i++)printf("%c ",seat[i]);getch();
}

void SignUp(){
char username[31],password[11],re_password[11],ch,re_ch;
	int i=0,already_exist=0;
	clrscr();
	outline1(13,2,54,19);
	user=fopen("demo.txt","a+");
	title("MOVIE TICKET BOOKING SYSTEM",5,YELLOW);
	textcolor(GREEN);
	gotoxy(32,7);printf("User Authentication");
	gotoxy(25,10);printf("Username");
	gotoxy(37,10);box(15,1);
	gotoxy(25,12);printf("Password");
	gotoxy(37,12);box(15,1);
	gotoxy(25,14);printf("Re-Enter Password");
	gotoxy(37,14);box(15,1);
	do{gotoxy(37,10);box(15,1);
	gotoxy(37,10);	
	gets(username);
	rewind(user);
	while(fread(&u,sizeof(u),1,user)){
		if(strcmp(u.username,username)==0){
			already_exist=1;
			break;
		}
		else
			already_exist=0;
	}
	
	if(already_exist==1){
	gotoxy(25,20);	
	printf("Username Already Exists...");
	gotoxy(25,21);
	printf("Please Re-Enter");
	sleep(.5);}
	}while(already_exist==1);
	
	do{
	fflush(stdin);
	gotoxy(37,12);
	while(i<10){
		ch=getch();
		if(ch==13) break;
		else if(ch==8){
			if(i>0)
			{

				int n;
				i--;
				gotoxy(37,12);clreol(); //clear till end of line
				for(n=0;n<i;n++) putchar('*');
			}
			      }
		else{
			password[i]=ch;
			putchar('*');
			i++;
		    }
		}
	password[i]='\0';
	i=0;
	gotoxy(37,14);
	fflush(stdin);
	while(i<10){
		re_ch=getch();
		if(re_ch==13) break;
		else if(re_ch==8){
			if(i>0)
			{

				int n;
				i--;
				gotoxy(37,14);clreol(); //clear till end of line
				for(n=0;n<i;n++) putchar('*');
			}
		}
		else{
			re_password[i]=re_ch;
			putchar('*');
			i++;
		}

	}
	re_password[i]='\0';
		gotoxy(37,12);
		clreol();
		box(15,1);
		gotoxy(37,14);
		clreol();
		box(15,1);
	}while(strcmp(password,re_password)!=0);


	u.total_users=nextUserID();
	fflush(stdin);
	strcpy(u.username,username);
	fflush(stdin);
	strcpy(u.password,password);
	fseek(user,0,SEEK_END);
	fwrite(&u,sizeof(struct Userdata),1,user);
	fclose(user);
	SignIn();
}

void SignIn(){
	char username[31],password[11],ch;
	int i=0,key=0;
	clrscr();
	outline1(13,2,54,15);

	title("MOVIE TICKET BOOKING SYSTEM",5,YELLOW);
	textcolor(GREEN);
	gotoxy(32,7);
	printf("User Authentication");
	gotoxy(25,10);
	printf("Username");
	gotoxy(37,10);
	box(15,1);
	gotoxy(25,12);
	printf("Password");
	gotoxy(37,12);
	box(15,1);
	gotoxy(37,10);
	gets(username);
	fflush(stdin);
	gotoxy(37,12);
	while(i<10){
		ch=getch();
		if(ch==13) break;
		else if(ch==8){
			if(i>0)
			{
				int n;
				i--;
				gotoxy(37,12);
				clreol(); //clear till end of line
				for(n=0;n<i;n++) 
				putchar('*');
			}
		}
		else{
			password[i]=ch;
			putchar('*');
			i++;
		}
	}
	password[i]='\0';
	user=fopen("demo.txt","r");
	//rewind(user);
	while(fread(&u,sizeof(u),1,user)){
		if(strcmp(u.username,username)==0 && strcmp(u.password,password)==0){
			gotoxy(25,20);
			textbackground(1);
			cprintf("LOGIN SUCCESSFULL DONE");
			textbackground(0);
			sleep(1);
			key=1;
			setup();
			break;
		}
	}
	fclose(user);
	if(key==0)
	{
	gotoxy(25,20);
	printf("Invalid Username or Password!!");
	gotoxy(25,21);
	printf("Please Re-Enter");
	sleep(1);
	SignIn();
	}


}

void SignUp_SignIn()
{
int i;char key[12]="SecurityKey",key1[12];
char choice[5];
clrscr();
singleline1(10,2,64,20);
gotoxy(15,5);
textbackground(4);
textcolor(WHITE);
cprintf("          A Theatre You Will Fall In Love With         ");
textbackground(9);
gotoxy(23,8);
 cprintf("                                        ");
gotoxy(23,20);
cprintf("                                        ");
for(i=9;i<20;i++)
{
gotoxy(23,i);
cprintf(" ");
gotoxy(62,i);
cprintf(" ");
}
gotoxy(27,9);
textbackground(3);
cprintf("  MOVIE TICKET BOOKING SYSTEM");
gotoxy(0,9);
box(6,3);
gotoxy(24,9);
box(3,3);
fflush(stdin);
textbackground(9);
gotoxy(23,10);
cprintf("                                        ");
gotoxy(24,12);
printf(" LOGIN / SIGH UP MENU:");
gotoxy(24,14);textcolor(15);textbackground(0);
cprintf(" if already a user then sign in (I) ");
gotoxy(25,15);
cprintf("| else sign up (U)");
textbackground(11);
gotoxy(26,18);
cprintf(" SIGN IN ");
gotoxy(23,21);
printf("q/Q : To Quit");
gotoxy(51,18);
cprintf(" SIGN UP ");

do
{  textcolor(15);
gotoxy(23,22);
cprintf("Enter choice as (U/I/Q)");
gets(choice);
}while(strcmp(choice,"u")!=0&&strcmp(choice,"i")!=0&&strcmp(choice,"U")!=0&&strcmp(choice,"I")!=0&&strcmp(choice,"q")!=0&&strcmp(choice,"Q")!=0);

fflush(stdin);
gotoxy(23,24);
box(35,1);
textbackground(BLACK);
textcolor(15);
if(strcmp(choice,"i")==0||strcmp(choice,"I")==0)
SignIn();
else if(strcmp(choice,"u")==0||strcmp(choice,"U")==0){textcolor(15);
gotoxy(23,24);printf("Enter Security Key : ");
gotoxy(43,24);gets(key1);
if(strcmp(key1,key)==0)
SignUp();
else{gotoxy(23,25);printf("Invalid Security Key....Plz Try Again Later");}
}
else if(strcmp(choice,"q")==0||strcmp(choice,"Q")==0)
exit(0);
}


void ResetAudi()
{
	int i=0,c;char local[72];
	fp=fopen("seat.txt","a+");
	rewind(fp);
	while(i<72){
		local[i]='0';
		i++;
		 }
	fclose(fp);
	fp=fopen("seat.txt","w+");
	fwrite(local,1,sizeof(local),fp);
	fclose(fp);
}
void setup()
{
int m=10,n=51,i,j,a=0,b=0,c=0,option=0;
textbackground(0);
textcolor(15);
clrscr();
gotoxy(9,3);
textbackground(1);
cprintf("                            MAIN MENU                           ");
singleline(1,1,78,22,4);
gotoxy(21,5);
textbackground(6);
cprintf("         WELCOME TO MAK CINEMAS        ");
for(i=0;i<m;i++)
	{
	for(j=0;j<n;j++)
		{gotoxy(9+j,6+i);
		if(j==12||j==n-1||(i==m-1 && j>=12)){textbackground(6);
		cprintf(" ");}
	else if(i==1&&a==0)
		{ textbackground(1);gotoxy(9+12+j,6+i);
		cprintf(" 1. BOOKING                           ");
		j+=22;
		a++;
		}
		else if(i==4&&b==0)
		{
		textbackground(1);gotoxy(9+12+j,6+i);
		cprintf(" 2. UPDATE                            ");
		j+=21;
		b++;
		}
		else if(i==7&&c==0)
		{ textbackground(1);gotoxy(9+12+j,6+i);
		cprintf(" 3. CANCEL                            ");
		j+=21;
		c++;
		}
		else
		printf(" ");
		}
	printf("\n");
	}
	textcolor(7);
	textbackground(11);
	textcolor(15);
	gotoxy(3,17);
	cprintf("Press 0 To Reset Auditoriam / Press 4 To Quit");
	gotoxy(3,20);
	printf("PLEASE SELECT AN OPTION FROM THE ABOVE MENU");
	do
	{
	gotoxy(3,21);
	box(5,1);
	gotoxy(3,21);
	scanf("%d",&option);
	}while(option!=1 && option!=2 && option!=3 && option!=0 &&  option!=4);
	if(option==1)booking();
	else if(option==0)
	{	ResetAudi();
		gotoxy(3,22);
		printf("Audi Reset Successful....");
	}
	else if(option==3)
		CancelTicket();
	else if(option==4)
		exit(1);
	else if(option==2)
		UpdateTicket();
}

void booking()
{
int m=10,n=51,i,j,a=0,b=0,c=0,d=0,movie,slot;char ch;clrscr();textbackground(0);textcolor(15);
textbackground(4);
gotoxy(9,3);
cprintf("                           BOOKING MENU                          ");
gotoxy(23,5);
textbackground(9);     
textcolor(15);
cprintf("     MOVIES                TIMINGS     ");
for(i=0;i<m;i++)
	{
	for(j=0;j<n;j++)
		{gotoxy(11+j,6+i);
		if(j==12||j==n-1||(i==m-1 && j>=12))
		{
		textbackground(9);
		cprintf(" ");
		}
		else if(i==1&&a==0)
		{
		textbackground(6);
		printf("            ");
		cprintf(" 1) 3 Idiots          11:00 , 17:30   ");
		j+=49;
		a++;
		}
		else if(i==3&&b==0)
		{
		textbackground(6);
		printf("            ");
		cprintf(" 2) Bahubali          10:00 , 16:30   ");
		j+=49;
		b++;
		}
		else if(i==5&&c==0)
		{
		textbackground(6);
		printf("            ");
		cprintf(" 3) Annabelle         12:00 , 18:30   ");
		j+=49;
		c++;
		}
		else if(i==7&&d==0)
		{
		textbackground(6);
		printf("            ");
		cprintf(" 4) Chhichhore        10:30 , 18:00   ");
		j+=49;
		d++;
		}
		else if(j>=13)
		{
		textbackground(3);
		cprintf(" ");
		}
		else
		printf(" ");
		}
	}
	textbackground(4);
	outline(1,1,78,22,15);
	gotoxy(11,17);
	textbackground(11);
	cprintf("PLEASE SELECT AN OPTION FROM THE ABOVE MENU");
	textbackground(0);
	gotoxy(11,18);
	printf("(Press q to quit / Press m to return to main menu / ");
	gotoxy(11,19);
	printf("Or Any Other Key To Continue):");
	gotoxy(45,19);
	ch=getch();
	if(ch=='q')exit(1);
	else if(ch=='m')setup();
	else{
	do
	{gotoxy(11,21);
	box(15,1);
	gotoxy(11,21);
	printf("movie : ");
	scanf("%d",&movie);
	}while(movie!=1 && movie!=2 && movie!=3 && movie!=4);
	do
	{gotoxy(11,23);
	box(15,1);
	gotoxy(11,23);
	printf("slot  : ");
	scanf("%d",&slot);
	}while(slot!=1 && slot!=2);
	PrintLayout(seat,movie,slot,"0000000000");  }
	textcolor(15);
	textbackground(0);
}


int UpdateBookedSeats(char seat1[])
{

	int c,i;char local[72];
	fp=fopen("seat.txt","a+");
	rewind(fp);
	i=0;
	while(i<72) {
		c = fgetc(fp);
		if( feof(fp) )
			break ;
		if(c=='0' && seat1[i]=='1')local[i]='1';
		else if(c=='0' && seat1[i]=='0')local[i]='0';
		else if(c=='1' && seat1[i]=='0')local[i]='1';
		else if(c=='1' && seat1[i]=='1')return 1;
		i++;
		 }
	fclose(fp);
	fp=fopen("seat.txt","w+");
	fwrite(local,1,sizeof(local),fp);
	fclose(fp);
	return 0;
}

void PrintLayout(char seat1[],int movie,int slot,char mobile[])
{       int m,id;char d,timedate[20];
	int check=0,j;int i,x,y,number,column;
	char row;
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	assert(strftime(timedate, sizeof(timedate), "%c", tm));
	do{
	for(i=0;i<72;i++)
	seat[i]='0';
	clrscr();
	gotoxy(26,1);
	textcolor(WHITE+BLINK);cputs("MOVIE TICKET BOOKING SYSTEM");
	singleline(1,2,78,20,4);
	gotoxy(13,4);
	box(56,1);
	gotoxy(30,4);
	textcolor(15);
	textbackground(1);
	cprintf("All Eyes Here Please");
	gotoxy(78,7);
	textbackground(7);
	textcolor(15);
	cprintf("E ");
	gotoxy(78,8);
	cprintf("N ");
	gotoxy(78,9);
	cprintf("T ");
	gotoxy(78,10);
	cprintf("R ");
	gotoxy(78,11);
	cprintf("Y ");
	gotoxy(35,22);
	box(17,7);
	gotoxy(41,22);
	printf("EXIT");
	textbackground(BLACK);
	outline(4,7,35,8,15);
	outline(41,7,35,8,15);
	outline(4,17,73,3,15);
	gotoxy(1,24);
	printf("* - Available");
	gotoxy(65,24);
	printf("- Already Booked");
	gotoxy(63,24);textcolor(1);
	cprintf("*");textcolor(15);
	for(i=1;i<=12;i++)
	{       gotoxy((6*i)+1,6);
		printf("%d",i);
	}
	gotoxy(3,8);
	printf("A");
	gotoxy(3,10);
	printf("B");
	gotoxy(3,12);
	printf("C");
	gotoxy(3,14);
	printf("D");
	gotoxy(3,18);
	printf("E");
	gotoxy(3,20);
	printf("F");
	gotoxy(70,3);
	box(10,3);
	gotoxy(70,3);
	printf("AUDI - 1");
	fp1=fopen("seat.txt","a+");
	rewind(fp1);
	i=0;
	//while(i<72) {
	  //	d=fgetc(fp1);
		//if( feof(fp) )
		  //	break ;

	for(x=1;x<=14;x+=2)
	{
		if(x==9)
		continue;
		for(y=1;y<=72;y+=6)
		{gotoxy(6+y,7+x);
		d=fgetc(fp1);
		if(d=='1'){
			   textcolor(1);
			   cprintf("*");
			   textcolor(15);
			}
		else if(d=='0'){
			textcolor(15);
			cprintf("*");
			textcolor(15);}
		}
	}
	//i++;}
	fclose(fp1);
	gotoxy(2,25);
	box(78,3);
	gotoxy(2,25);
	printf("Enter The No.Of Seats To Be Booked :-");
	scanf("%d",&number);
	gotoxy(2,25);
	box(78,3);
	gotoxy(2,25);
	printf("Enter The Row :-");
	do{
	scanf("%s",&row);
	}while(row!='a'&& row!='b'&& row!='c'&& row!='d' && row!='e' && row!='f'&& row!='A' && row!='B' && row!='C' && row!='D' && row!='E'&& row!='F');
	gotoxy(2,25);
	box(78,3);
	gotoxy(2,25);
	printf("Enter The Column :-");
	do{
	scanf("%d",&column);
	}while(column>12);
	if(row=='a'|| row=='A')
		for(i=column-1;i<column+number-1;i++)
			seat1[i]='1';
	else if(row=='b'|| row=='B')
		for(i=column+11;i<column+number+11;i++)
			seat1[i]='1';
	else if(row=='c'|| row=='C')
		for(i=column+23;i<column+number+23;i++)
			seat1[i]='1';
	else if(row=='d'|| row=='D')
		for(i=column+35;i<column+number+35;i++)
			seat1[i]='1';
	else if(row=='e'|| row=='E')
		for(i=column+47;i<column+number+47;i++)
			seat1[i]='1';
	else if(row=='F'|| row=='f')
		for(i=column+59;i<column+number+59;i++)
			seat1[i]='1';

	check=UpdateBookedSeats(seat);}while(check!=0);
	clrscr();
	gotoxy(28,4);
	textcolor(WHITE);cputs("MOVIE TICKET BOOKING SYSTEM");
	textcolor(WHITE+BLINK);
	singleline(22,2,37,22,4);
	gotoxy(23,23);
	box(37,3);
	gotoxy(23,24);
	box(37,3);
	gotoxy(28,23); 
	textbackground(3);
	textcolor(WHITE);
	cprintf("The cinema has no boundary;");
	gotoxy(29,24);
	cprintf("it is a ribbon of dreams");
	singleline(26,3,29,1,0);
	gotoxy(40,7);
	printf("%s",timedate);
	gotoxy(24,7);
	printf("AUDI - 1");
	for(m=0;m<37;m++){gotoxy(23+m,6);
	cprintf("%c",196);   }
	for(m=0;m<37;m++){gotoxy(23+m,8);
	cprintf("%c",196);   }
	if(movie==1 && slot==1)
	{gotoxy(24,10);printf("MOVIE -> 3 Idiots");gotoxy(24,12);printf("TIMING -> 11:00");}
	else if(movie==1 && slot==2)
	{gotoxy(24,10);printf("MOVIE -> 3 Idiots");gotoxy(24,12);printf("TIMING -> 17:30");}
	else if(movie==2 && slot==1)
	{gotoxy(24,10);printf("MOVIE -> Bahubali");gotoxy(24,12);printf("TIMING -> 10:00");}
	else if(movie==2 && slot==2)
	{gotoxy(24,10);printf("MOVIE -> Bahubali");gotoxy(24,12);printf("TIMING -> 16:30");}
	else if(movie==3 && slot==1)
	{gotoxy(24,10);printf("MOVIE -> Annabelle");gotoxy(24,12);printf("TIMING -> 12:00");}
	else if(movie==3 && slot==2)
	{gotoxy(24,10);printf("MOVIE -> Annabelle");gotoxy(24,12);printf("TIMING -> 18:30");}
	else if(movie==4 && slot==1)
	{gotoxy(24,10);printf("MOVIE -> Chhichhore");gotoxy(24,12);printf("TIMING -> 10:30");}
	else if(movie==4 && slot==2)
	{gotoxy(24,10);printf("MOVIE -> Chhichhore");gotoxy(24,12);printf("TIMING -> 18:00");}
	gotoxy(24,14);printf("SEAT -> %c (%d - %d)",row,column,column+number-1);
	for(m=0;m<37;m++){gotoxy(23+m,18);
	cprintf("%c",196);   }
	gotoxy(24,19);
	if(row!='e'&&row!='E' && row!='f' && row!='F'){
	printf("Total Billing Amount = %d * 180",number);gotoxy(45,20);printf("= %d(inc.GST)",180*number);}
	else {
	printf("Total Billing Amount = %d * 250",number);gotoxy(45,20);printf("= %d(inc.GST)",250*number);}
	for(m=0;m<37;m++){gotoxy(23+m,22);if(m==10){puts(" Enjoy Your Day ");m+=15;}
	cprintf("%c",1);   }
	for(m=0;m<37;m++){gotoxy(23+m,21);
	cprintf("%c",196);   }

	fp1=fopen("customer.txt","a+");fflush(stdin);
	id=nextCustomerId();fflush(stdin);
	gotoxy(44,9);printf("Booking Id : %d",id);
	c.CusId=id;fflush(stdin);
	c.column=column;fflush(stdin);
	c.number=number;fflush(stdin);
	c.movie=movie;fflush(stdin);
	c.slot=slot;fflush(stdin);
	strcpy(c.datetime,timedate);fflush(stdin);
	if(strcmp(mobile,"0000000000")==0){
	gotoxy(24,16);printf("Mobile No : ");for(;;){gotoxy(36,16);box(10,1);
		gotoxy(36,16);
		fflush(stdin);scanf("%s",c.mobile);
		if(strlen(c.mobile)==10 && isValidMobile(c.mobile) && (c.mobile[0]=='9'||c.mobile[0]=='8'||c.mobile[0]=='7'||c.mobile[0]=='6')){
			//c.mobile=atoi(c.mobile);
			break;}}}
	else{
	gotoxy(24,16);
	printf("Mobile No : ");
	gotoxy(36,16);
	box(10,1);
	gotoxy(36,16);
	printf("%s",mobile);
	}
	c.row=row;
	fseek(fp1,0,SEEK_END);
	fwrite(&c,sizeof(struct Customer),1,fp1);
	fclose(fp1);


}

void UpdateTicket(){
	int Cid,m,found=0,found1=0;
	clrscr();
	singleline(26,3,30,13,1);
	gotoxy(27,4);
	box(30,4);
	gotoxy(27,5);
	box(30,4);
	gotoxy(27,6);
	box(30,4);
	gotoxy(35,5);
	printf("UPDATE MENU");
	for(m=0;m<30;m++){textbackground(1);gotoxy(27+m,7);
	cprintf("%c",196);   }textbackground(0);
	gotoxy(30,9);
	printf("Enter Booking Id : ");
	for(m=0;m<30;m++){textbackground(0);textcolor(4);gotoxy(27+m,13);
	cprintf("%c",240);   }textbackground(0);textcolor(15);
	gotoxy(50,9);
	scanf("%d",&Cid);
	fp=fopen("customer.txt","r+");rewind(fp);
	fp1=fopen("cancel.txt","r+");rewind(fp1);
	while(fread(&c,sizeof(c),1,fp)){
		if(c.CusId==Cid){
			found=1;
			break;
		}
	}fclose(fp);
	while(fread(&ca,sizeof(ca),1,fp1)){
		if(ca.CanId==Cid){
			found1=1;
			break;
		}
	}fclose(fp1);
	if(found && !found1){gotoxy(22+10-8+3+1,15);textbackground(11);textcolor(BLUE);
		cprintf("Above Seats Will Be Updated!");textbackground(0);textcolor(15);
		gotoxy(32,11);printf("SEAT -> %c (%d - %d)",c.row,c.column,c.column+c.number-1);
		getch();
		CancelTicket();
		getch();
		PrintLayout(seat,c.movie,c.slot,c.mobile);

	}
	else if(found && found1){   gotoxy(24+3,15);textbackground(11);textcolor(BLUE);
		cprintf("ERROR:Seats Already Updated!!!");textbackground(0);textcolor(15);
	}
	else {   gotoxy(24+5,14);textbackground(11);textcolor(BLUE);
		cprintf("ERROR: Record Not Found!!!");textbackground(0);textcolor(15);
	}
textcolor(15);textbackground(0);
}

void CancelTicket(){
	int Cid,m,found=0,found1=0,found3=0,i;char seat1[72],ch;
	clrscr();
	singleline(26,3,30,12,1);
	gotoxy(27,4);
	box(30,4);
	gotoxy(27,5);
	box(30,4);
	gotoxy(27,6);
	box(30,4);
	gotoxy(36,5);
	printf("CANCELATION");
	for(m=0;m<30;m++){textbackground(1);
	gotoxy(27+m,7);
	cprintf("%c",196);
	   }textbackground(0);
	gotoxy(30,9);
	printf("Enter Booking Id : ");
	gotoxy(50,9);
	scanf("%d",&Cid);
	fp=fopen("customer.txt","a+");//fflush(stdin);
	fp1=fopen("seat.txt","a+");//fflush(stdin);
	fp2=fopen("cancel.txt","a+");//fflush(stdin);
	rewind(fp);
	//rewind(fp1);
	rewind(fp2);
	while(fread(&c,sizeof(c),1,fp)){
		if(c.CusId==Cid){
			found=1;
			break;
		}
	}rewind(fp2);
	while(fread(&ca,sizeof(ca),1,fp2)){
		if(ca.CanId==c.CusId){
			found1=1;
			break;
		}
	}rewind(fp1);
	for(i=0;i<72;i++) seat1[i]=fgetc(fp1);fclose(fp1);
	if(found1){gotoxy(22+10,14);textbackground(11);textcolor(BLUE);
		cprintf("  Already Deleted  ");textbackground(0);textcolor(15);}
	else if(found && !found1){gotoxy(22+10,14);textbackground(11);textcolor(BLUE);
		cprintf("  Ticket Cancelled  ");textbackground(0);textcolor(15);
		gotoxy(32,11);printf("SEAT -> %c (%d - %d)",c.row,c.column,c.column+c.number-1);
		ca.CanId=c.CusId;
		fseek(fp2,0,SEEK_END);
	fwrite(&ca,sizeof(struct Cancel),1,fp2);
	fclose(fp2);
		if(c.row=='a'|| c.row=='A')
		for(i=c.column-1;i<c.column+c.number-1;i++)
			seat1[i]='0';
	else if(c.row=='b'|| c.row=='B')
		for(i=c.column+11;i<c.column+c.number+11;i++)
			seat1[i]='0';
	else if(c.row=='c'|| c.row=='C')
		for(i=c.column+23;i<c.column+c.number+23;i++)
			seat1[i]='0';
	else if(c.row=='d'|| c.row=='D')
		for(i=c.column+35;i<c.column+c.number+35;i++)
			seat1[i]='0';
	else if(c.row=='e'|| c.row=='E')
		for(i=c.column+47;i<c.column+c.number+47;i++)
			seat1[i]='0';
	else if(c.row=='F'|| c.row=='f')
		for(i=c.column+59;i<c.column+c.number+59;i++)
			seat1[i]='0';
	fp1=fopen("seat.txt","w+");
	fwrite(seat1 , 1 , sizeof(seat1) , fp1 );
	fclose(fp1);fclose(fp);
	}

	else{   gotoxy(24+5,14);
		textbackground(11);
		textcolor(BLUE);
		cprintf("ERROR:Record not  found!!!");
		textbackground(0);textcolor(15);
	}
textcolor(15);
textbackground(0);
}

void outline(int c1, int r1, int c2, int r2,int color){
	int i,j;
	textcolor(color);
	gotoxy(c1,r1);
	cprintf("%c",201);
	for(i=1;i<=c2;i++)
	   cprintf("%c",205);
	cprintf("%c",187);
	for(i=1;i<=r2;i++)
	{
	  gotoxy(c1,r1+i);
	  cprintf("%c",186);
	  gotoxy(c1+c2+1,r1+i);
	  cprintf("%c",186);
	}
	gotoxy(c1,r1+i);
	cprintf("%c",200);
	for(i=1;i<=c2;i++)
	   cprintf("%c",205);
	cprintf("%c",188);
}

void singleline(int c1, int r1, int c2, int r2,int color){
	int i;
	gotoxy(c1,r1);
	textbackground(color);
	cprintf("%c",218);
	for(i=1;i<=c2;i++)
	   cprintf("%c",196);
	cprintf("%c",191);
	for(i=1;i<=r2;i++)
	{
	  gotoxy(c1,r1+i);
	  cprintf("%c",179);
	  gotoxy(c1+c2+1,r1+i);
	  cprintf("%c",179);
	}
	gotoxy(c1,r1+i);
	cprintf("%c",192);
	for(i=1;i<=c2;i++)
	   cprintf("%c",196);
	cprintf("%c",217);
}

void title(char *title, int row, int color){
	int col=40-strlen(title)/2;
	gotoxy(col,row);
	textcolor(color);
	cprintf("%s",title);
	textcolor(WHITE);
}

void outline1(int c1, int r1, int c2, int r2){
	int i,j;
	textcolor(RED);
	gotoxy(c1,r1);
	cprintf("%c",201);
	for(i=1;i<=c2;i++)
	   cprintf("%c",205);
	cprintf("%c",187);
	for(i=1;i<=r2;i++)
	{
	  gotoxy(c1,r1+i);
	  cprintf("%c",186);
	  gotoxy(c1+c2+1,r1+i);
	  cprintf("%c",186);
	}
	gotoxy(c1,r1+i);
	cprintf("%c",200);
	for(i=1;i<=c2;i++)
	   cprintf("%c",205);
	cprintf("%c",188);
}

void singleline1(int c1, int r1, int c2, int r2){
	int i;
	gotoxy(c1,r1);
	printf("%c",218);
	for(i=1;i<=c2;i++)
	   printf("%c",196);
	printf("%c",191);
	for(i=1;i<=r2;i++)
	{
	  gotoxy(c1,r1+i);
	  printf("%c",179);
	  gotoxy(c1+c2+1,r1+i);
	  printf("%c",179);
	}
	gotoxy(c1,r1+i);
	printf("%c",192);
	for(i=1;i<=c2;i++)
	   printf("%c",196);
	printf("%c",217);
}

void box(int size,int color){
	int i;
	textbackground(color);
	for(i=1;i<=size;i++)
	  cprintf(" ");


	textbackground(BLACK);
}








