#include<iostream>
#include<string>
char html[110][110];
using namespace std;
int main(){
	string line;
	int cnt = 1;
	bool pra_flag = false;
	bool rand_flag = false;
	bool last_flag = false;
	while(getline(cin,line)){
		//空行 
		if(line.size() == 0){
			pra_flag = true;
			if(last_flag == true){
				string hh = html[cnt-1];
				hh.erase(hh.size()-1,1);
				hh = hh+"</p>"+'\n';
				strcpy(html[cnt-1],hh.c_str());
				last_flag = false;
			}
			
			if(rand_flag == true){
				string hh = "</ul>\n";
				strcpy(html[cnt++],hh.c_str()); 
				rand_flag = false;
			}
			continue;
		}
		//标题 
		if(line[0] == '#'){
			int rank = 1;
			while(line[rank] == '#')
				rank++;
			
			int sep = rank;
			rank = (rank > 6 ? 6:rank);
			
			while(line[sep] == ' ')
				sep++;
				
			string heading = line.erase(0,sep);
			string hh = "";
			char c = rank + '0';
			heading = hh+"<h" + c +">"+heading +"</h"+c+">"+ '\n'; 
			strcpy(html[cnt++],heading.c_str());
		
			continue;
		}
		//无序列表
		if(line[0] == '*'){
			if(rand_flag == false){//第一行要加上<ul>
				string hh = "<ul>\n";
				strcpy(html[cnt++] , hh.c_str() );
				rand_flag = true;
			}
			
			int i = 1;
			while(line[i++] == ' ') ;
			
			string hh = "";
			line.erase(0,i-1);			
			line = hh+"<li>" + line +"</li>"+"\n";
			
			strcpy(html[cnt++],line.c_str());
			continue;
		} 
		//段落首行 
		if( pra_flag == true){
			string hh = "<p>"; 
			line = hh+line;
			pra_flag = false;
			last_flag = true;
		}
		//强调	
		int t = line.find('_',0);
		while(t != string::npos){
			int tt = line.find('_',t+1);
			string hh = "<em>";
			for(int i = t+1;i < tt;i++){
				hh += line[i];
			}
			hh = hh + "</em>";
			line.erase(t,tt-t+1);
			line.insert(t,hh);
			cout<<line<<endl;
			t = line.find('_',t);
		}
		//超级链接
		t = line.find('[',0);
		while(t != string::npos){
			int tt = line.find(']',t+1);
			string Text = "";
			for(int i = t+1;i < tt;i++){
				Text+=line[i];
			}
			int xt = line.find('(',tt+1);
			int xtt = line.find(')',xt+1);
			string Link = "";
			for(int i = xt+1;i < xtt;i++){
				Link+=line[i];
			}
			
			string hh = "";
			hh = hh+"<a href=\""+Link+"\">"+Text+"</a>";	
			line.erase(t,xtt-t+1);
			line.insert(t,hh);
			
			t = line.find('[',0);
			
		} 
		
		line += "\n";
		strcpy(html[cnt++],line.c_str());
			
	}
	
	
	for(int i = 1;i < cnt;i++){
		cout<<html[i];
	}
	
		
	return 0;
} 







