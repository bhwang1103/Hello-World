#include<stdio.h>
#include<string.h>
using namespace std;

typedef struct priv{
	char category[35];
	bool islevel;
	int level;
}priv;

typedef struct role{
	int num_cate;
	char role_name[35];
	priv role_cate[12];
}role;

typedef struct user{
	int num_role;
	int num_priv;
	char user_name[35];
	role user_role[12];
	priv user_priv[102];
}user;
priv p[102];
role r[102];
user u[102];
int main(){
	int pp,rr,uu,qq;
	char *q;
	char temp[35];

	scanf("%d",&pp);
	for(int i = 0;i < pp;i++){
		getchar();
		scanf("%s",temp);
		//是否为有权值的权限 
		if( (q = strrchr(temp,':') ) != NULL){
			p[i].islevel = true;
			strncpy(p[i].category,temp,q-temp);
			p[i].level = temp[q-temp+1] - '0'; 
		}else{
			p[i].islevel = false;
			strcpy(p[i].category,temp);
			p[i].level = -1;
		}
		
	}	

	scanf("%d",&rr);
	for(int i = 0;i < rr;i++){
		int num;
		getchar();
		scanf("%s",&r[i].role_name);
		scanf("%d",&num);
		r[i].num_cate = num;
		for(int j = 0;j < num;j++){
			getchar();
			scanf("%s",temp); 
			if( (q = strrchr(temp,':') ) != NULL){
				r[i].role_cate[j].islevel = true;
				strncpy(r[i].role_cate[j].category,temp,q-temp);
				r[i].role_cate[j].level = temp[q-temp+1] - '0'; 
			}else{
				r[i].role_cate[j].islevel = false;
				strcpy(r[i].role_cate[j].category,temp);
				r[i].role_cate[j].level = -1;
			}
		}	
	}
	
	scanf("%d",&uu); 
	for(int i = 0;i < uu;i++){
		int num;
		getchar();
		scanf("%s",&u[i].user_name);
		scanf("%d",&num);
		u[i].num_role = num;
		for(int j = 0;j < num;j++){
			getchar();
			scanf("%s",temp); 
			//将角色结构赋给人，而不只是姓名 
			for(int jj = 0;jj < rr;jj++){
				if( strcmp(temp,r[jj].role_name) == 0  ){
					u[i].user_role[j] = r[jj];
					break;
				}
			}
			
		}
		//下面对user进行预处理
		int xxxk = 0;
		for(int k = 0; k < num;k++){
			int jup = u[i].user_role[k].num_cate;
			//*****debug
			//printf("jup = %d",jup); 
			
			for(int j = 0;j < jup;j++){
				//检查当前权限是否存在过
				char xxxtemp[35] ;
				strcpy (xxxtemp,u[i].user_role[k].role_cate[j].category);
				//********debug
				//printf("%s\n",xxxtemp);
				
				bool xxxflag = false; 
				for(int kj = 0;kj < xxxk;kj++){
					if(strcmp(u[i].user_priv[kj].category,   xxxtemp) == 0){
						//的确存在过,改成最大的
						xxxflag = true;
						if(u[i].user_priv[kj].level < u[i].user_role[k].role_cate[j].level){
							u[i].user_priv[kj].level = u[i].user_role[k].role_cate[j].level;
						} 
					}
							 
				
				}
				
				if(xxxflag == false){
					u[i].user_priv[xxxk++] = u[i].user_role[k].role_cate[j];
				}
				
				
			}
		}
		
		u[i].num_priv = xxxk;
				
	}

	
	scanf("%d",&qq);
	char tempName[35];
	char tempCate[35];
	user tempUser;
	bool qqflag;
	bool qqislevel;
	int qqlevel;
	for(int i = 0;i < qq;i++){
		getchar();
		scanf("%s %s",tempName,tempCate);
		qqflag = false;
		qqislevel = false;
		qqlevel = -1;
			if( (q = strrchr(tempCate,':') ) != NULL){
				qqislevel = true;
				qqlevel = temp[q-temp+1] - '0'; 
				tempCate[q-tempCate] = '\0';		
			}
		
		for(int j = 0;j < uu;j++){
			if( strcmp(u[j].user_name,tempName) == 0){
				tempUser = u[j];		
				for(int k = 0;k < tempUser.num_priv;k++){
					if(strcmp(tempUser.user_priv[k].category,tempCate) == 0){
						if(tempUser.user_priv[k].islevel == true){
							if(qqislevel == true){
								if(qqlevel <=  tempUser.user_priv[k].level){
									printf("true\n");
									qqflag = true;
								}
							}else{
								printf("%d\n",tempUser.user_priv[k].level);
								qqflag = true;
							}
							}else{
							printf("true\n");
							qqflag = true;
						}
					}
				}
				
				break;
			}
			
		}
		if(qqflag == false){
			printf("false\n");
		}
		
	}
		
}
