#include <math.h>
#include <iostream>
using namespace std;

#define  n1size 25
#define  n2size 50
#define  n2showsize 20



class Num
{
public:
	int zf;
	int n1[n1size];
	int n2[n2size];
	
	Num();
	Num(int nn1[n1size],int nn2[n2size]);
	Num(int n);
	~Num(){};
	void numprint();
	void operator =(Num &a);
	Num operator +(Num a);
	Num operator -(Num a);
	Num operator *(Num a);
	Num operator /(int a);
};

inline Num::Num()//构造函数
{
	for (int i=0;i<n1size;i++)
	{
		n1[i]=0;
	}
	for (int i=0;i<n2size;i++)
	{
		n2[i]=0;
	}
	zf=1;
}

inline Num::Num(int nn1[n1size],int nn2[n2size])//构造函数
{
	for (int i=0;i<n1size;i++)
	{
		n1[i]=nn1[i];
	}
	for (int i=0;i<n2size;i++)
	{
		n2[i]=nn2[i];
	}
	zf=1;
}

inline Num::Num(int n)
{
	zf=1;
	if(n<0){zf=-1;n=0-n;}
	int i=n1size;
	while (n!=0)
	{
		n1[i-1]=n%10;
		n/=10;
		i--;
	}
	i--;
	for (;i>=0;i--)
	{
		n1[i]=0;
	}
	for (int j=0;j<n2size;j++)
	{
		n2[j]=0;
	}
}

void Num::operator =(Num &a)//等号复制
{
	//Num x(a.n1,a.n2);
	for (int i=0;i<n1size;i++)
	{
		n1[i]=a.n1[i];
	}
	for (int i=0;i<n2size;i++)
	{
		n2[i]=a.n2[i];
	}
	zf=a.zf;
	//return this;
}

void Num::numprint()
{
	if(zf==-1)cout<<"-";
	int showflag=0;
	if(n2[n2showsize]>=5)
	{
		Num temp;
		temp.n2[n2showsize]=5;
		Num copy(n1,n2);
		copy=copy+temp;
		copy.numprint();
		return;
	}
	for (int i=0;i<n1size;i++)
	{
		if(n1[i]!=0)showflag=1;
		if(showflag==1)cout<<n1[i];
	}
	if(showflag==0)cout<<"0";
	cout<<".";
	for (int i=0;i<n2showsize;i++)
	{
		cout<<n2[i];
	}
}

Num Num::operator +(Num a)
{
	if (a.zf!=zf)
	{
		int nn1[n1size];
		int nn2[n2size];
		int jieweiflag=0;
		int zfflag=0;
		int fzf=1;
		for (int i=0;i<n1size+n2size-1;i++)
		{
			if (i<n1size)
			{
				if(n1[i]>a.n1[i]){zfflag=1;break;}
				if(n1[i]<a.n1[i]){zfflag=-1;break;}
			} 
			else
			{
				if(n2[i-n1size]>a.n2[i-n1size]){zfflag=1;break;}
				if(n2[i-n1size]<a.n2[i-n1size]){zfflag=-1;break;}
			}
		}
		if (zfflag==1)
		{
			for (int i=n2size-1;i>=0;i--)
			{
				nn2[i]=n2[i]-a.n2[i]-jieweiflag;
				if (nn2[i]>=0)
				{
					jieweiflag=0;
				} 
				else
				{
					jieweiflag=1;
					nn2[i]+=10;
				}
			}
			for (int i=n1size-1;i>=0;i--)
			{
				nn1[i]=n1[i]-a.n1[i]-jieweiflag;
				if (nn1[i]>=0)
				{
					jieweiflag=0;
				} 
				else
				{
					jieweiflag=1;
					nn1[i]+=10;
				}
			}
			fzf=zf;
		}
		if (zfflag==-1)
		{
			for (int i=n2size-1;i>=0;i--)
			{
				nn2[i]=a.n2[i]-n2[i]-jieweiflag;
				if (nn2[i]>=0)
				{
					jieweiflag=0;
				} 
				else
				{
					jieweiflag=1;
					nn2[i]+=10;
				}
			}
			for (int i=n1size-1;i>=0;i--)
			{
				nn1[i]=a.n1[i]-n1[i]-jieweiflag;
				if (nn1[i]>=0)
				{
					jieweiflag=0;
				} 
				else
				{
					jieweiflag=1;
					nn1[i]+=10;
				}
			}
			fzf=(-1)*zf;
		}
		if (zfflag==0)
		{
			Num xx;
			return xx;
		}
		Num x(nn1,nn2);
		x.zf=fzf;
		return x;
	}
	int nn1[n1size];
	int nn2[n2size];
	int jinweiflag=0;
	for (int i=n2size-1;i>=0;i--)
	{
		nn2[i]=n2[i]+a.n2[i]+jinweiflag;
		if (nn2[i]<10)
		{
			jinweiflag=0;
		} 
		else
		{
			jinweiflag=1;
			nn2[i]%=10;
		}
	}
	for (int i=n1size-1;i>=0;i--)
	{
		nn1[i]=n1[i]+a.n1[i]+jinweiflag;
		if (nn1[i]<10)
		{
			jinweiflag=0;
		} 
		else
		{
			jinweiflag=1;
			nn1[i]%=10;
		}
	}
	Num x(nn1,nn2);
	x.zf=zf;
	return x;
}

Num Num::operator -(Num a)
{
	if (a.zf!=zf)
	{
		int nn1[n1size];
		int nn2[n2size];
		int jinweiflag=0;
		for (int i=n2size-1;i>=0;i--)
		{
			nn2[i]=n2[i]+a.n2[i]+jinweiflag;
			if (nn2[i]<10)
			{
				jinweiflag=0;
			} 
			else
			{
				jinweiflag=1;
				nn2[i]%=10;
			}
		}
		for (int i=n1size-1;i>=0;i--)
		{
			nn1[i]=n1[i]+a.n1[i]+jinweiflag;
			if (nn1[i]<10)
			{
				jinweiflag=0;
			} 
			else
			{
				jinweiflag=1;
				nn1[i]%=10;
			}
		}
		Num x(nn1,nn2);
		x.zf=zf;
		return x;
	}
	int nn1[n1size];
	int nn2[n2size];
	int jieweiflag=0;
	int zfflag=0;
	int fzf=1;
	for (int i=0;i<n1size+n2size-1;i++)
	{
		if (i<n1size)
		{
			if(n1[i]>a.n1[i]){zfflag=1;break;}
			if(n1[i]<a.n1[i]){zfflag=-1;break;}
		} 
		else
		{
			if(n2[i-n1size]>a.n2[i-n1size]){zfflag=1;break;}
			if(n2[i-n1size]<a.n2[i-n1size]){zfflag=-1;break;}
		}
	}
	if (zfflag==1)
	{
		for (int i=n2size-1;i>=0;i--)
		{
			nn2[i]=n2[i]-a.n2[i]-jieweiflag;
			if (nn2[i]>=0)
			{
				jieweiflag=0;
			} 
			else
			{
				jieweiflag=1;
				nn2[i]+=10;
			}
		}
		for (int i=n1size-1;i>=0;i--)
		{
			nn1[i]=n1[i]-a.n1[i]-jieweiflag;
			if (nn1[i]>=0)
			{
				jieweiflag=0;
			} 
			else
			{
				jieweiflag=1;
				nn1[i]+=10;
			}
		}
		fzf=zf;
	}
	if (zfflag==-1)
	{
		for (int i=n2size-1;i>=0;i--)
		{
			nn2[i]=a.n2[i]-n2[i]-jieweiflag;
			if (nn2[i]>=0)
			{
				jieweiflag=0;
			} 
			else
			{
				jieweiflag=1;
				nn2[i]+=10;
			}
		}
		for (int i=n1size-1;i>=0;i--)
		{
			nn1[i]=a.n1[i]-n1[i]-jieweiflag;
			if (nn1[i]>=0)
			{
				jieweiflag=0;
			} 
			else
			{
				jieweiflag=1;
				nn1[i]+=10;
			}
		}
		fzf=(-1)*zf;
	}
	if (zfflag==0)
	{
		Num xx;
		return xx;
	}
	Num x(nn1,nn2);
	x.zf=fzf;
	return x;
}

Num Num::operator *(Num a)
{
	int nn1[n1size+n2size];
	int nn2[n2size+n1size];
	int nn[2*(n1size+n2size)];
	int num1[n1size];
	int num2[n2size];
	for (int i=0;i<n1size;i++)
	{
		nn1[i]=n1[i];
		nn2[i]=a.n1[i];
	}
	for (int i=0;i<n2size;i++)
	{
		nn1[i+n1size]=n2[i];
		nn2[i+n1size]=a.n2[i];
	}
	for (int i=0;i<2*(n1size+n2size);i++)
	{
		nn[i]=0;
	}
	for (int i=n1size+n2size-1;i>=0;i--)
	{
		int jinweiflag=0;
		for (int j=n1size+n2size-1;j>=0;j--)
		{
			nn[i+j+1]=nn[i+j+1]+nn1[i]*nn2[j]+jinweiflag;
			if (nn[i+j+1]<10)
			{
				jinweiflag=0;
			}
			else
			{
				jinweiflag=nn[i+j+1]/10;
				nn[i+j+1]%=10;
			}
		}
	}
	for (int i=0;i<n1size;i++)
	{
		num1[i]=nn[i+n1size];
	}
	for (int i=0;i<n2size;i++)
	{
		num2[i]=nn[i+2*n1size];
	}
	Num x(num1,num2);
	x.zf=1;
	if(zf!=a.zf)x.zf=-1;
	return x;
}

Num Num::operator /(int a)
{
	if(a==0)cout<<"除数为0，错误。"<<endl;
	int nn1[n1size+n2size];
	int nn2[n2size+n1size];
	int num1[n1size];
	int num2[n2size];
	for (int i=0;i<n1size;i++)
	{
		nn1[i]=n1[i];
		nn2[i]=0;
	}
	for (int i=0;i<n2size;i++)
	{
		nn1[i+n1size]=n2[i];
		nn2[i+n1size]=0;
	}
	int k=0;
	for (k=0;nn1[k]!=0;k++);
	int c=0;
	for (;k<n1size+n2size-1;k++)
	{
		c=c%a*10+nn1[k];
		nn2[k]=c/a;
	}
	for (int i=0;i<n1size;i++)
	{
		num1[i]=nn2[i];
	}
	for (int i=0;i<n2size;i++)
	{
		num2[i]=nn2[i+n1size];
	}
	Num x(num1,num2);
	x.zf=zf;
	if(a<0)x.zf=-1*x.zf;
	return x;
}

