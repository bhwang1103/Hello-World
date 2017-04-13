#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef struct SuiCong{
	int xl;
	int gjz;
	int wz;
}SuiCong;
SuiCong firstSc[10],lastSc[10];

int firstHero = 30;
int lastHero = 30;

bool cmp(SuiCong sc1,SuiCong sc2){
	return sc1.wz < sc2.wz;
}
int main(){
	//num1 num2 ָ���ǵ�ǰ��ӵ����� 
	int n,num1 = 0,num2 = 0;
	int attacker,defender;
	//���ֱ�־ 
	bool flagFirst = true;
	bool flagEnd = false;
	bool firstWin = false;
	//
	char caozuo[10];
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		//��ָ��
		if(flagFirst == true ){
			//���ַ�
			getchar();
			scanf("%s",&caozuo);
			if(strcmp(caozuo,"summon") == 0 ){
				//�ٻ���Ӳ��� 
				num1++;
				scanf("%d",&firstSc[num1].wz);
				scanf("%d",&firstSc[num1].gjz);
				scanf("%d",&firstSc[num1].xl);
				//���洦�����λ�ó�ͻ�����
				for(int j = 1;j < num1;j++){
					if(firstSc[num1].wz <= firstSc[j].wz){
						firstSc[j].wz++;
					}
				}
				
				sort(firstSc+1,firstSc+num1+1,cmp); 
			
			}else if(strcmp(caozuo,"attack") == 0){
				//�������� 
				scanf("%d",&attacker);
				scanf("%d",&defender);
				if(defender == 0){
					//����Ӣ��
					lastHero -= firstSc[attacker].gjz;
					if(lastHero <= 0){
						flagEnd = true;
						firstWin = true; 
					} 
				}else{
					//�����Է����
					firstSc[attacker].xl -= lastSc[defender].gjz;
					lastSc[defender].xl -= firstSc[attacker].gjz;
					if(firstSc[attacker].xl <= 0){
						//�����������
						for(int j = 1;j < num1+1;j++){
							if(firstSc[j].wz > firstSc[attacker].wz){
								firstSc[j].wz--;
							}
						}
						firstSc[attacker].wz = 10000;
						sort(firstSc+1,firstSc+num1+1,cmp);
						num1--;	 
					}
					if(lastSc[defender].xl <= 0){
						//�Է�������� 
							for(int j = 1;j < num2+1;j++){
							if(lastSc[j].wz > lastSc[defender].wz){
								lastSc[j].wz--;
							}
						}
						lastSc[defender].wz = 10000;
						sort(lastSc+1,lastSc+num2+1,cmp); 
						num2--;	 
						
					}
					
					 
				}
				
				
				
					
			}else if(strcmp(caozuo,"end") == 0){
				//�������� 
				flagFirst = false;
			}
			
		}else{
			//���ַ� 
			getchar();
			scanf("%s",&caozuo);
			if(strcmp(caozuo,"summon") == 0 ){
				//�ٻ���Ӳ��� 
				num2++;
				scanf("%d",&lastSc[num2].wz);
				scanf("%d",&lastSc[num2].gjz);
				scanf("%d",&lastSc[num2].xl);
				//���洦�����λ�ó�ͻ�����
				for(int j = 1;j < num2;j++){
					if(lastSc[num2].wz <= lastSc[j].wz){
						lastSc[j].wz++;
					}
				}
			
				
				sort(lastSc+1,lastSc+num2+1,cmp); 
				
			
			
			}else if(strcmp(caozuo,"attack") == 0){
				//�������� 
				scanf("%d",&attacker);
				scanf("%d",&defender);
				if(defender == 0){
					//����Ӣ��
					firstHero -= lastSc[attacker].gjz;
					if(firstHero <= 0){
						flagEnd = true;
						firstWin = false; 
					} 
				}else{
					//�����Է����
					lastSc[attacker].xl  -= firstSc[defender].gjz;
					firstSc[defender].xl -= lastSc[attacker].gjz;
				
					if(lastSc[attacker].xl <= 0){
						//�����������
						for(int j = 1;j < num2+1;j++){
							if(lastSc[j].wz > lastSc[attacker].wz){
								lastSc[j].wz--;
							}
						}
						lastSc[attacker].wz = 10000;
						sort(lastSc+1,lastSc+num2+1,cmp);
						num2--;	 
					}
					if(firstSc[defender].xl <= 0){
						//�Է�������� 
							for(int j = 1;j < num1+1;j++){
							if(firstSc[j].wz > firstSc[defender].wz){
								firstSc[j].wz--;
							}
						}
						firstSc[defender].wz = 10000;
						sort(firstSc+1,firstSc+num1,cmp);
						num1--;	 
						
					}
					
					 
				}
				
				
				
				
					
			}else if(strcmp(caozuo,"end") == 0){
				//�������� 
				flagFirst = true;

			}
			
				
			
			
			
			
		}
				
	}	
	
	//����ı�׼���
	if(flagEnd == true){
		if(firstWin == true){
			printf("1\n");
		}else{
			printf("-1\n");
		}
	}else{
		printf("0\n");
	}
	
	printf("%d\n%d",firstHero,num1);
	for(int k = 1;k < num1+1;k++){
		if(k == num1){
			printf(" %d\n",firstSc[k].xl);
		}else{
			printf(" %d",firstSc[k].xl);
		}
	}
		
	
	printf("%d\n%d",lastHero,num2);
	for(int k = 1;k < num2+1;k++){
		if(k == num2){
			printf(" %d\n",lastSc[k].xl);
		}else{
			printf(" %d",lastSc[k].xl);
		}
	}	
} 
