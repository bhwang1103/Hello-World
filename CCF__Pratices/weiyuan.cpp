#include "StdAfx.h" #include "afxwin.h" #include <windows.h> #include "QTH9054fun.h" #include <iostream>
#ifdef _DEBUG #define new DEBUG_NEW #undef THIS_FILE static char THIS_FILE[] = __FILE__; #endif
CWinApp theApp; using namespace std; void Init8254(){ ULONG adr8254=0x00; ULONG adr,dat;
adr=adr8254+3;//ѡ������ 0 ��Ϊʱ�ӷ����� dat=0x37; IO8bWrite(adr,dat); adr=adr8254; dat=0x32;//32 ��Ƶ IO8bWrite(adr,dat); dat=0; IO8bWrite(adr,dat);
adr=adr8254+3;//ѡ��ʱ�� 1 ��Ϊ��������
dat=0x77; IO8bWrite(adr,dat); adr=adr8254+1; dat=0x10; IO8bWrite(adr,dat); dat=0x00; IO8bWrite(adr,dat);
}
void Init8255(){ ULONG adr8255=0x20; ULONG adr,dat; adr=adr8255+3; dat=0x88; IO8bWrite(adr,dat); IO8bWrite(adr8255+2,0xff); }
void Player(int h,int n){//��ʱģ�� int t=h*10+n; for( int i = 0; i < t; i++){ Beep(500,500); Sleep(500); } }
int w=-1,x=-1,y=-1,z=-1;//���ӱ��� int h=0,n=9,m=5,l=9,shiqu=0,ii=0;//��ʼʱ�����ʱ�� int clk_flag = 0;//��ʱ����
void Clock(){//���ö�ʱ���� Beep(500,500); cout <<"������ָ��ʱ��(x x x x):"<<endl; cin >>w>>x>>y>>z; clk_flag = 1; }
void Second(){//����ʱ ULONG wei4[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //0 1 2 3 4 5 6 7 8 9 ULONG adr8255=0x20; ULONG adr,dat; int i=0,j=0,l=0,m=0,n=0; while(1){ int key; int key1; int state; while((state=IO8bRead(0x60)&(0x04))==0x00){
adr=adr8255+1; dat=0x80; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[n]; IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x40;
IO8bWrite(adr,dat); adr=adr8255; dat=wei4[m]-0x80; IO8bWrite(adr,dat); Sleep(1); if(state==1) break; adr=adr8255+1; dat=0x20; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x10; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[i]; IO8bWrite(adr,dat); Sleep(1);
} j++; while((state=IO8bRead(0x60)&(0x04))==0x04){ key=IO8bRead(adr8255+2)&(0x80); key1=IO8bRead(adr8255+2)&(0x40);
adr=adr8255+1; dat=0x80; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[n]; IO8bWrite(adr,dat); adr=adr8255+1; dat=0x40; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[m]-0x80; IO8bWrite(adr,dat); Sleep(1); if(state==0) break; adr=adr8255+1; dat=0x20; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); adr=adr8255+1; dat=0x10; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[i]; IO8bWrite(adr,dat);
} j++; if(j==2 && key==0){ i += 10; j=0;
} if(j==2){ j=0; } if(i==10){ i=0; l++; } if(l==10){ l=0; m++; } if(m==10){ n++; m=0; } if(n==10){ n=0; }
if(key1==0) break;
}
}
void shiqubiao(){ cout<<endl<<endl<<"��ǰʱ��Ϊ��"<<shiqu<<"ʱ��"<<endl; cout<<"����������Ҫ��ѯ��ʱ��"<<endl; cout<<"ʱ��/����"<<endl; cout<<"UTC Ӣ��       +1 ����        +2 ϣ��       +3 Ī˹��"<<endl; cout<<"+4 ������      +5 �ͻ�˹̹    +6 ������˹̹ +7 ̩��"<<endl; cout<<"+8 �й�        +9 �ձ�        +10 �ص�      +11 ������Ⱥ��"<<endl; cout<<"+12 ������     +13 ��Ħ��Ⱥ�� +14 ʥ����"<<endl; cout<<"-1 ��ý�Ⱥ��  -2 ����ʱ      -3 ����       -4 ʥ���Ǹ�"<<endl; cout<<"-5 ����ʱ��    -6 �в�ʱ��    -7 ɽ��ʱ��   -8 ̫ƽ��ʱ��"<<endl; cout<<"-9 ����˹��    -10 ������     -11 ����ʱ-11 -12 ���ڱ������"<<endl; int opt,shi; cin >> opt; shi = (h*10 + n - shiqu + opt + 24)%24;
shiqu = opt; h = shi / 10; n = shi % 10; cout<<h<<" "<<n<<endl;
} void shizhong(){ ULONG adr8254=0x00; ULONG adr8255=0x20; ULONG adrisd=0x40; ULONG adr,dat; ULONG wei4[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int j=0,k1=0,k=0,k2=0,k3=0,key2,key3,key4,key5; while(1){ if(!(IO8bRead(adr8255+2)&(0x20))) break; while((IO8bRead(0x60)&(0x02))==0x00) {
//��ʾʱ��ģ�� //λѡ�ź�ͨ�� B ��λ�˿� //��ʾ�����ź�ͨ�� A �˿� adr=adr8255+1; //���� 1 dat=0x80;      IO8bWrite(adr,dat); adr=adr8255; dat=wei4[h]; IO8bWrite(adr,dat); Sleep(1);
adr=adr8255+1; //���� 2 dat=0x40; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[n]; IO8bWrite(adr,dat); Sleep(1);
adr=adr8255+1;//���� 3 dat=0x20; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[m]; IO8bWrite(adr,dat); Sleep(1);
adr=adr8255+1;//���� 4 dat=0x10; IO8bWrite(adr,dat); adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); Sleep(1);
} cout<<h<<n<<m<<l<<ii<<endl; j++;//�͵�ƽ�ж� while((IO8bRead(0x60)&(0x02))==0x02){ //ͨ�� C �˿ڻ�ȡ Key key2=IO8bRead(adr8255+2)&(0x80); key3=IO8bRead(adr8255+2)&(0x40); key4=IO8bRead(adr8255+2)&(0x10); key5=IO8bRead(0x60)&(0x08);
adr=adr8255; dat=0x80; IO8bWrite(adr,dat); adr=adr8255+1; dat=0x80; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[h];
IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x40; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[n]-0x80;//�������� IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x20; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[m]; IO8bWrite(adr,dat); Sleep(1); adr=adr8255+1; dat=0x10; IO8bWrite(adr,dat);
adr=adr8255; dat=wei4[l]; IO8bWrite(adr,dat); Sleep(1);
} j++;//�ߵ�ƽ�ж� //ʱ�����ҵ������� if(j==2){//������� i ii++; j=0; } if(ii==60){//���Ӽ�ʱ��λ ii=0; l++; } if(l==10){//���Ӽ�ʱʮλ l=0; m++; } if(m==6){ n++; m=0; Player(h,n); //������� ii += 10*h+n; } if(n==10){ h++; n=0; } if(h==2 && n == 4){ h=0; n=0; }
if(w==h && x==n && y==m && z==l && clk_flag == 1){ //��ʱ��������
Beep(1000,1000); ii++; clk_flag = 0;
}
if(k1!=key3){//����һСʱ n++; k1=key3; int s; s=h*10+n; if(s>23) s-=24;
n = s%10; h = s/10;
} if(k!=key2){//��һСʱ n--; k=key2; int s; s=h*10+n; if(s<0){ s=s+24; }
    n = s%10; h = s/10; }
if(k2!=key4){//��һ���� l--; k2=key4; int s; s=m*10+l; if(s<0){ s=s+60; } m=s/10; l=s-m*10; }
if(k3!=key5){//��һ���� l++; k3=key5; int s; s=m*10+l; if(s>59){ s=s-60; } m=s/10; l=s-m*10; }
}
} int _tmain(int argc, TCHAR* argv[], TCHAR* envp[]) { int nRetCode = 0;
// initialize MFC and print and error on failure if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)) { // TODO: change error code to suit your needs nRetCode = 1; } else { // TODO: code your application's behavior here. CString strHello; cout << (LPCTSTR)strHello << endl; } ULONG adr8254=0x00; ULONG adr8255=0x20; ULONG adrisd=0x40; Init9054(); OpenInt(); Init8254(); //��ʼ�� 8254 Init8255(); //��ʼ�� 8255 int flag=5; while(1){ while(flag!=0){ cout<<endl<<endl<<"��ѡ����:"<<endl; cout<<"��ǰʱ��"<<shiqu<<endl; cout <<"1.��������"<<endl; cout <<"2.����ʱ"<<endl; cout <<"3.ʱ��ת��"<<endl; cout <<"4.ʱ��"<<endl; cin >>flag; switch(flag){ case 1: Clock(); break; case 2: Second(); break; case 3: shiqubiao(); break; case 4: shizhong(); break; } } } CloseInt(); Cleanup(); return nRetCode;
}
