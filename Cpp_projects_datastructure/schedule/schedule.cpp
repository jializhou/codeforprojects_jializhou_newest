#include <iostream>
using namespace std;
void quicksort(int arrays[2][2200],int low,int arraylen);//��������
int main()
{
	int n,m,i,lenth=0;
	int a[2][2200];
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>a[0][i]>>a[1][i];
	}
	cin>>m;
	for(i=0;i<m;i++)
	{
		cin>>a[0][i+n]>>a[1][i+n];
	}
	n+=m;//������빤��

	quicksort(a,0,n);
	//���������

	lenth=a[0][0];
	for(i=0;i<n-1;i++)
	{
		if(a[1][i]>a[0][i+1])
		{
			if(a[1][i]>a[1][i+1])
			{
				a[1][i+1]=a[1][i];
			}
		}
		else if(a[0][i+1]-a[1][i]>lenth)
		{
			lenth=a[0][i+1]-a[1][i];
		}
	}
	cout<<lenth<<endl;//��ɼ�������г��ȹ������㷨���Ƚ���ʼʱ��ͽ���ʱ��ֱ��������a[0]��a[1],������ʼʱ����Ⱥ���������a[0],����a[1]ͬʱ����a[0]�ţ�֮��a[i]<b[i-1]�������a[i]����b[i-1]
	return 0;//Ȼ��a[1][i]���Ÿı䣬����a[0][i+1]��a[1][i]������ֵ(���迼��a[0][i+1]<a[1][i]���������Ϊ������ʱ��
}

int sort_num(int arrays[2][2200],int low, int arraylen)//�����ͬѧ�Ŀ��������㷨�������߲��ң����߷ֱ��С����ʹӴ�С����һ��������ֹͣ
{
	int len=arraylen,temp;
	int i=low-1,j=low;
	while(j<arraylen)
	{
		if (arrays[0][j]<arrays[0][len])//��ʼʱi=low-1=0,j=low=1,arraylenΪ�ұ߽߱�ֵ���Ƚ�a[0][j]��a[0][len]�Ĵ�С�����a[0][j]<a[0][len]����iǰ����a[0][i]��a[0][j]����
		{
			i++;
			if (i!=j)
			{
				temp = arrays[0][i];
				arrays[0][i] = arrays[0][j];
				arrays[0][j] = temp;
				temp = arrays[1][i];
				arrays[1][i] = arrays[1][j];
				arrays[1][j] = temp;
			}
		}
		j++;//������jǰ�ƣ����a[0][j]>a[0][len]����i���䣬jǰ�ƣ�һֱ�ظ�������̣�ֱ��j�Ƶ�len��λ�á�
	}
		if (i+1!=len)
		{
			temp = arrays[0][i+1];
			arrays[0][i+1] =arrays[0][len];
			arrays[0][len] = temp;
			temp = arrays[1][i+1];
			arrays[1][i+1] = arrays[1][len];
			arrays[1][len] = temp;
		}
	return i+1;
}

void quicksort(int arrays[2][2200],int low, int arraylen)//�ݹ����
{
	if(low<arraylen)
	{
		int a=sort_num(arrays,low,arraylen);
		quicksort(arrays,low,a-1);
		quicksort(arrays,a+1,arraylen);
	}
}