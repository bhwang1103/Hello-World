//smart patient 
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
void mygetline(char *);
char sr[1010];
char ss[1010];
int main(){
	int n,t;
	string line,root;
	cin>>n>>root;
	getchar();	
	while(n--){ 
		mygetline(ss);
		line = ss;
		//处理非根目录路径
		if(line[0] != '/')
			line = '/' + root +'/'+line;
		
		//处理../
		t = line.find("/../",0);
		while(t != string::npos){
			if(t == 0){
				line.erase(0,3);	
			}else{
				int spos = line.rfind('/',t-1);
				line.erase(spos,t-spos+3);
			}
			t = line.find("/../",0);
		}
		//除掉多余的//
		t = line.find("//",0);
		while(t != string::npos){
			int len = 1;
			while( line[t+len] == '/')	len++; 
			line.erase(t+1,len-1);
			
			t = line.find("//",0);
		} 
		//消掉'./' 
		t = line.find("/./",0);
		while(t != string::npos){
			line.erase(t,2);
			t = line.find("/./",0);
		}
		int size = line.size();
		if(size != 1 && line[size-1] == '/'){
			line.erase(size-1,1);
		}
		
		cout<<line<<endl;
			
	}	
	
}


void mygetline(char *s){
	char c;
	while( (c = getchar() ) != EOF && c != '\n'){
		*s++ = c;
	}
	*s = '\0';
}
