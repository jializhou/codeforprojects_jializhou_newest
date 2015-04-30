#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;
int multiply[101];
unsigned int *pMultiply[101];
int k;
int index;//index为希望查询的位序N
unsigned int weapon;
unsigned int Min(unsigned int **number,int *multiply);

unsigned int GetUglyNumber()
{
    if(index <= 0)
        return 0;
    unsigned int *pUglyNumbers = new unsigned int[index];//从小到大排出的数据
    pUglyNumbers[0] = 1;
    int nextUglyIndex = 1;
    for(int i = 0; i < k; i++)
    {
        pMultiply[i] = pUglyNumbers;//记录对于每一个质因子而言，排在它之前的每一个丑数乘以它都小于当前最大的丑数，而排在它之后的每一个丑数乘以该因子都大于当前最大的丑数
    }

    while(nextUglyIndex < index)
    {
        unsigned int min = Min(pMultiply, multiply);
        pUglyNumbers[nextUglyIndex] = min;
        for(int i = 0; i < k; i++)
        {
            while(*pMultiply[i] * multiply[i] <= pUglyNumbers[nextUglyIndex])
                ++pMultiply[i];
        }
        ++nextUglyIndex;
    }

    unsigned int  ugly = pUglyNumbers[nextUglyIndex - 1];
    delete[] pUglyNumbers;
    return ugly;
}

unsigned int Min(unsigned int **number,int *multiply)
{
    unsigned int min=*number[0]*multiply[0];
    if(k == 1) return min;
    else
        for(int i = 1; i < k ; i++)
        {
            min = (*number[i]*multiply[i] < min) ? *number[i]*multiply[i] : min;
        }
    return min;
}
int main()
{
	cin>>k>>index;
	for(int i=0;i<k;i++)
		cin>>multiply[i];
	weapon = GetUglyNumber();
	cout<<weapon<<endl;
	//system("pause");
	return 0;
}