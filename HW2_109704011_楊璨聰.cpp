/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
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
int main()
{
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
    cout<<comA;
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
        	cout<<"¥­¤â";
			break;
		}else if(comAB[0]==4){
			cout<<"COM WIN!";
			break;
		}else if(userAB[0]==4){ 
			cout<<"USER¡@WIN!";
			break;
		}
        //system("PAUSE");
    }while(true);
    return 0;
}

