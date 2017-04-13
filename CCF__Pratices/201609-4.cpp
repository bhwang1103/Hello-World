//priority_queue--dijstra 
#include<cstdio>
#include<vector>
#include<queue>
#include<utility>
#define Nmax 10010
using namespace std;
struct Edge{
	int nextNode;
	int cost;
};
typedef pair<int,int> P;
vector<Edge> edge[Nmax];
priority_queue< P,vector<P>,greater<P> > pq;
int dis[Nmax];
int ec[Nmax];//存的是加入最小点时对应的边代价

void dijstra(int);
int main(){
	int n,m,a,b,c;
	while (~scanf("%d %d",&n,&m) ){
		for(int i = 1;i <= n;i++) edge[i].clear();
		
		while(m--){
			scanf("%d %d %d",&a,&b,&c);
			Edge tmp;
			tmp.cost = c;
			tmp.nextNode = b;
			edge[a].push_back(tmp);
			tmp.nextNode = a;
			edge[b].push_back(tmp);
		}
		dijstra(n);
			
	}
	
} 

void dijstra(int n){
	//初始化
	for(int i = 1;i <= n;i++) dis[i] = 123123123,ec[i] = 0;
	
	dis[1] = 0;
	while(!pq.empty()) pq.pop();
	
	pq.push(P(0,1));
	//松弛边
	
	while(!pq.empty()){
		P p = pq.top(); 
		pq.pop();
		//first为代价 second为编号 
		if(dis[p.second] < p.first) continue;
		
		dis[p.second] = p.first;
		int i_max = edge[p.second].size();
		for(int i = 0;i < i_max;i++){
			int ne = edge[p.second].at(i).nextNode;
			int cc = edge[p.second].at(i).cost;
			
			if(dis[ne] >  dis[p.second]+ cc || dis[ne] == dis[p.second]+ cc  && cc < ec[ne] ){
				dis[ne] = dis[p.second]+cc;
				ec[ne] = cc;
				pq.push( P(dis[ne],ne) );
			}
			
			
		}
		
		
	} 
	
	long sum = 0;
	for(int i = 1;i <= n;i++){
		sum += ec[i];	
	}	
	printf("%ld\n",sum);

}
