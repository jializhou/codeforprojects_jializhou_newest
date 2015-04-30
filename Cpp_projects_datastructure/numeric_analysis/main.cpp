#include "number.h"
#include <iostream>
#include <math.h>

using namespace std;
Num zero(0);
Num one(1);
Num two(2);	
Num four(4);
Num six(6);
#define  n1size 25
#define  n2size 50
#define  n2showsize 20

#define  Tailenum 22
#define  Longnum 80
#define  Longnum2 80
#define  etlnum2 9
#define  etlnum3 5


void Taile(Num &a);
void Longgekuta1(Num &a);
void Longgekuta2(Num &a);
void Taile2(Num &a,int pi_nlnum);
void Pi_Taile2(Num &a);
void Pi_Taile(Num &a);
void Tixing(Num &a,int num);
void Romberg(Num &a);

int main(void)
{
	cout<<"e��"<<endl;
	cout<<"̩��չ���������㣺"<<endl;
	Num result;
	Taile(result);
	result.numprint();
	cout<<endl;
	cout<<"9����������������㣺"<<endl;
	Longgekuta1(result);
	result.numprint();
	cout<<endl;
	cout<<"�����������2���㣺"<<endl;
	Longgekuta2(result);
	result.numprint();
	cout<<endl<<endl;

	cout<<"pi��"<<endl;
	cout<<"�Ľ�̩��չ���������㣺"<<endl;
	Pi_Taile2(result);
	result.numprint();
	cout<<endl;
	cout<<"Machin�������㣺"<<endl;
	Pi_Taile(result);
	result.numprint();
	cout<<endl<<endl;
	cout<<"��ֵ���ַ������㣺"<<endl;
	cout<<"(�������ι�ʽ��"<<"����Ϊ1/1024ʱ��ֵ,��ʱ�����Բ���"<<endl;
	Tixing(result,1024);
	result.numprint();	
	cout<<")"<<endl;
	cout<<"�����������ʽ��"<<endl;
	Romberg(result);
	result.numprint();	
	cout<<endl;
	fflush stdin;
	getchar();
	cout<<endl;
	return 0;
}

void Taile(Num &a)//��̩���㷨����e
{
	Num s(1);
	Num add(1);
	for (int i=1;i<Tailenum;i++)
	{
		add = add/i;
		s=s+add;
	}
	a=s;
}

void Longgekuta1(Num &a)//��9������-������ʽ������ȡ1��1/100���ɵ�e
{
	Num h(1);
	Num yn(1);
	Num yn1(1);
	h = h/ Longnum;
	Num k1,k2,k3,k4,k5,k6;
	for (int i=0;i<Longnum;i++)
	{
		Num add(1);
		for (int j=1;j< etlnum2;j++)
		{
			add = h*add/j;
			yn1=yn1+add*yn;
		}
//yn1=yn+yn*h+yn*h*h/2+yn*h*h*h/6+yn*h*h*h*h/24+yn*h*h*h*h*h/120+yn*h*h*h*h*h*h/720;
		yn = yn1;
	}
	a=yn;
}

void Longgekuta2(Num &a)//�����������-������ʽ��ȡ1/1024��1/100�����e^(1/1024)��ֵ��֮��ƽ��10�μ��ɵõ�e.��С�˼�����
{
	Num h(1);
	Num yn(1);
	Num yn1(1);
	Num e(1);
	e = e/1024;
	h = h/Longnum;
	Num k1,k2,k3,k4,k5,k6;
	for (int i=0;i<Longnum2;i++)
	{
		Num add(1);
		for (int j=1;j<etlnum3;j++)
		{
			add = e*h*add/j;
			yn1=yn1+add*yn;
		}
//yn1=yn+yn*h+yn*h*h/2+yn*h*h*h/6+yn*h*h*h*h/24+yn*h*h*h*h*h/120+yn*h*h*h*h*h*h/720;
		yn = yn1;
	}
	for(int i=0;i<10;i++)
	{
		yn = yn*yn;
	}
	a=yn;
}

void Taile2(Num &a,int pi_tlnum)//��̩���㷨����pi
{
	Num s(a);
	Num add1,delete1;
	Num temp(a);
	Num add(temp);
	temp = temp*temp;
	for (int i=1;i<pi_tlnum;i++)
	{
		int t = 4*i-1;
		add = add * temp;
		delete1 = add/t;
		s = s - delete1;
		t= 4*i+1;
		add = add * temp;
		add1 = add/t;
		s=s+add1;
	}
	a=s;
}

void Pi_Taile2(Num &a)//���øĽ���Ĺ�ʽ����̩���㷨���� pi
{
	int num =5;
	Num m1(one/13),m2(one/21),m3(one/57),m4(one/239);
	Taile2(m1,num);
	Taile2(m2,num);
	Taile2(m3,num);
	Taile2(m4,num);
	a = six*m1+six*m2+two*m3+m4;
	a = four* a;
}

//void Pi_Taile(Num &a)//����̫������n=200000ʱ��δ������С�����20λ����
//{
//	Num s(one);
//	Num add1,delete1;
//	Num add(one);
//	for (int i=1;i<pi_tlnum;i++)
//	{
//		int t = 4*i-1;
//		delete1 = add/t;
//		s = s - delete1;
//		t= 4*i+1;
//		add1 = add/t;
//		s=s+add1;
//	}
//	a=four*s;
//}

void Pi_Taile(Num &a)//��Machin��ʽ������̩���㷨����pi
{
	int num = 10;
	Num m1(one/5),m2(one/239);
	Taile2(m1,num);
	Taile2(m2,num);
	a = four*m1-m2;
	a = four* a;
}
 
void Tixing(Num &a,int pi_tixing)//��_0^1[1/(1+x*x)dx]=��/4,��_a^b[f(x)dx]=1/n*{[f(0)+f(1)]/2+(f(xi),i=1..n-1)�ĺ�},xi=i/n
{
	Num fx;
	fx= one+one/2;
	fx = fx/2;
	Num c(pi_tixing*pi_tixing);
		int d = pi_tixing*pi_tixing;
	for(int i=1;i<pi_tixing;i++)
	{
		int b = d+i*i;
		fx = fx + c/b;
	}
	fx = fx/pi_tixing;
	a = four*fx;
}

void Romberg(Num &a)//�����������㷨����
{
	//Num fx;
	//fx= one+one/2;
	//Num c(pi_tixing*pi_tixing);
	//int d = pi_tixing*pi_tixing;
	//for(int i=1;i<pi_tixing;i++)
	//{
	//	int b = d+i*i;
	//	fx = fx + two*c/b;
	//}
	//c= four*c;
	//for(int i=0;i<pi_tixing;i++)
	//{
	//	int b = 4*d+(2*i+1)*(2*i+1);
	//	fx = fx+c/b;
	//}
	//fx = fx/pi_tixing;
	//fx = fx/6;
	//a = two*four*fx;
	Num t1,t2,t3,t4;
	Tixing(t1,64);
	Tixing(t2,128);
	Tixing(t3,256);
	Tixing(t4,512);
	Num s1= four*t2/3-t1/3;
	Num s2= four*t3/3-t2/3;
	Num s3=four*t4/3-t3/3;
	Num c1=four*four*s2/15-s1/15;
	Num c2=four*four*s3/15-s2/15;
	Num r=four*four*four*c2/63-c1/63;
	a=r;
}