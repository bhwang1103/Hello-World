//Dijkstra
#include<cstdio>
#include<vector>
#define Nmax 10010
using namespace std;
struct Edge{
	int nextNode;
	int cost;
};
vector<Edge> edge[Nmax];
bool mark[Nmax];
int dis[Nmax];
int ec[Nmax];
void dijkstra(int N);
int main(){
	int N,M,a,b,cost;
	while( scanf("%d%d",&N,&M) &&(N != 0) ){
		//ͼ�ĳ�ʼ�� 
		for (int i = 1;i <= N;i++) edge[i].clear();
		
		for(int i = 0;i < M ;i++){
			scanf("%d %d %d",&a,&b,&cost);
			Edge tmp;	
			tmp.nextNode = b;
			tmp.cost = cost;
			edge[a].push_back(tmp);
			tmp.nextNode = a;
			edge[b].push_back(tmp);	
		}
		dijkstra(N);
		
	//	printf("%d\n",dis[N]);	
		
			
	} 
	
};

void dijkstra(int N){
	for(int i = 1; i <= N;i++) mark[i] = false,dis[i] = 200000,ec[i] = 0;
	
	dis[1] = 0;
	int min_dis = 100000,min_id = 1;
	for(int k = 1; k <= N;k++){
		//�ҳ���ǰ�ľ�����С��
		//�����öѽ����Ż� 
		min_dis = 100000;
		for(int i = 1;i <= N;i++){
			if(mark[i] == false){//���·����û��ȷ���ĵ� 
				if(dis[i] < min_dis){
					min_dis = dis[i];
					min_id = i;
				}
			}
		}
		//���ý��������·����
		mark[min_id] = true;
		
		//����Ա߽����ɳ�
		for(int j = 0;j < edge[min_id].size();j++){
			if ( (mark [edge[min_id][j].nextNode] == false) &&
				(dis [edge[min_id][j].nextNode ] > edge[min_id][j].cost +dis[min_id])){
				
				dis [edge[min_id][j].nextNode ] = edge[min_id][j].cost +dis[min_id];
				ec[edge[min_id][j].nextNode] = edge[min_id][j].cost;
			}
			
		}
		
		
		 
	}
	long sum = 0;
	for(int i = 1;i <= N;i++){
		sum += ec[i];
	}
	printf("%ld\n",sum);
	
}

