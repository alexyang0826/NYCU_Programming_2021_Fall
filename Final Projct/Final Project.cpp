#include <iostream>
#include <cstring>
#include <algorithm>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#include <fstream>
#include <Windows.h>
#include <Windows.h>
#include <dos.h>
#include <cmath>
using namespace std;
struct user{
	char username[13];
	char passwd[13];
	int login_no;
	int money;
	int lose,win,tie;
};
struct userlist{
	int user_no;
	user member[100];
};
struct order{
	char user[13];
	int meal;
	int no;
	int sw;
	int ice;
};
userlist users;
struct orderlist{
	int mealno;
	int orderno;
	order member[100];
};
int user_id;
orderlist orders; 
//----------------------------SQL Function
void update();
void updateO();
//----------------------------Login Function
userlist LoadUsers();
int Login();
void input_username(char un[]);
void input_password(char un[],char pw[]);
void input_password2(char un[],char pw[],char pw2[]);
int mainLI();
//----------------------------MainUI Function
void MainScreen(int select,int id);
int MainUI(int select,int id);
int mainUI(int id);
void KScreen(int select,int id);
int KUI(int select,int id);
int KEUI();
//----------------------------Order Function
orderlist LoadOrders();
void OrderScreen(int select,int id);
int OrderUI(int select,int id);
int orderUI(int id);
void OrderScreen1(int select,int id);
int OrderUI1(int select,int id);
int orderUI1(int id);
void OrderScreen2(int select,int id);
int OrderUI2(int select,int id);
int orderUI2(int id);
void OrderScreen3(int select,int id);
int OrderUI3(int select,int id);
int orderUI3(int id);
void OrderScreen4(int id,int no,int i);
//----------------------------Check Function
int mainCK(int id);
int mainCKK();
int money();
//----------------------------ChangePW Function
void changePw(int id);
void change_password(char pw[]);
void change_password1(char pw[],char pw2[]);
void change_password2(char pw[],char pw2[],char pw3[]);
//----------------------------Chatroom Function
void Chatroom(char un[]);
//----------------------------Sudoku Function
int map[9][9];
int mainSu(int id);
void init(int p[][9][10]);
void Sudoku_Read(int Qno, int Q[][9], int p[][9][10]);
void Sudoku_Print(int Q[][9],int A[][9],int R,int C);
int Sudoku_Check(int p[][9][10],int R,int C);
void MainUIS(int Q[][9],int A[][9]);
bool isPlace(int count);
void backtrace(int count);
//----------------------------XAXB Function
void num2digit(int num,int digit[]);
bool isLegal(int num);
void XAXB(int G,int A,int AB[]);
int mainXAXB(int id);
//-----------------------------Car Game Function
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 
HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4]={' ','A','A',' ',
				'A','A','A','A',
				' ','A','A',' ',
				'A','A','A','A',};
int carPos=WIN_WIDTH/2;
int score=0;
void gotoxy(int x,int y){
	CursorPosition.X=x;
	CursorPosition.Y=y;
	SetConsoleCursorPosition(console, CursorPosition);
}				
void setcursor(bool visible, DWORD size){
	if(size==0)
		size=20;
	
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible=visible;
	lpCursor.dwSize=size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){
	for(int i=0;i<SCREEN_HEIGHT;i++){
		for(int j=0;j<17;j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±"; 
		}
	}
	for(int i=0;i<SCREEN_HEIGHT;i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	}
}
void genEnemy(int ind){
	enemyX[ind]=17+rand()%(33);
}
void drawEnemy(int ind){
	if(enemyFlag[ind]==true){
		gotoxy(enemyX[ind],enemyY[ind]);   cout<<"****";
		gotoxy(enemyX[ind],enemyY[ind]+1); cout<<" ** ";
		gotoxy(enemyX[ind],enemyY[ind]+2); cout<<"****";
		gotoxy(enemyX[ind],enemyY[ind]+3); cout<<" ** ";
	}
}
void eraseEnemy(int ind){
	if(enemyFlag[ind]==true){
		gotoxy(enemyX[ind],enemyY[ind]);   cout<<"    ";
		gotoxy(enemyX[ind],enemyY[ind]+1); cout<<"    ";
		gotoxy(enemyX[ind],enemyY[ind]+2); cout<<"    ";
		gotoxy(enemyX[ind],enemyY[ind]+3); cout<<"    ";
	}
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind]=1;
	genEnemy(ind);
}
void drawCar(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			gotoxy(j+carPos,i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			gotoxy(j+carPos,i+22); cout<<" ";
		}
	}
}
int collision(){
	if(enemyY[0]+4>=23){
		if(enemyX[0]+4-carPos>=0&&enemyX[0]+4-carPos<9){
			return 1;
		}
	}
	return 0;
}
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t-----------------------------"<<endl;
	cout<<"\t\t---------Game Over-----------"<<endl;
	cout<<"\t\t---------Score:"<<score<<"------------"<<endl;
	cout<<"\t\t---------獲得$:"<<score*10<<"--------"<<endl; 
	system("PAUSE");
	
}
void updateScore(){
	gotoxy(WIN_WIDTH+7,5);cout<<"分數: "<<score<<endl;
}
void instructions(){

	system("cls");
	cout<<"遊戲說明";
	cout<<"\n-----------------";
	cout<<"左右移動以避開來車";
	cout<<"\n\n按下 'a' 往左";
	cout<<"\n按下 'd' 往右";
	cout<<"\n按下 'esc' 離開";
	cout<<"\n\n按下任意鍵離開";
	getch();
}
void play(){
	carPos=-1+WIN_WIDTH/2;
	score=0;
	enemyFlag[0]=1;
	enemyFlag[1]=0;
	enemyY[0]=1;
	enemyY[1]=1; 
	system("cls");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH+7,2);cout<<"賽車遊戲";
	gotoxy(WIN_WIDTH+6,4);cout<<"----------";
	gotoxy(WIN_WIDTH+6,6);cout<<"----------";
	gotoxy(WIN_WIDTH+7,12);cout<<"控制";
	gotoxy(WIN_WIDTH+7,13);cout<<"----------";	
	gotoxy(WIN_WIDTH+2,14);cout<<"A - 往左";
	gotoxy(WIN_WIDTH+2,15);cout<<"D - 往右";
	
	gotoxy(18,5);cout<<"按下任意鍵開始";
	getch();
	gotoxy(18,5);cout<<"              ";
	
	while(1){
		if(kbhit()){
			char ch=getch();
			if(ch=='a'||ch=='A'){
				if(carPos>18)
					carPos-=4;
			}
			if(ch=='d'||ch=='D'){
				if(carPos<50)
					carPos+=4;
			}
			if(ch==27){
				break;
			}
		}
		
		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if(collision()==1){
			gameover();
			return;
		}
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);
		
		if(enemyY[0]==10)
			if(enemyFlag[1]==0)
				enemyFlag[1]=1;
		
		if(enemyFlag[0]==1)
				enemyY[0]+=1;
		
		if(enemyFlag[1]==1)
				enemyY[1]+=1;
		
		if(enemyY[0]>SCREEN_HEIGHT-4){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if(enemyY[1]>SCREEN_HEIGHT-4){
			resetEnemy(1);
			score++;
			updateScore();
		}	
	}	
}
int mainCR(){
	score=0;
	setcursor(0,0);
	srand((unsigned)time(NULL));
	char op;
	do{
		system("cls");
		gotoxy(10,5); cout<<"----------------------";
		gotoxy(10,6); cout<<"|      賽車遊戲      |";
		gotoxy(10,7); cout<<"----------------------";
		gotoxy(10,9); cout<<"1. 開始遊戲";
		gotoxy(10,10); cout<<"2. 遊戲說明";
		gotoxy(10,11); cout<<"3. 離開";
		gotoxy(10,13); cout<<"已賺$"<<score*10;
		gotoxy(10,15); cout<<"選項:";
		op=getche();
		
		if(op=='1') play();
		else if(op=='2')	instructions();
		else if(op=='3')	return (score*10);
	}while(1);
	return 0;
}
//MAIN---------------------------------------
int main(){
	mainLI();
	return 0;
}
//--------------------------------SQL Function
void update(){
	ofstream fout;
	fout.open("memberlist.txt",ios::trunc);
	fout.close();
	fout.open("memberlist.txt",ios::app);
	fout<<users.user_no<<endl;
	for(int i=0;i<users.user_no;i++){
		fout<<users.member[i].username<<endl;
		fout<<users.member[i].passwd<<endl;
		fout<<users.member[i].login_no<<endl;
		fout<<users.member[i].money<<endl;
		fout<<users.member[i].lose<<" "<<users.member[i].win<<" "<<users.member[i].tie<<endl;
	}
	fout.close();
}
void updateO(){
	ofstream fout;
	fout.open("orderlist.txt",ios::trunc);
	fout.close();
	fout.open("orderlist.txt",ios::app);
	fout<<orders.mealno<<endl;
	fout<<orders.orderno<<endl;
	for(int i=0;i<orders.orderno;i++){		
		fout<<orders.member[i].user<<endl;
		fout<<orders.member[i].meal<<endl;
		fout<<orders.member[i].no<<endl;
		fout<<orders.member[i].sw<<endl;
		fout<<orders.member[i].ice<<endl;
	}
	fout.close();
}
//--------------------------------Login Function
userlist LoadUsers(){
	int i=0;
	ifstream fin;
	fin.open("memberlist.txt");
	fin>>users.user_no;
	for(int i=0;i<users.user_no;i++){
		fin >> users.member[i].username;
		fin >> users.member[i].passwd;
		fin >> users.member[i].login_no;
		fin >> users.member[i].money;
		fin >> users.member[i].lose>>users.member[i].win>>users.member[i].tie;
 	}
	fin.close();
	return users;
}
int Login(){
	char username[13];
	char passwd[13];
	int i;
	do{
		input_username(username);
		input_password(username,passwd);
		for(i=0;i<users.user_no;i++)
		{
			if(strcmp(username,users.member[i].username)==0){
				if(strcmp(passwd,users.member[i].passwd)==0){
					users.member[i].login_no++;
					update();
					return i;
				}
				else
				{
					cout<<endl<<"Incorrect password"<<endl;
					system("PAUSE");
					input_password(username,passwd);
					i--;
					continue;
				}
			}
		}
		if(i==users.user_no){
			char passwd2[13];
			do{
				input_password2(username,passwd,passwd2);
				if(strcmp(passwd,passwd2)==0){
					users.user_no++;
					for(int j=0;j<strlen(username);j++){
						users.member[i].username[j]=username[j];
					}
					for(int j=0;j<strlen(passwd);j++){
						users.member[i].passwd[j]=passwd[j];
					}
					users.member[i].login_no=1;
					users.member[i].money=0;
					users.member[i].lose=0;
					users.member[i].win=0;
					users.member[i].tie=0;
					return i;
				}else{
					cout<<endl<<"Not same password"<<endl;
					system("PAUSE");
				}
			}while(strcmp(passwd,passwd2)!=0);
		}
	}while(true);

}
void input_username(char un[]){
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Username: ";
		for(i=0;i<n;i++)
			cout << un[i];
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				un[11] = c1;
			}
			else
			{
				un[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	un[n] = '\0';
}
void input_password(char un[],char pw[]){
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Username: ";
		cout << un << endl;
		cout << "Password: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				pw[11] = c1;
			}
			else
			{
				pw[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	pw[n] = '\0';
}
void input_password2(char un[],char pw[],char pw2[]){
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Username: ";
		cout << un << endl;
		cout << "Password: ";
		for(i=0;i<strlen(pw);i++)
			cout << '*';
		cout<<endl;
		cout << "Input Password Again: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				pw2[11] = c1;
			}
			else
			{
				pw2[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	pw2[n] = '\0';
}
int mainLI(){
	orders=LoadOrders();
	users = LoadUsers();
	user_id = Login();
	update();
	if(user_id==0){
		KEUI();
	}else{
		mainUI(user_id);	
	}
	return user_id;
}

//----------------------------MainUI Function
void MainScreen(int select,int id){
	system("cls");
	users=LoadUsers();
	int i;
	char L[9],R[9];
	for(i=0;i<9;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"    _____ _  _      ____  _       ____  ____  ____     _  _____ ____  _____ "<<endl;
	cout<<"   /    // \\/ \\  /|/  _ \\/ \\     /  __\\/  __\\/  _ \\   / |/  __//   _\\/__ __\\"<<endl;
	cout<<"   |  __\\| || |\\ ||| / \\|| |     |  \\/||  \\/|| / \\|   | ||  \\  |  /    / \\  "<<endl; 
	cout<<"   | |   | || | \\||| |-||| |_/\\  |  __/|    /| \\_/|/\\_| ||  /_ |  \\_   | |  "<<endl; 
	cout<<"   \\_/   \\_/\\_/  \\|\\_/ \\|\\____/  \\_/   \\_/\\_\\\\____/\\____/\\____\\\\____/  \\_/  "<<endl;
	cout<<endl;
	printf("-----%s您好，歡迎蒞臨可不可，您已登入第%d次，儲值金為%d元------\n",users.member[id].username,users.member[id].login_no,users.member[id].money);
	cout<<endl;
	cout <<"             "<< L[1] << "1" << R[1] << " Order" << endl;
	cout <<"             "<< L[2] << "2" << R[2] << " 查訂單" << endl;
	cout <<"             "<< L[3] << "3" << R[3] << " 修改會員資料" << endl;
	cout <<"             "<< L[4] << "4" << R[4] << " 寂寞聊天室" << endl;
	cout <<"             "<< L[5] << "5" << R[5] << " 玩數獨" << endl;
	cout <<"             "<< L[6] << "6" << R[6] << " 猜數字" << endl;
	cout <<"             "<< L[7] << "7" << R[7] << " 賽車遊戲" << endl;
	cout <<"             "<< L[8] << "8" << R[8] << " 播放音樂-千本櫻" << endl;
	cout <<"             "<< L[0] << "0" << R[0] << " 離開系統" << endl;
}
void KScreen(int select,int id){
	system("cls");
	int i;
	char L[4],R[4];
	for(i=0;i<4;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"    _____ _____ _____ _____ _____ _____ "<<endl;
	cout<<"   |  |  |   __| __  |  |  |  |  |   __|"<<endl;
	cout<<"   |    -|   __| __ -|  |  |    -|   __|  "<<endl; 
	cout<<"   |__|__|_____|_____|_____|__|__|_____|"<<endl; 
	cout<<endl;
	cout<<endl;
	cout <<"             "<< L[1] << "1" << R[1] << " 查訂單" << endl;
	cout <<"             "<< L[2] << "2" << R[2] << " 儲值" << endl;
	cout <<"             "<< L[3] << "3" << R[3] << " 播放音樂-千本櫻" << endl;
	cout <<"             "<< L[0] << "0" << R[0] << " 離開系統" << endl;
}
int KUI(int select,int id){
	char x,x1;
	do{
		KScreen(select,id);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 3)%4;
			if(x1==80)
				select = (select + 1)%4;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='3')
			select = x - '0';
	}while(x!=13);
	return select;
}
int MainUI(int select,int id){
	char x,x1;
	do{
		MainScreen(select,id);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 8)%9;
			if(x1==80)
				select = (select + 1)%9;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='8')
			select = x - '0';
	}while(x!=13);
	return select;
}
int mainUI(int id){
	int select = 1;
	do{
		select = MainUI(select,id);
		switch(select)
		{
			case 1:
				orderUI(id);
				break;
			case 2:
				mainCK(id);
				break;
			case 3:
				changePw(id);
				update();
				break;
			case 4:
				Chatroom(users.member[id].username);
				break;
			case 5:
				mainSu(id);
				update();
				break;
			case 6:
				system("cls");
				mainXAXB(id);
				update();
				break;
			case 7:
				users.member[id].money+=mainCR();
				update();
				break;
			case 8:
				ShellExecute(NULL, "open", "C:\\Users\\alexy\\Desktop\\Final Projct\\MU.exe", NULL, NULL, SW_SHOWDEFAULT);
				break;
		}
	}while(select!=0);
	return 0;
}
int KEUI(){
	int select = 1;
	int id=0;
	do{
		select = KUI(select,id);
		switch(select)
		{
			case 1:
				mainCKK();
				break;
			case 2:
				money();
				break;
			case 3:
				ShellExecute(NULL, "open", "C:\\Users\\alexy\\Desktop\\Final Projct\\MU.exe", NULL, NULL, SW_SHOWDEFAULT);
				break;
		}
	}while(select!=0);
	return 0;
}
//----------------------------Order Function
orderlist LoadOrders(){
	int i=0;
	ifstream fin;
	fin.open("orderlist.txt");
	fin>>orders.mealno;
	fin>>orders.orderno;
	for(int i=0;i<orders.orderno;i++){
		fin >> orders.member[i].user;
		fin >> orders.member[i].meal;
		fin >> orders.member[i].no;
		fin >> orders.member[i].sw;
		fin >> orders.member[i].ice;
 	}
	fin.close();
	return orders;
}
void OrderScreen(int select,int id){
	system("cls");
	int i;
	char L[5],R[5];
	for(i=0;i<5;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<" ___ ___    ___  ____   __ __ "<<endl;
	cout<<"|   |   |  /  _]|    \\||  |  |"<<endl;
	cout<<"| _   _ | /  [_ |  _  ||  |  |"<<endl; 
	cout<<"|  \\_/  ||    _]|  |  ||  |  |"<<endl; 
	cout<<"|   |   ||   [_ |  |  ||  :  |"<<endl;
	cout<<"|___|___||_____||__|__| \\__,_|"<<endl;
	cout<<endl;
	printf("-----餘額為%d元------\n",users.member[id].money);
	cout<<endl;
	cout <<" "<< L[1] << "1" << R[1] << " 紅茶   $10" << endl;
	cout <<" "<< L[2] << "2" << R[2] << " 綠茶   $10" << endl;
	cout <<" "<< L[3] << "3" << R[3] << " 酸梅   $10" << endl;
	cout <<" "<< L[4] << "4" << R[4] << " 三合一 $20" << endl; 
	cout <<" "<< L[0] << "0" << R[0] << " 離開" << endl;
}
int OrderUI(int select,int id){
	char x,x1;
	do{
		OrderScreen(select,id);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 4)%5;
			if(x1==80)
				select = (select + 1)%5;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='3')
			select = x - '0';
	}while(x!=13);
	return select;
}
int orderUI(int id){
	int meal = 1,ice=1,sw=1,no=1;
		m:
		meal=OrderUI(meal,id);
		if(meal==0){
			return 0;
		}else{
			n:
				no=orderUI1(id);
				if(no==0){
					goto m;
				}else{
					s:
					sw=orderUI2(id);
					if(sw==0){
						goto n;
					}else{
						ice=orderUI3(id);
						if(ice==0){
							goto s;
						}else{
							goto r;
						}
					}				
				}
			}
	r:
	for(int i=0;i<strlen(users.member[id].username);i++)
		orders.member[orders.orderno].user[i]=users.member[id].username[i];
	orders.member[orders.orderno].meal=meal;
	orders.member[orders.orderno].no=no;
	orders.member[orders.orderno].sw=sw;
	orders.member[orders.orderno].ice=ice;
	orders.orderno++;
	int mon=no*((meal/4)+1)*10;
	OrderScreen4(id,mon,orders.orderno-1);
	return 0;
}
int OrderUI1(int select,int id){
	char x,x1;
	do{
		OrderScreen1(select,id);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 5)%6;
			if(x1==80)
				select = (select + 1)%6;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='5')
			select = x - '0';
	}while(x!=13);
	return select;
}
int orderUI1(int id){
	int no = 1;
	no = OrderUI1(no,id);
	return no;
}
int OrderUI2(int select,int id){
	char x,x1;
	do{
		OrderScreen2(select,id);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 5)%6;
			if(x1==80)
				select = (select + 1)%6;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='5')
			select = x - '0';
	}while(x!=13);
	return select;
}
int orderUI2(int id){
	int sw = 1;
	sw = OrderUI2(sw,id);
	return sw;
}
int OrderUI3(int select,int id){
	char x,x1;
	do{
		OrderScreen3(select,id);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 5)%6;
			if(x1==80)
				select = (select + 1)%6;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='5')
			select = x - '0';
	}while(x!=13);
	return select;
}
int orderUI3(int id){
	int ice = 1;
	ice = OrderUI3(ice,id);
	return ice;
}
void OrderScreen1(int select,int id){
	system("cls");
	int i;
	char L[6],R[6];
	for(i=0;i<6;i++)
	{
		L[i]= ' ';
		R[i]= ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<" ___ ___    ___  ____   __ __ "<<endl;
	cout<<"|   |   |  /  _]|    \\||  |  |"<<endl;
	cout<<"| _   _ | /  [_ |  _  ||  |  |"<<endl; 
	cout<<"|  \\_/  ||    _]|  |  ||  |  |"<<endl; 
	cout<<"|   |   ||   [_ |  |  ||  :  |"<<endl;
	cout<<"|___|___||_____||__|__| \\__,_|"<<endl;
	cout<<endl;
	printf("-----餘額為%d元------\n",users.member[id].money);
	cout<<endl;
	cout <<"|數量|--> 甜度--> 冰塊" << endl;
	cout <<" "<< L[1] << "1" << R[1] << endl;
	cout <<" "<< L[2] << "2" << R[2] << endl;
	cout <<" "<< L[3] << "3" << R[3] << endl;
	cout <<" "<< L[4] << "4" << R[4] << endl;
	cout <<" "<< L[5] << "5" << R[5] << endl;
	cout <<" "<< L[0] << "0" << R[0] << " 回上頁" << endl;
}
void OrderScreen2(int select,int id){
	system("cls");
	int i;
	char L[6],R[6];
	for(i=0;i<6;i++)
	{
		L[i]= ' ';
		R[i]= ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<" ___ ___    ___  ____   __ __ "<<endl;
	cout<<"|   |   |  /  _]|    \\||  |  |"<<endl;
	cout<<"| _   _ | /  [_ |  _  ||  |  |"<<endl; 
	cout<<"|  \\_/  ||    _]|  |  ||  |  |"<<endl; 
	cout<<"|   |   ||   [_ |  |  ||  :  |"<<endl;
	cout<<"|___|___||_____||__|__| \\__,_|"<<endl;
	cout<<endl;
	printf("-----餘額為%d元------\n",users.member[id].money);
	cout<<endl;
	cout <<" 數量 -->|甜度|--> 冰塊" << endl;
	cout <<"          "<< L[1] << "1" << R[1] << " 無糖" << endl;
	cout <<"          "<< L[2] << "2" << R[2] << " 三分" << endl;
	cout <<"          "<< L[3] << "3" << R[3] << " 五分" << endl;
	cout <<"          "<< L[4] << "4" << R[4] << " 七分" << endl;
	cout <<"          "<< L[5] << "5" << R[5] << " 全糖" << endl;
	cout <<"          "<< L[0] << "0" << R[0] << " 回上頁" << endl;
}
void OrderScreen3(int select,int id){
	system("cls");
	int i;
	char L[6],R[6];
	for(i=0;i<6;i++)
	{
		L[i]= ' ';
		R[i]= ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<" ___ ___    ___  ____   __ __ "<<endl;
	cout<<"|   |   |  /  _]|    \\||  |  |"<<endl;
	cout<<"| _   _ | /  [_ |  _  ||  |  |"<<endl; 
	cout<<"|  \\_/  ||    _]|  |  ||  |  |"<<endl; 
	cout<<"|   |   ||   [_ |  |  ||  :  |"<<endl;
	cout<<"|___|___||_____||__|__| \\__,_|"<<endl;
	cout<<endl;
	printf("-----餘額為%d元------\n",users.member[id].money);
	cout<<endl;
	cout <<" 數量 --> 甜度-->|冰塊|" << endl;
	cout <<"                  "<< L[1] << "1" << R[1] << " 去冰" << endl;
	cout <<"                  "<< L[2] << "2" << R[2] << " 三分" << endl;
	cout <<"                  "<< L[3] << "3" << R[3] << " 五分" << endl;
	cout <<"                  "<< L[4] << "4" << R[4] << " 七分" << endl;
	cout <<"                  "<< L[5] << "5" << R[5] << " 正常" << endl;
	cout <<"                  "<< L[0] << "0" << R[0] << " 回上頁" << endl;
}
void OrderScreen4(int id,int no,int i){
	system("cls");
	cout<<" ___ ___    ___  ____   __ __ "<<endl;
	cout<<"|   |   |  /  _]|    \\||  |  |"<<endl;
	cout<<"| _   _ | /  [_ |  _  ||  |  |"<<endl; 
	cout<<"|  \\_/  ||    _]|  |  ||  |  |"<<endl; 
	cout<<"|   |   ||   [_ |  |  ||  :  |"<<endl;
	cout<<"|___|___||_____||__|__| \\__,_|"<<endl;
	cout<<endl;
		if(users.member[id].money<no){
		printf("餘額不足，您還差$%d，請儲值或玩小遊戲賺取儲值金!\n",no-users.member[id].money);
		system("PAUSE");		
	}else{
		users.member[id].money-=no;
		printf("訂單成立!您的訂單:\n\n");
		cout<<"  號碼:"<<i+1<<endl;
		cout<<"  種類:"; 
		if(orders.member[i].meal==1){
			cout<<"紅茶"<<endl;
		}else if(orders.member[i].meal==2){
			cout<<"綠茶"<<endl;
		}else if(orders.member[i].meal==3){
			cout<<"酸梅"<<endl; 
		}else if(orders.member[i].meal==4){
			cout<<"三合一"<<endl; 
		}
		cout<<"  數量:"<<orders.member[i].no<<endl;
		cout<<"  甜度:";
		if(orders.member[i].sw==1){
			cout<<"無糖"<<endl;
		}else if(orders.member[i].sw==2){
			cout<<"三分"<<endl;
		}else if(orders.member[i].sw==3){
			cout<<"五分"<<endl; 
		}else if(orders.member[i].sw==4){
				cout<<"七分"<<endl; 
		}else if(orders.member[i].sw==5){
			cout<<"全糖"<<endl; 
		}
		cout<<"  冰塊:";
		if(orders.member[i].ice==1){
			cout<<"去冰"<<endl;
		}else if(orders.member[i].ice==2){
			cout<<"三分"<<endl;
		}else if(orders.member[i].ice==3){
			cout<<"五分"<<endl; 
		}else if(orders.member[i].ice==4){
			cout<<"七分"<<endl; 
		}else if(orders.member[i].ice==5){
			cout<<"正常"<<endl; 
		}
		printf("  \n金額$%d，餘額$%d。\n",no,users.member[id].money);
		update();
		updateO();
		system("PAUSE");
	}
}
//----------------------------Check Function
int mainCKK(){
	next:
	orders=LoadOrders();
	system("cls");
	cout<<"-----------"<<endl;
	printf("目前已完成:%.2d\n",orders.mealno);
	cout<<"-----------"<<endl;
	cout<<"=====訂單====="<<endl;
	int i=orders.mealno;
	if(orders.mealno==orders.orderno){
		cout<<"\nXXX沒有訂單XXX\n\n";
		goto no; 
	}
			cout<<"  顧客:"<<orders.member[i].user<<endl; 
			cout<<"  號碼:"<<i+1<<endl;
			cout<<"  種類:"; 
			if(orders.member[i].meal==1){
				cout<<"紅茶"<<endl;
			}else if(orders.member[i].meal==2){
				cout<<"綠茶"<<endl;
			}else if(orders.member[i].meal==3){
				cout<<"酸梅"<<endl; 
			}else if(orders.member[i].meal==4){
				cout<<"三合一"<<endl; 
			}
			cout<<"  數量:"<<orders.member[i].no<<endl;
			cout<<"  甜度:";
			if(orders.member[i].sw==1){
				cout<<"無糖"<<endl;
			}else if(orders.member[i].sw==2){
				cout<<"三分"<<endl;
			}else if(orders.member[i].sw==3){
				cout<<"五分"<<endl; 
			}else if(orders.member[i].sw==4){
				cout<<"七分"<<endl; 
			}else if(orders.member[i].sw==5){
				cout<<"全糖"<<endl; 
			}
			cout<<"  冰塊:";
			if(orders.member[i].ice==1){
				cout<<"去冰"<<endl;
			}else if(orders.member[i].ice==2){
				cout<<"三分"<<endl;
			}else if(orders.member[i].ice==3){
				cout<<"五分"<<endl; 
			}else if(orders.member[i].ice==4){
				cout<<"七分"<<endl; 
			}else if(orders.member[i].ice==5){
				cout<<"正常"<<endl; 
			}
	cout<<endl<<endl;
	cout<<"按下Page Down顯示下一張訂單\n";
	no:
	cout<<"按下0離開\n";
	char x,x1;
	do{
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==81){
				orders.mealno++;
				updateO();
				goto next;
			}		
		}
	}while(x!='0');
	return 0;
}
int mainCK(int id){
	orders=LoadOrders();
	bool top=false;
	system("cls");
	cout<<"-----------"<<endl;
	printf("目前叫號:%.2d\n",orders.mealno);
	cout<<"-----------"<<endl;
	cout<<"=====已完成====="<<endl; 
	for(int i=0;i<orders.mealno;i++){
		if(strcmp(orders.member[i].user,users.member[id].username)==0){
			if(top){
				cout<<"----------------"<<endl;
			}
			cout<<"  號碼:"<<i+1<<endl;
			cout<<"  種類:"; 
			if(orders.member[i].meal==1){
				cout<<"紅茶"<<endl;
			}else if(orders.member[i].meal==2){
				cout<<"綠茶"<<endl;
			}else if(orders.member[i].meal==3){
				cout<<"酸梅"<<endl; 
			}else if(orders.member[i].meal==4){
				cout<<"三合一"<<endl; 
			}
			cout<<"  數量:"<<orders.member[i].no<<endl;
			cout<<"  甜度:";
			if(orders.member[i].sw==1){
				cout<<"無糖"<<endl;
			}else if(orders.member[i].sw==2){
				cout<<"三分"<<endl;
			}else if(orders.member[i].sw==3){
				cout<<"五分"<<endl; 
			}else if(orders.member[i].sw==4){
				cout<<"七分"<<endl; 
			}else if(orders.member[i].sw==5){
				cout<<"全糖"<<endl; 
			}
			cout<<"  冰塊:";
			if(orders.member[i].ice==1){
				cout<<"去冰"<<endl;
			}else if(orders.member[i].ice==2){
				cout<<"三分"<<endl;
			}else if(orders.member[i].ice==3){
				cout<<"五分"<<endl; 
			}else if(orders.member[i].ice==4){
				cout<<"七分"<<endl; 
			}else if(orders.member[i].ice==5){
				cout<<"正常"<<endl; 
			}
			top=true;
		}
	}
	top=false;
	cout<<endl<<endl;
	cout<<"=====製作中====="<<endl;
	for(int i=orders.mealno;i<orders.orderno;i++){
		if(strcmp(orders.member[i].user,users.member[id].username)==0){
			if(top){
				cout<<"----------------"<<endl;
			}
			cout<<"  號碼:"<<i+1<<endl;
			cout<<"  種類:"; 
			if(orders.member[i].meal==1){
				cout<<"紅茶"<<endl;
			}else if(orders.member[i].meal==2){
				cout<<"綠茶"<<endl;
			}else if(orders.member[i].meal==3){
				cout<<"酸梅"<<endl; 
			}else if(orders.member[i].meal==4){
				cout<<"三合一"<<endl; 
			}
			cout<<"  數量:"<<orders.member[i].no<<endl;
			cout<<"  甜度:";
			if(orders.member[i].sw==1){
				cout<<"無糖"<<endl;
			}else if(orders.member[i].sw==2){
				cout<<"三分"<<endl;
			}else if(orders.member[i].sw==3){
				cout<<"五分"<<endl; 
			}else if(orders.member[i].sw==4){
				cout<<"七分"<<endl; 
			}else if(orders.member[i].sw==5){
				cout<<"全糖"<<endl; 
			}
			cout<<"  冰塊:";
			if(orders.member[i].ice==1){
				cout<<"去冰"<<endl;
			}else if(orders.member[i].ice==2){
				cout<<"三分"<<endl;
			}else if(orders.member[i].ice==3){
				cout<<"五分"<<endl; 
			}else if(orders.member[i].ice==4){
				cout<<"七分"<<endl; 
			}else if(orders.member[i].ice==5){
				cout<<"正常"<<endl; 
			}
			top=true;
		}
	}
	cout<<endl<<endl;
	system("PAUSE");
	return 0; 
}
int money(){
	char un[13]; 
	char c1,c2;
	int n=0,i,j;
	int id;
	do
	{
		system("cls");
		cout << "請輸入您要找的使用者: ";
		for(i=0;i<n;i++)
			cout << un[i];
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				un[11] = c1;
			}
			else
			{
				un[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	un[n] = '\0';
	users=LoadUsers();
	for(j=0;j<users.user_no;j++){
		if(strcmp(un,users.member[j].username)==0){
			id=j;
			break;
		}
	}
	if(j==users.user_no){
		cout<<"\n查無此人\n";
		system("PAUSE");
	}else{
		char mo[6];
		n=0;i=0;
		do{
		system("cls"); 
		cout<<"使用者: "<<un<<endl;
		cout<<"儲值金: "<<users.member[id].money<<endl<<endl;
		cout<<"請輸入您想加值的金額: ";
		for(i=0;i<n;i++)
			cout << mo[i];
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='0'&&c1<='9'))
		{
			if(n==4)
			{
				mo[n] = c1;
			}
			else
			{
				mo[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
		}while(c1!=13);
		mo[n] = '\0';
		int mon=0;
		reverse(mo,mo+strlen(mo));
		for(j=0;j<strlen(mo);j++){
			mon+=(mo[j]-'0')*pow(10,j);
		}
		users.member[id].money+=mon;
		printf("\n\n加值成功\!加值了$%d，目前儲值金為:%d\n",mon,users.member[id].money);
		update();
		system("PAUSE");
		return 0;
	}
	
}
//----------------------------ChangePW Function
void changePw(int id){
	char pw[13],pw2[13],pw3[13];
	change_password(pw);
	while(strcmp(pw,users.member[id].passwd)==1){
		cout<<endl<<"Incorrect Password!"<<endl;
		system("PAUSE");
		change_password(pw);
	}
	change_password1(pw,pw2);
	change_password2(pw,pw2,pw3);
	while(strcmp(pw2,pw3)==1){
		cout<<endl<<"Not Same Password!"<<endl;
		system("PAUSE");
		change_password2(pw,pw2,pw3);
	}
	for(int i=0;i<13;i++){
		users.member[id].passwd[i]=pw3[i];
	}
	cout<<endl<<"Change Sucess!"<<endl;
	system("PAUSE");
}
void change_password(char pw[]){
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Origin Password: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				pw[11] = c1;
			}
			else
			{
				pw[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	pw[n] = '\0';
}
void change_password1(char pw[],char pw2[]){
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Origin Password: ";
		for(i=0;i<strlen(pw);i++)
			cout << '*';
		cout <<endl<< "New Password: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				pw2[11] = c1;
			}
			else
			{
				pw2[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	pw2[n] = '\0';
}
void change_password2(char pw[],char pw2[],char pw3[]){
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		cout << "Origin Password: ";
		for(i=0;i<strlen(pw);i++)
			cout << '*';
		cout <<endl<< "New Password: ";
		for(i=0;i<strlen(pw2);i++)
			cout << '*';
		cout <<endl<< "Input Password Again: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				pw3[11] = c1;
			}
			else
			{
				pw3[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	pw3[n] = '\0';
}
//----------------------------Chatroom Function
void Chatroom(char un[]){
	char talk[100];
	ifstream fin;
	ofstream fout;
	do{
		system("cls");
		fin.open("msg.txt");
		while(!fin.eof())
		{
			fin.getline(talk,99);
			cout<<talk<<endl;
		}
		fin.close();
		cout<<"---------------------------------------------"<<endl;
		cout<<un<< ": ";
		cin.getline(talk,99);
		if((strcmp(talk,"Exit")==0)|| (strcmp(talk,"exit")==0)) 
			break;
		if(strlen(talk)>0)
		{
			fout.open("msg.txt",std::ofstream::app);
			fout<<un<<": "<<talk<<endl;
			fout.close(); 
		}
	}while(true);
}
//----------------------------Sudoku Function
int mainSu(int id){
	int r,c,n,modified = 1;
	int Q[9][9];
	int A2[9][9];
	int pool[9][9][10];
	init(pool);
	Sudoku_Read(1,Q,pool);
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			map[r][c] = Q[r][c];
			A2[r][c] = Q[r][c];
		}
	cout << endl;
	MainUIS(Q,A2);
	system("cls");
	backtrace(0);
	bool Ans=true;
	for(r=0;r<9;r++)
		{
			for(c=0;c<9;c++)
			{
				if(A2[r][c]!=map[r][c]||A2[r][c]==0)
				{
					Ans=false; //0-9
					break;
				}else{					
					continue;
				}
			}
		}
	if(Ans==true){
		cout<<"Correct!"<<endl;
	}else{
		cout<<"Worng Answer!"<<endl;
	}
	users.member[id].money+=20;
	system("PAUSE");
	return 0;
}
bool isPlace(int count){
	int row = count / 9;
	int col = count % 9;
	int j;
	for(j = 0; j < 9; ++j){
		if(map[row][j] == map[row][col] && j != col){
			return false;
		}
	}
	for(j = 0; j < 9; ++j){
		if(map[j][col] == map[row][col] && j != row){
			return false;
		}
	}
	int tempRow = row / 3 * 3;
	int tempCol = col / 3 * 3;
	for(j = tempRow; j < tempRow + 3;++j){
		for(int k = tempCol; k < tempCol + 3; ++k){
			if(map[j][k] == map[row][col] && j != row && k != col){
				return false;
			}
		}
	}
	return true;
}
void backtrace(int count){
	if(count == 81){
		for(int i = 0; i < 9; ++i){
			for(int j =  0; j < 9; ++j){
				cout<<" "<<map[i][j]<<" ";
				if(j==2||j==5)
					cout <<"|";
			}
			cout<<endl;
			if(i==2||i==5)
				cout << "-----------------------------"<<endl;
		}
		return;
	}
	int row = count / 9;
	int col = count % 9;
	if(map[row][col] == 0){
		for(int i = 1; i <= 9; ++i){
			map[row][col] = i;
			if(isPlace(count)){
				backtrace(count+1);
			}
		}
		map[row][col] = 0;
	}else{
		backtrace(count+1);
	}
}
void MainUIS(int Q[][9],int A[][9]){
	int r=0,c=0;
	char c1,c2;
	do
	{
		Sudoku_Print(Q,A,r,c);
		c1 = getch();
		if(c1==-32)
		{
			c2 = getch();
			switch(c2)
			{
				case 72:
					r = (r+8)%9;
					break;
				case 75:
					c = (c+8)%9;
					break;
				case 77:
					c = (c+1)%9;
					break;
				case 80:
					r = (r+1)%9; 
					break;
			}	
		}
		if(c1>='0'&&c1<='9')
		{
			if(Q[r][c]==0)
				A[r][c] = c1-'0';
		}
	}while(c1!=13);
}
void init(int p[][9][10]){
	int r,c,n;
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
			for(n=1;n<=9;n++)
				p[r][c][n] = 1;
}
void Sudoku_Read(int Qno, int Q[][9], int p[][9][10]){
	int r,c,n,select;
	ifstream fin;
	srand(time(NULL));
	select=rand()%6;
	switch(select){
		case 0:
		case 4:
			fin.open("Q1.txt");
			break;
		case 1:
		case 5:
			fin.open("Q2.txt");
			break;
		case 2:
		case 3:
			fin.open("Q3.txt");
			break;
	}
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			fin >> n;
			Q[r][c] = n;
		}
	}
	fin.close();
}
void Sudoku_Print(int Q[][9],int A[][9],int R,int C){
	int r,c;
	system("cls");
	char left[9][9],right[9][9];
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			left[r][c] = ' ';
			right[r][c] = ' ';
		}
	if(Q[R][C]==0)
	{
		left[R][C] = '<';
		right[R][C] = '>';
	}
	else
	{
		left[R][C] = '[';
		right[R][C] = ']';
	}
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			cout<<left[r][c];
			if(A[r][c]==0)
				cout << " ";
			else
				cout << A[r][c];
			cout <<right[r][c];
			if(c==2||c==5)
				cout <<"|";
		}
		cout << endl;
		if(r==2||r==5)
			cout << "-----------------------------"<<endl;
	}
}
int Sudoku_Check(int p[][9][10],int R,int C){
	int sum=0,n,a;
	for(n=1;n<=9;n++)
	{
		sum += p[R][C][n];
		if(p[R][C][n]==1)
			a = n;
	}
	if(sum==1)
		return a;
	else
		return 0;
}
//----------------------------XAXB Function
void num2digit(int num,int digit[]){
    digit[0]=num/1000;
    digit[1]=num%1000/100;
    digit[2]=num%100/10;
    digit[3]=num%10;
}
bool isLegal(int num){
    int d[4],i,j;
    num2digit(num,d);
    for(i=0;i<3;i++){
        for(j=i+1;j<4;j++){
            if(d[i]==d[j]){
                return false;
            }
        }
    }
    return true;
}
void XAXB(int G,int A,int AB[]){
    AB[0]=0;
    AB[1]=0;
	int GD[4];
    int AD[4];
    num2digit(G,GD);
    num2digit(A,AD);
    int i,j;
    for(int i=0;i<4;i++){
        if(GD[i]==AD[i]){
            AB[0]++;
        }
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(GD[i]==AD[j]){
                AB[1]++;
            }
        }
    }
    AB[1]-=AB[0];
}
int mainXAXB(int id){
    int comG,comA,userG,userA,comAB[2],userAB[2],tempAB[2],count=0;
    srand(time(NULL));
    do{
        comA=rand()%10000;
        //cout<<comA<<endl;
    }while(isLegal(comA)==false);
    do{
       	cout<<"Please input your answer:";
        cin>>userA;
    }while(isLegal(userA)==false);
    int pool[10000];
    int i;
    for(i=0;i<10000;i++){
        if(isLegal(i)){
            pool[i]=1;
        }else{
            pool[i]=0;
        }
    }
    printf("%.4d\n",comA);
    do{
        for(i=0;i<10000;i++){
            if(pool[i]==1){
                break;
            }
        }
        comG=i;
        XAXB(comG,userA,comAB);
        do{
       		cout<<"Please input your guess:";
        	cin>>userG;
    	}while(isLegal(userG)==false);
        XAXB(userG,comA,userAB);
        count++;
        printf("(%d)USER:%.4d    %dA%dB\n",count,userG,userAB[0],userAB[1]);
        printf("    COM:%.4d    %dA%dB\n",comG,comAB[0],comAB[1]);
        //cout<<"("<<comG<<")"<<comG<<"    "<<comAB[0]<<"A"<<comAB[1]<<"B\n";
        for(i=0;i<10000;i++){
            if(pool[i]==1){
                XAXB(comG,i,tempAB);
                //cout<<tempAB[0]<<" "<<tempAB[1]<<endl;
                if(tempAB[0]!=comAB[0]||tempAB[1]!=comAB[1]){
                    pool[i]=0;
                }
            }
        }
        if(userAB[0]==4&&comAB[0]==4){
        	cout<<"  TIE!"<<endl;
        	users.member[id].money+=10;
        	users.member[id].tie++;
			break;
		}else if(comAB[0]==4){
			cout<<"  COM WIN!"<<endl;
			users.member[id].lose++;
			break;
		}else if(userAB[0]==4){ 
			cout<<"  USER　WIN!"<<endl;
			users.member[id].money+=20;
			users.member[id].win++;
			break;
		}
    }while(true);
    cout<<"WIN: "<<users.member[id].win<<" /LOSE: "<<users.member[id].lose<<" /TIE: "<<users.member[id].tie<<endl;
    system("PAUSE");
    return 0;
}

 
