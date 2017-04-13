#include<cstdio>
#define Nmax 1010
int num[Nmax];
int det[Nmax];
int main(){
	int n,count = 0;
	while(~scanf("%d",&n) ){
	
		for(int i = 0; i < n; i++){
			scanf("%d",&num[i]);
		}
		for(int j = 1;j < n;j++){
			det[j] = num[j] - num[j-1];
		}
		for(int k = 1;k+1 < n;k++){
			if(det[k] *det[k+1] < 0) count++;
		}
		printf("%d\n",count);
	}
}
