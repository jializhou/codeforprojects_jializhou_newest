#include"temperature.h"
#include<iostream>
using namespace std;
#define max 50001
#define divs 277
void quicksort(int arrays[max], int low, int arraylen, int tp[max]); //��������
int searchmin(int arrays[max], int *tp, int low, int arraylen, int value); //��ѯmin
int searchmax(int arrays[max], int *tp, int low, int arraylen, int value); //��ѯmax
int x[max], y[max], temp[max], tpx[max], tpy[max], rankx[max], ranky[max]; //*x,*y�ֱ�װ��۲�վ�ĵ������꣬tempװ������¶���Ϣ��*tpx,*tpy�ֱ�������x,y��С����tpx[2]=8��ʾ���ڵ�2λ����x[8],rank[8]=2��ʾx[8]���ڵ�2λ������rankx[i]��Ϊ����x[i]������
long long sum[max ][(max - 1) / divs + 2]; // i,j��ʾ����x��[0,i-1]�������� y��[0..j*divs-1]������
int sum1[max ][(max - 1) / divs + 2] ; // �ȸõ�С�ĵ���֮��

int main()
{
    int n = GetNumOfStation();
    for(int i = 0; i < n; i++) //¼����Ϣ������������ʼ��
    {
        GetStationInfo(i, &x[i], &y[i], &temp[i]);
        tpx[i] = i;
        tpy[i] = i;
    }
    quicksort(x, 0, n - 1, tpx);
    quicksort(y, 0, n - 1, tpy);

    for(int i = 0; i < n; i++) //����x[i],y[i]����������
    {
        rankx[tpx[i]] = i;
        ranky[tpy[i]] = i;
    }
    for (int i = 1; i <= n; i++) //Ϊ�˷������һ����Χ�ڵ��¶�ֵ������ȵ�pС�ĵ�(��������p����)�������¶�ֵ֮��sum��֮��Χ���ĵ�sum��Ӽ�,�ٶ��������������ɵõ���Χ�ڵ��¶�֮�͡�sum[i][j]��ʾ����rankx=i,ranky=j���·����¶�֮�ͣ��൱��һ��hashtable��ӳ���ϵ��
    {
        int k = tpx[i - 1];
       for (int j = 1; j <= (n - 1) / divs ; j++)
        {
            sum[i][j] = sum[i - 1][j];//�Ȱ�֮ǰ����ĵ��¶ȼӽ���
            sum1[i][j] = sum1[i - 1][j];
            if (ranky[k] < j * divs)
            {
                sum[i][j] += temp[k];//֮�󿴣�i,j)���Ƿ����Ҫ��
                sum1[i][j]++;
            }
        }
    }
    int x1, x2, y1, y2, flag = 1;
    int rx1, rx2, ry1, ry2;
    while(flag)
    {
        flag = GetQuery(&x1, &y1, &x2, &y2);
        if(x1 > x[tpx[n - 1]]) rx1 = n;
        else rx1 = searchmin(x, tpx, 0, n - 1, x1);
        if(y1 > y[tpy[n - 1]]) ry1 = n;
        else ry1 = searchmin(y, tpy, 0, n - 1, y1);
        if(x2 < x[tpx[0]]) rx2 = -1;
        else rx2 = searchmax(x, tpx, 0, n - 1, x2);
        if(y2 < y[tpy[0]]) ry2 = -1;
        else ry2 = searchmax(y, tpy, 0, n - 1, y2); //rx1,ry1�ֱ��Ǳ�x1,y1���������ȵ���С��������rx2,ry2�ֱ��Ǳ�x2,y2С������ȵ��������
        long long s = 0;
        int q;
        if ((rx1 > rx2) || (ry1 > ry2))//��������û�е�
            q = 0;
        else
        {
         int yc1 = ry1 / divs + 1, yc2 = (ry2 + 1) / divs;
            s = sum[rx2 + 1][yc2] - sum[rx2 + 1][yc1 - 1] - sum[rx1][yc2] + sum[rx1][yc1 - 1];
            q = sum1[rx2 + 1][yc2] - sum1[rx2 + 1][yc1 - 1] - sum1[rx1][yc2] + sum1[rx1][yc1 - 1];//��¼��Χ�ڵĵ���
            for (int i = (yc1 - 1) * divs; i <= ry1 - 1; i++)
                if (rankx[tpy[i]] >= rx1 && rankx[tpy[i]] <= rx2)//��ȥ���ڷ�Χ�ڵĵ�
                {
                    s -= temp[tpy[i]];
                    q--;
                }
            for (int i = yc2 * divs; i <= ry2; i++)
                if (rankx[tpy[i]] >= rx1 && rankx[tpy[i]] <= rx2)//��������ĵ�
                {
                    s += temp[tpy[i]];
                    q++;
                }
        }
        if (q == 0)
            Response(0);
        else
            Response(s / q);
    }
    return 0;
}

int searchmin(int arrays[max], int *tp, int low, int arraylen, int value)//���ҵ��Ǳ�value�����С���������value������
{
    if(low == arraylen) return low;
    int mid = (low + arraylen) / 2;
    if(value <= arrays[tp[mid]])
        return searchmin(arrays, tp, low, mid, value);
    else
        return searchmin(arrays, tp, mid + 1, arraylen, value);
}
int searchmax(int arrays[max], int *tp, int low, int arraylen, int value)//��ѯ���Ǳ�valueС������������߾���value������
{
    if(low == arraylen) return low;
    int mid = (low + arraylen) / 2;
    if(value < arrays[tp[mid + 1]])
        return searchmax(arrays, tp, low, mid, value);
    else
        return searchmax(arrays, tp, mid + 1, arraylen, value);
}

int sort_num(int arrays[max], int low, int arraylen, int tp[max]) //���������㷨�������߲��ң����߷ֱ��С����ʹӴ�С����һ��������ֹͣ
{
    int len = arraylen, temp;
    int i = low - 1, j = low;
    while(j < arraylen)
    {
        if (arrays[tp[j]] < arrays[tp[len]]) //��ʼʱi=low-1=0,j=low=1,arraylenΪ�ұ߽߱�ֵ���Ƚ�a[tp[j]]��a[tp[len]]�Ĵ�С,���a[tp[j]]<a[tp[len]]����iǰ����tp[i]��tp[j]����
        {
            i++;
            if (i != j)
            {
                temp = tp[i];
                tp[i] = tp[j];
                tp[j] = temp;
            }
        }
        j++;//������jǰ�ƣ����a[tp[j]]>a[tp[len]]����i���䣬jǰ�ƣ�һֱ�ظ�������̣�ֱ��j�Ƶ�len��λ�á�
    }
    if (i + 1 != len)
    {
        temp = tp[i + 1];
        tp[i + 1] = tp[len];
        tp[len] = temp;
    }
    return i + 1;
}

void quicksort(int arrays[max], int low, int arraylen, int tp[max]) //�ݹ����
{
    if(low < arraylen)
    {
        int a = sort_num(arrays, low, arraylen, tp);
        quicksort(arrays, low, a - 1, tp);
        quicksort(arrays, a + 1, arraylen, tp);
    }
}

