#include<stdio.h>
#include<stdlib.h>
#include"DoubleList.h"

int main()
{
    int n, i = 0, j = 0, bh[1000] = {0}, times;
    float x1, x2, y1, y2;
    scanf("%d", &n);
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    DoubleList<dat>* bian = new DoubleList<dat>;//使用了两个链表，分别存储编号对应的幻灯片的两个点对应的坐标，以及序号对应的点的坐标。
    dat d(x1, y1, x2, y2, 0);
    bian->Insert(d);
    if(n > 1)
    {
        for(i = 1; i < n; i++)
        {
            scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
            dat d(x1, y1, x2, y2, i);
            bian->Insert(d);
        }
    }
    scanf("%f %f", &x1, &y1);
    DoubleList<dat>* xu = new DoubleList<dat>;
    dat c(x1, y1, 0);
    xu->Insert(c);
    if(n > 1)
    {
        for(i = 1; i < n; i++)
        {
            scanf("%f %f", &x1, &y1);
            dat c(x1, y1, i);
            xu->Insert(c);
        }
    }


    int n1 = 0;
    while((xu->nwLength) && (n1 != xu->nwLength))//一个虚假的while循环，判读条件是现在是否还有幻灯片以及上一次没有进行for循环时的幻灯片数和现在的片数是否相等：如果相等，表明已经不能继续抽出幻灯片，跳出while循环。
    {
        n1 = xu->nwLength;
        Node<dat>* dot = xu->Head;
        for(i = 0; i < xu->nwLength; i++)//找每个点是否只落在一个幻灯片所在的区域内，如果只有一个则记下该序号，并且删除该幻灯片和序号；如果出现多于一个的情况，立即跳出for循环，进行对下一个序号点的检验工作；如果没有落入任何一个幻灯片，则表明无解，直接输出-1停止。
        {
            Node<dat>* node = bian->Head;
            Node<dat>* cur;
            x1 = dot->data.x1;
            y1 = dot->data.y1;
            times = 0;
            for(j = 0; j < bian->nwLength; j++)
            {
                if((x1 > node->data.x1) && (x1 < node->data.x2) && (y1 > node->data.y1) && (y1 < node->data.y2))
                {
                    cur = node;
                    times++;
                    if(times > 1) break;
                }
                node = node->Next;
            }
            if(times == 0)
            {
                printf("-1\n");
                goto end;
            }
            else if(times == 1)
            {
                bh[cur->data.serial] = dot->data.serial + 1;
                dot = xu->Delete(dot);
                bian->Delete(cur);
            }
            else if(times > 1)
            {
                dot = dot->Next;
            }
        }
    }
    if(xu->nwLength != 0)//检查此时是否还有幻灯片，如果还有，则表明无解；否则打印出所需要的输出即可。
    {
        printf("-1\n");
        goto end;
    }
    else
    {
        for(i = 0; i < n; i++)
        {
            printf("%d %d\n", i + 1, bh[i]);
        }
    }
end:
    return 0;
}