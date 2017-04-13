#include<stdio.h>

int main(){
	int n,temp;
	int seats[21];
	for(int i = 0;i < 20;i++) seats[i] = 5;	
	
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		scanf("%d",&temp);
		
		for(int j = 0;j < 20;j++){
			if(seats[j] >= temp){
				for(int k = 1; k < temp + 1;k++){
					if(k == temp){
						printf("%d\n",(j+1)*5 - seats[j] + k);	
					}
					else{
						printf("%d ",(j+1)*5 - seats[j] + k);
					}
				}
				seats[j] -= temp;	
				break;
			}
		}
		
		
	}
} 










