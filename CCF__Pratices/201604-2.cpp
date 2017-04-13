#include<cstdio>
int num[20][20];
int egnum[10][10];
bool is_hold(int,int);
void change(int ,int);
int main(){
	int col,xx = 0;
	for(int i = 1;i < 16;i++){
		for(int j = 1;j < 11; j++ )
			scanf("%d",&num[i][j]);
	}
	for(int j = 1;j < 11;j++)  
		num[16][j] = 1; //最后一行模拟阻塞 
	
	
	for(int i = 1;i < 5;i++){
		for(int j = 1;j < 5;j++)
			scanf("%d",&egnum[i][j]);
	}
	scanf("%d",&col);
	//仿真,以左上角为基准坐标 
	for(int i = 1;i <= 15;i++){
		//一定会阻塞 
		if( is_hold(i,col)){ 
			xx = i;
			break;	
		}	
	} 
	
	change(xx,col);
	
	for(int i = 1;i < 16;i++){
		for(int j = 1;j < 11; j++ ){			
			if( j < 10){
				printf("%d ",num[i][j]);
			}else{
				printf("%d\n",num[i][j]);
			}
		}
	}
	
	
		
}

bool is_hold(int x,int y){
	int sum = 0;
	for(int i = 1;i < 5;i++){
		for(int j = 1;j < 5;j++){
			sum += (egnum[i][j] * num[x+i][y+j-1]);
		}
	}
	if(sum > 0){
		return true;
	}else{
		return false;
	}
}
void change(int x,int y){
	for(int i = 1;i < 5;i++){
		for(int j = 1;j < 5;j++){
		 num[x+i-1][y+j-1] += egnum[i][j];
		}
	}
}
