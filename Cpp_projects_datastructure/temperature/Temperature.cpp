#include"temperature.h"
#include<iostream>
using namespace std;
#define max 50001
#define divs 277
void quicksort(int arrays[max], int low, int arraylen, int tp[max]); //快速排序
int searchmin(int arrays[max], int *tp, int low, int arraylen, int value); //查询min
int searchmax(int arrays[max], int *tp, int low, int arraylen, int value); //查询max
int x[max], y[max], temp[max], tpx[max], tpy[max], rankx[max], ranky[max]; //*x,*y分别装入观察站的地理坐标，temp装入的是温度信息，*tpx,*tpy分别用作对x,y大小排序（tpx[2]=8表示排在第2位的是x[8],rank[8]=2表示x[8]排在第2位）升序，rankx[i]即为最终x[i]的排名
long long sum[max ][(max - 1) / divs + 2]; // i,j表示的是x在[0,i-1]的排名和 y在[0..j*divs-1]的排名
int sum1[max ][(max - 1) / divs + 2] ; // 比该点小的点数之和

int main()
{
    int n = GetNumOfStation();
    for(int i = 0; i < n; i++) //录入信息，并对排名初始化
    {
        GetStationInfo(i, &x[i], &y[i], &temp[i]);
        tpx[i] = i;
        tpy[i] = i;
    }
    quicksort(x, 0, n - 1, tpx);
    quicksort(y, 0, n - 1, tpy);

    for(int i = 0; i < n; i++) //记下x[i],y[i]的最终排名
    {
        rankx[tpx[i]] = i;
        ranky[tpy[i]] = i;
    }
    for (int i = 1; i <= n; i++) //为了方便计算一个范围内的温度值，算出比点p小的点(不包括点p本身)的所有温度值之和sum，之后范围的四点sum相加减,再对少数点做处理即可得到范围内的温度之和。sum[i][j]表示的是rankx=i,ranky=j左下方的温度之和，相当于一个hashtable（映射关系）
    {
        int k = tpx[i - 1];
       for (int j = 1; j <= (n - 1) / divs ; j++)
        {
            sum[i][j] = sum[i - 1][j];//先把之前算过的点温度加进来
            sum1[i][j] = sum1[i - 1][j];
            if (ranky[k] < j * divs)
            {
                sum[i][j] += temp[k];//之后看（i,j)点是否符合要求
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
        else ry2 = searchmax(y, tpy, 0, n - 1, y2); //rx1,ry1分别是比x1,y1大或者是相等的最小排名，而rx2,ry2分别是比x2,y2小或是相等的最大排名
        long long s = 0;
        int q;
        if ((rx1 > rx2) || (ry1 > ry2))//表明其中没有点
            q = 0;
        else
        {
         int yc1 = ry1 / divs + 1, yc2 = (ry2 + 1) / divs;
            s = sum[rx2 + 1][yc2] - sum[rx2 + 1][yc1 - 1] - sum[rx1][yc2] + sum[rx1][yc1 - 1];
            q = sum1[rx2 + 1][yc2] - sum1[rx2 + 1][yc1 - 1] - sum1[rx1][yc2] + sum1[rx1][yc1 - 1];//记录范围内的点数
            for (int i = (yc1 - 1) * divs; i <= ry1 - 1; i++)
                if (rankx[tpy[i]] >= rx1 && rankx[tpy[i]] <= rx2)//刨去不在范围内的点
                {
                    s -= temp[tpy[i]];
                    q--;
                }
            for (int i = yc2 * divs; i <= ry2; i++)
                if (rankx[tpy[i]] >= rx1 && rankx[tpy[i]] <= rx2)//加上少算的点
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

int searchmin(int arrays[max], int *tp, int low, int arraylen, int value)//查找的是比value大的最小排名或就是value的排名
{
    if(low == arraylen) return low;
    int mid = (low + arraylen) / 2;
    if(value <= arrays[tp[mid]])
        return searchmin(arrays, tp, low, mid, value);
    else
        return searchmin(arrays, tp, mid + 1, arraylen, value);
}
int searchmax(int arrays[max], int *tp, int low, int arraylen, int value)//查询的是比value小的最大排名或者就是value的排名
{
    if(low == arraylen) return low;
    int mid = (low + arraylen) / 2;
    if(value < arrays[tp[mid + 1]])
        return searchmax(arrays, tp, low, mid, value);
    else
        return searchmax(arrays, tp, mid + 1, arraylen, value);
}

int sort_num(int arrays[max], int low, int arraylen, int tp[max]) //快速排序算法，从两边查找，两边分别从小到大和从大到小排序，一旦相遇即停止
{
    int len = arraylen, temp;
    int i = low - 1, j = low;
    while(j < arraylen)
    {
        if (arrays[tp[j]] < arrays[tp[len]]) //初始时i=low-1=0,j=low=1,arraylen为右边边界值。比较a[tp[j]]与a[tp[len]]的大小,如果a[tp[j]]<a[tp[len]]，则i前进，tp[i]与tp[j]交换
        {
            i++;
            if (i != j)
            {
                temp = tp[i];
                tp[i] = tp[j];
                tp[j] = temp;
            }
        }
        j++;//交换后j前移，如果a[tp[j]]>a[tp[len]]，则i不变，j前移，一直重复这个过程，直至j移到len的位置。
    }
    if (i + 1 != len)
    {
        temp = tp[i + 1];
        tp[i + 1] = tp[len];
        tp[len] = temp;
    }
    return i + 1;
}

void quicksort(int arrays[max], int low, int arraylen, int tp[max]) //递归调用
{
    if(low < arraylen)
    {
        int a = sort_num(arrays, low, arraylen, tp);
        quicksort(arrays, low, a - 1, tp);
        quicksort(arrays, a + 1, arraylen, tp);
    }
}

