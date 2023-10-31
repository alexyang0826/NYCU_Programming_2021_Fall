#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(){

string s1,s2,s3;
stringstream ss;
cin>>s1>>s2;

s3=s1+s2;
//cout<<s3;
while(s3.length()>1){

int n=0;
//cout<<s3;
for(int i=0;i<s3.length();i++){
n+=int(s3[i]-'0');
//cout<<n<<" ";
}
ss.clear();
ss.str("");
ss<<n;
ss>>s3;
}
//cout<<(s3[0]-'0')/2;
switch((s3[0]-'0')/2){
		case 0:
			cout<<"¦ã³s¡P¸­¥d & ¦Ì¥d²ï¡Pªü¥d°Ò";
			break;
		case 1:
			cout<<"µæ¤ëÎö & ·R»e²ú¶®";
			break;
		case 2:
			cout<<"²L¤«´f & ¬KÔÃ¬üªÅ";
			break;
		case 3:
			cout<<"Batman & Robin";
			break;
		case 4:
			cout<<"Trump & Xi^";
			break;
	} 

return 0;

}
