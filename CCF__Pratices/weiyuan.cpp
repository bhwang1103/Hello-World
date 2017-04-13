#include "StdAfx.h" #include "afxwin.h" #include <windows.h> #include "QTH9054fun.h" #include <iostream>
#ifdef _DEBUG #define new DEBUG_NEW #undef THIS_FILE static char THIS_FILE[] = __FILE__; #endif
CWinApp theApp; using namespace std; void Init8254(){ ULONG adr8254=0x00; ULONG adr,dat;
adr=adr8254+3;//选计数器 0 作为时钟发生器 dat=0x37; IO8bWrite(adr,dat); adr=adr8254; dat=0x32;//32 分频 IO8bWrite(adr,dat); dat=0; IO8bWrite(adr,dat);
adr=adr8254+3;//选计时器 1 作为秒表计数器
dat=0x77; IO8bWrite(adr,dat); adr=adr8254+1; dat=0x10; IO8bWrite(adr,dat); dat=0x00; IO8bWrite(adr,dat);
}
void Init8255(){ ULONG adr8255=0x20; ULONG adr,dat; adr=adr8255+3; dat=0x88; IO8bWrite(adr,dat); IO8bWrite(adr8255+2,0xff); }
void Player(int h,int n){//报时模块 int t=h*10+n; for( int i = 0; i < t; i++){ Beep(500,500); Sleep(500); } }
int w=-1,x=-1,y=-1,z=-1;//闹钟变量 int h=0,n=9,m=5,l=9,shiqu=0,ii=0;//初始时间变量时区 int clk_flag = 0;//定时开关
void Clock(){//设置定时部分 Beep(500,500); cout <<"请输入指定时间(x x x x):"<<endl; cin >>w>>x>>y>>z; clk_flag = 1; }
void Second(){//秒表计时 ULONG wei4[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //0 1 2 3 4 5 6 7 8 9 ULONG adr8255=0x20; ULONG adr,dat; int i=0,j=0,l=0,m=0,n=0; while(1){ int key; int key1; int state; while((state=IO8bRead(0x60)&(0x04))==0x00){
adr=adr8255+1; dat=0x80; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[n]; IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x40;
IO8bWrite(adr,dat); adr=adr8255; dat=wei4[m]-0x80; IO8bWrite(adr,dat); Sleep(1); if(state==1) break; adr=adr8255+1; dat=0x20; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x10; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[i]; IO8bWrite(adr,dat); Sleep(1);
} j++; while((state=IO8bRead(0x60)&(0x04))==0x04){ key=IO8bRead(adr8255+2)&(0x80); key1=IO8bRead(adr8255+2)&(0x40);
adr=adr8255+1; dat=0x80; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[n]; IO8bWrite(adr,dat); adr=adr8255+1; dat=0x40; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[m]-0x80; IO8bWrite(adr,dat); Sleep(1); if(state==0) break; adr=adr8255+1; dat=0x20; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); adr=adr8255+1; dat=0x10; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[i]; IO8bWrite(adr,dat);
} j++; if(j==2 && key==0){ i += 10; j=0;
} if(j==2){ j=0; } if(i==10){ i=0; l++; } if(l==10){ l=0; m++; } if(m==10){ n++; m=0; } if(n==10){ n=0; }
if(key1==0) break;
}
}
void shiqubiao(){ cout<<endl<<endl<<"当前时区为："<<shiqu<<"时区"<<endl; cout<<"请输入您需要查询的时区"<<endl; cout<<"时区/地区"<<endl; cout<<"UTC 英国       +1 法国        +2 希腊       +3 莫斯科"<<endl; cout<<"+4 阿联酋      +5 巴基斯坦    +6 哈萨克斯坦 +7 泰国"<<endl; cout<<"+8 中国        +9 日本        +10 关岛      +11 所罗门群岛"<<endl; cout<<"+12 新西兰     +13 萨摩亚群岛 +14 圣诞岛"<<endl; cout<<"-1 佛得角群岛  -2 世界时      -3 巴西       -4 圣地亚哥"<<endl; cout<<"-5 东部时间    -6 中部时间    -7 山地时间   -8 太平洋时间"<<endl; cout<<"-9 阿拉斯加    -10 夏威夷     -11 世界时-11 -12 日期变更线西"<<endl; int opt,shi; cin >> opt; shi = (h*10 + n - shiqu + opt + 24)%24;
shiqu = opt; h = shi / 10; n = shi % 10; cout<<h<<" "<<n<<endl;
} void shizhong(){ ULONG adr8254=0x00; ULONG adr8255=0x20; ULONG adrisd=0x40; ULONG adr,dat; ULONG wei4[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int j=0,k1=0,k=0,k2=0,k3=0,key2,key3,key4,key5; while(1){ if(!(IO8bRead(adr8255+2)&(0x20))) break; while((IO8bRead(0x60)&(0x02))==0x00) {
//显示时分模块 //位选信号通过 B 高位端口 //显示数字信号通过 A 端口 adr=adr8255+1; //数码 1 dat=0x80;      IO8bWrite(adr,dat); adr=adr8255; dat=wei4[h]; IO8bWrite(adr,dat); Sleep(1);
adr=adr8255+1; //数码 2 dat=0x40; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[n]; IO8bWrite(adr,dat); Sleep(1);
adr=adr8255+1;//数码 3 dat=0x20; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[m]; IO8bWrite(adr,dat); Sleep(1);
adr=adr8255+1;//数码 4 dat=0x10; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); Sleep(1);
} cout<<h<<n<<m<<l<<ii<<endl; j++;//低电平判定 while((IO8bRead(0x60)&(0x02))==0x02){ //通过 C 端口获取 Key key2=IO8bRead(adr8255+2)&(0x80); key3=IO8bRead(adr8255+2)&(0x40); key4=IO8bRead(adr8255+2)&(0x10); key5=IO8bRead(0x60)&(0x08);
adr=adr8255; dat=0x80; IO8bWrite(adr,dat); adr=adr8255+1; dat=0x80; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[h];
IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x40; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[n]-0x80;//点是亮的 IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x20; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[m]; IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x10; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); Sleep(1);
} j++;//高电平判定 //时钟自我调整部分 if(j==2){//满足则加 i ii++; j=0; } if(ii==60){//分钟计时个位 ii=0; l++; } if(l==10){//分钟计时十位 l=0; m++; } if(m==6){ n++; m=0; Player(h,n); //整点放音 ii += 10*h+n; } if(n==10){ h++; n=0; } if(h==2 && n == 4){ h=0; n=0; }
if(w==h && x==n && y==m && z==l && clk_flag == 1){ //定时语音提醒
Beep(1000,1000); ii++; clk_flag = 0;
}
if(k1!=key3){//增加一小时 n++; k1=key3; int s; s=h*10+n; if(s>23) s-=24;
n = s%10; h = s/10;
} if(k!=key2){//减一小时 n--; k=key2; int s; s=h*10+n; if(s<0){ s=s+24; }
    n = s%10; h = s/10; }
if(k2!=key4){//减一分钟 l--; k2=key4; int s; s=m*10+l; if(s<0){ s=s+60; } m=s/10; l=s-m*10; }
if(k3!=key5){//增一分钟 l++; k3=key5; int s; s=m*10+l; if(s>59){ s=s-60; } m=s/10; l=s-m*10; }
}
} int _tmain(int argc, TCHAR* argv[], TCHAR* envp[]) { int nRetCode = 0;
// initialize MFC and print and error on failure if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)) { // TODO: change error code to suit your needs nRetCode = 1; } else { // TODO: code your application's behavior here. CString strHello; cout << (LPCTSTR)strHello << endl; } ULONG adr8254=0x00; ULONG adr8255=0x20; ULONG adrisd=0x40; Init9054(); OpenInt(); Init8254(); //初始化 8254 Init8255(); //初始化 8255 int flag=5; while(1){ while(flag!=0){ cout<<endl<<endl<<"请选择功能:"<<endl; cout<<"当前时区"<<shiqu<<endl; cout <<"1.语音提醒"<<endl; cout <<"2.秒表计时"<<endl; cout <<"3.时区转换"<<endl; cout <<"4.时钟"<<endl; cin >>flag; switch(flag){ case 1: Clock(); break; case 2: Second(); break; case 3: shiqubiao(); break; case 4: shizhong(); break; } } } CloseInt(); Cleanup(); return nRetCode;
}
