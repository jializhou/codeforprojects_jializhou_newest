#include <iostream>
using namespace std;
void quicksort(int arrays[2][2200],int low,int arraylen);//快速排序
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
	n+=m;//完成输入工作

	quicksort(a,0,n);
	//完成排序工作

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
	cout<<lenth<<endl;//完成计算最长空闲长度工作，算法：先将起始时间和降落时间分别放入数组a[0]和a[1],按照起始时间的先后排序数组a[0],数组a[1]同时跟着a[0]排，之后将a[i]<b[i-1]的情况的a[i]换成b[i-1]
	return 0;//然后a[1][i]跟着改变，计算a[0][i+1]与a[1][i]的最大差值(仍需考虑a[0][i+1]<a[1][i]的情况）即为最大空闲时间
}

int sort_num(int arrays[2][2200],int low, int arraylen)//借鉴了同学的快速排序算法，从两边查找，两边分别从小到大和从大到小排序，一旦相遇即停止
{
	int len=arraylen,temp;
	int i=low-1,j=low;
	while(j<arraylen)
	{
		if (arrays[0][j]<arrays[0][len])//初始时i=low-1=0,j=low=1,arraylen为右边边界值。比较a[0][j]与a[0][len]的大小，如果a[0][j]<a[0][len]，则i前进，a[0][i]与a[0][j]交换
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
		j++;//交换后j前移，如果a[0][j]>a[0][len]，则i不变，j前移，一直重复这个过程，直至j移到len的位置。
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

void quicksort(int arrays[2][2200],int low, int arraylen)//递归调用
{
	if(low<arraylen)
	{
		int a=sort_num(arrays,low,arraylen);
		quicksort(arrays,low,a-1);
		quicksort(arrays,a+1,arraylen);
	}
}