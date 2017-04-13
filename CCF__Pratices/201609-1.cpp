#include<stdio.h>

int num[1010];
int res[1011];

int main(){
	int n,temp,max;
	while(scanf("%d",&n) != EOF){
		for(int i = 0;i < n;i++){
			scanf("%d",&num[i]);	
		}
		for(int j = 1;j < n;j++){
			
			temp = num[j]-num[j-1]; 
			res[j] = temp > 0 ? temp : -temp;
		}
		max = 0;
		for(int k = 1;k < n;k++){
			max = (res[k] > max ? res[k] : max);
		}
		printf("%d\n",max);
		
		
	}




} 













