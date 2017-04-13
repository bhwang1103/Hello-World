#include<stdio.h>
int main(){
	bool flag;
	int n,temp;
	int a[1010],sum[1010];
	while(scanf("%d",&n) != EOF){
		for(int i = 0;i < 1011;i++){
			a[i] = 0;
			sum[i] = 0;
		}
		for(int i = 0;i < n ; i++){
			scanf("%d",&temp);
			a[temp]++;
		}
		for(int i = 0;i < 1010;i++){
			sum[i+1] = sum[i] + a[i+1];
		}	
		
		flag = false;
		for(int i = 0;i < 1010;i++){
			if((a[i] > 0) && (sum[i-1] == sum[1005] - sum[i]) ){
				printf("%d\n",i);
				flag = true;
				break;
			}
		}
		if(flag == false){
			printf("-1\n");
		}
		
		
	}
		
} 
