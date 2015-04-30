#include <iostream>
using namespace std;
class team
{
public:
	void set(int sora[50],int sorb[50],int sorc[50],int i,char member[50]); //读入原始信息
	void write(int number,int i,char *mem);
	int checka(char*mem);//检查教练A此刻喜欢的队员i是否已被分配，如果没有，返回该队员编号
	int checkb(char*mem); 
	int checkc(char*mem); 
private:
	int sorta[50],sortb[50],sortc[50],n,mem[50];//mem数组用来记录已经被分配的队员被分配到哪一组
};

void team::set(int sora[50],int sorb[50],int sorc[50],int j,char member[50])
{
	n=j;
	for(int i=0;i<50;i++)
	{
		sorta[i] = sora[i];
		sortb[i] = sorb[i];
		sortc[i] = sorc[i];
		mem[i] = member[i];
	}
}
void team::write(int number,int coachi,char*mem)//向数组mem[i]中写入编号为i的队员被分配给了哪个教练
{
	*(mem+number-1)=coachi;
}

int team::checka(char*mem)
{
	int i=0;
	while(mem[sorta[i]-1]!=0)
	{
		i++;
	}
	return sorta[i];
}

int team::checkb(char*mem)
{
	int i=0;
	while(mem[sortb[i]-1]!=0)
	{
		i++;
	}
	return sortb[i];
}

int team::checkc(char*mem)
{
	int i=0;
	while(mem[sortc[i]-1]!=0)
	{
		i++;
	}
	return sortc[i];
}

int main()
{
	team T;
	int k,a[50],b[50],c[50],i=0,j=0,count;//n:最大数，count:想要知道的数
	char mem[50]={0};
	cin>>count;
	for (i=0;i<count;i++)
		cin >> a[i];//读入数组a
	for (i=0;i<count;i++)
		cin >> b[i];//读入数组b
	for (i=0;i<count;i++)
		cin >> c[i];//读入数组c
	cin>>k;
	T.set(a,b,c,count,mem);
	while(count>0)//count是用于计数
	{	
		i=0;
		if(count>0)
		{
			T.write(T.checka(mem),'A',mem);
			count--;
		}
		if(count>0)
		{
			T.write(T.checkb(mem),'B',mem);
			count--;
		}
		if(count>0) 
		{
			T.write(T.checkc(mem),'C',mem);
			count--;
		}
	}
	cout<<mem[k-1]<<endl;
	return 0;
}