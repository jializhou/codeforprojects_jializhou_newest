#include<stdio.h>
#include<stdlib.h>
#include"DoubleList.h"

int main()
{
    int n, i = 0, j = 0, bh[1000] = {0}, times;
    float x1, x2, y1, y2;
    scanf("%d", &n);
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    DoubleList<dat>* bian = new DoubleList<dat>;//ʹ�������������ֱ�洢��Ŷ�Ӧ�Ļõ�Ƭ���������Ӧ�����꣬�Լ���Ŷ�Ӧ�ĵ�����ꡣ
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
    while((xu->nwLength) && (n1 != xu->nwLength))//һ����ٵ�whileѭ�����ж������������Ƿ��лõ�Ƭ�Լ���һ��û�н���forѭ��ʱ�Ļõ�Ƭ�������ڵ�Ƭ���Ƿ���ȣ������ȣ������Ѿ����ܼ�������õ�Ƭ������whileѭ����
    {
        n1 = xu->nwLength;
        Node<dat>* dot = xu->Head;
        for(i = 0; i < xu->nwLength; i++)//��ÿ�����Ƿ�ֻ����һ���õ�Ƭ���ڵ������ڣ����ֻ��һ������¸���ţ�����ɾ���ûõ�Ƭ����ţ�������ֶ���һ�����������������forѭ�������ж���һ����ŵ�ļ��鹤�������û�������κ�һ���õ�Ƭ��������޽⣬ֱ�����-1ֹͣ��
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
    if(xu->nwLength != 0)//����ʱ�Ƿ��лõ�Ƭ��������У�������޽⣻�����ӡ������Ҫ��������ɡ�
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