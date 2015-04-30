#include"beneficiation.h"
#include<iostream>
#include <stdio.h>
using namespace std;
#define max 10003
int flag = 1;
int  p_number[max], p_index[max];
typedef struct Dat
{
    bool p_i;
    bool p_j;
} dat;
//dat qmeasure(int i, int j, int a);
dat qmeasure(int j, int a);
int partition(int number[], int data[], int lo, int hi)
{
    int key = data[hi]; //以最后一个元素，data[hi]为主元
    int i = lo - 1;
    for(int j = lo; j < hi; j++) ///注，j从p指向的是r-1，不是r。
    {
        if(qmeasure(j, key).p_j == true)
        {
            i = i + 1;
            int tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }
    }
    int tmp = data[i + 1];
    data[i + 1] = data[hi];
    data[hi] = tmp;
    return i + 1;
}
void QuickSort(int number[], int data[], int lo, int hi)
{
    if (lo < hi)
    {
        int k = partition(number, data, lo, hi);
        QuickSort(number, data, lo, k - 1);
        QuickSort(number, data, k + 1, hi);
    }
}

//void qsort(int* number, int* index, int l, int r); //number表示读出的测量结果，index表示降序排名
int main()
{
    flag = GetNumOfOre();
    while(flag)
    {
        for(int i = 0; i < flag; i++) //对排名初始化
        {
            p_index[i] = i;
        }
        QuickSort(p_number, p_index, 0, flag - 1);
        for(int i = 0; i < flag; i++)
            Report(p_index[i], i);
        flag = GetNumOfOre();
    }
    return 0;
}
dat qmeasure(int j, int a)
{
    dat p;
    Measure(-1, a, p_index[j], -1, &p_number[p_index[max - 1]], &p_number[a], &p_number[p_index[j]], &p_number[p_index[max - 1]]);
    if(p_number[p_index[j]] > p_number[a]) p.p_j = true;
    else p.p_j = false;
    return p;
}
//dat qmeasure(int i, int j, int a)
//{
//    dat p;
//    Measure(p_index[i], a, p_index[j], -1, &p_number[p_index[i]], &p_number[a], &p_number[p_index[j]], &p_number[p_index[max - 1]]);
//    if(p_number[p_index[i]] > p_number[a])p.p_i = true;
//    else p.p_i = false;
//    if(p_number[p_index[j]] > p_number[a]) p.p_j = true;
//    else p.p_j = false;
//    return p;
//}
//void qsort(int* number, int* index, int l, int r) //number表示读出的测量结果，index表示降序排名
//{
//    int i = l, j = r, tmp,a=index[(l+r)>>1];
//    while (i < j)
//    {
//        dat p = qmeasure(i, j, a);
//        while(p.p_i || p.p_j)
//        {
//            if (p.p_i== true) i++;
//            if(p.p_j == true) j--;
//            p = qmeasure(i, j, a);
//        }
//        if (i <= j)
//        {
//            tmp = index[i];
//            index[i] = index[j];
//            index[j] = tmp;
//            i++;
//            j--;
//        }
//    }
//    if (i < r) qsort(number, index, i, r);
//    if (j > l) qsort(number, index, l, j);
//}
//
//void improved_qsort(int r[],int arr[], int low, int high)
//{
//if(low >= high) return;
//int i = low;
//int j = high+1;
//int pivot = arr[i];
//int temp;
//while(i<j)
//{
//for(i=i+1; i<high; i++)
//	if(qmeasure(i, j, pivot).p_i==false)
//break;
//for(j=j-1; j>low; j--)
//	if(qmeasure(i, j, pivot).p_j==false)
//break;
//if(i<j)
//{
//temp = arr[i];
//arr[i] = arr[j];
//arr[j] = temp;
//}
//}
//temp = arr[j];
//arr[j] = arr[low];
//arr[low] = temp;
//improved_qsort(r,arr, low, j-1);
//improved_qsort(r,arr, i, high);
//}


