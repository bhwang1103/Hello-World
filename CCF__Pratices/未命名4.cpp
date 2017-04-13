	scanf("%d",&rr);
	for(int i = 0;i < rr;i++){
		
	}
	
	scanf("%d",&uu);
	for(int i = 0;i < uu;i++){
		
	}
	
	scanf("%d",&qq);
	for(int i = 0;i < qq;i++){
		
	}
	
	
	//¼ì²é
	
		for(int i = 0;i < rr;i++){
		printf("%s ",r[i].role_name);
		for(int j = 0;j < r[i].num_cate;j++){
			printf("%s ",r[i].role_cate[j].category);
			if(r[i].role_cate[j].islevel == true){
				printf("%d",r[i].role_cate[j].level);
			}
		}
		printf("\n");
	}
	 
	 
	 	
	
		//¼ì²é
	
		for(int i = 0;i < uu;i++){
		printf("%s ",u[i].user_name);
		for(int j = 0;j < u[i].num_priv;j++){
			printf("%s %d\n",u[i].user_priv[j].category,u[i].user_priv[j].level);
		}
		printf("\n");
	}
	
