#include<stdio.h>
double pre(double T); 
int main(){
	double T;
	while(scanf("%lf",&T) != EOF){
		printf("%d\n",(int)pre(T));
	}	
} 

double pre(double T){
	double result = 0;
	if(T <= 3500){
		result = T;
	}else if( T <= 4955){
		result = (T-3500)/0.97 + 3500;
	}else if(T <= 7655){
		result = (T - 4955)/0.9 + 5000;
	}else if(T <= 11255){
		result = (T - 7655)/0.8 + 8000;
	}else if(T <= 30755){
		result = (T-11255)/0.75 + 12500;
	}else if(T <= 44755){
		result = (T - 30755)/0.7 + 38500;
	}else if(T <= 63505){
		result = (T - 44755)/0.65 + 58500;
	}else if(T > 63505){
		result = (T - 63505)/0.55 + 83500;
	}
	
	return result;
}
