#include<stdio.h>
#include<stdlib.h>
#include "DoubleList.h"
typedef enum status {NONE, UNDISCOVERED, DISCOVERED, VISITED} LAZYMARK;
DoubleList<dat>* head[100010] = {0};
LAZYMARK lazymark[100010] = {NONE};
Node<dat>* temp;
int longest;
int n, v1, v2, max;
long donfood ;
class queue
{
public:
    int que[100010];
    int head, tail;
    queue(): head(1), tail(0)
    {
    }
    bool empty()
    {
        if(head > tail)
            return 1;
        else return 0;
    }
    void enqueue(int d)
    {
        tail++;
        que[tail] = d;
    }
    int dequeue()
    {
        if(!empty())
        {
            head++;
            return que[head - 1];
        }
        return -1;
    }
};

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n-1; i++) //�������¼�뼰������������Ĺ���
    {
        scanf("%d %d %d", &v1, &v2, &max);
        if(lazymark[v1] == NONE)
        {
			lazymark[v1]= UNDISCOVERED;
            head[v1] = new DoubleList<dat>;
        }
        if(lazymark[v2] == NONE)
        {
            lazymark[v2] = UNDISCOVERED;
            head[v2] = new DoubleList<dat>;
        }
        dat e;
        e.max = max;
        e.amount = v2;
        e.ID = v1;
        head[v1]->Insert(e);
        e.amount = v1;
        e.ID = v2;
        head[v2]->Insert(e);
    }
    int s = 0;//0<=s<n
	int v=s+1;//1<=v<n+1
    do //��һ������ж���
        if (UNDISCOVERED == lazymark[v]) //һ��������δ���ֵĶ���
        {
            queue Q; //���븨������
            lazymark[v] = DISCOVERED;
            Q.enqueue(v); //��ʼ�����
            while (!Q.empty())
            {
                int Village = Q.dequeue();
                for (Node<dat>* u = head[Village]->Head; u != NULL; u = u->Next) //ö��v�������ھ�u
                    if (UNDISCOVERED == lazymark[u->data.amount])   //��u��δ�����֣���
                    {
                        lazymark[u->data.amount] = DISCOVERED;
                        head[u->data.amount]->almax = head[Village]->almax + u->data.max;
                        if(head[u->data.amount]->almax > donfood)
                        {
                            longest = u->data.amount;
                            donfood = head[u->data.amount]->almax;
                        }
                        Q.enqueue(u->data.amount); //���ָö���
                    }
                lazymark[v] = VISITED; //���ˣ���ǰ����������
            }
        }
    while ((v-1) != (s = (++s % n ))); //����ż�飬�ʲ�©����
    s = 1;
    while(head[s] != NULL)//reset
    {
        temp = head[s]->Head;
        lazymark[s] = UNDISCOVERED;
        head[s]->almax = 0;
        s++;
    }

    donfood = 0;
    s = longest-1;
    v = s+1;
    do //��һ������ж���
        if (UNDISCOVERED == lazymark[v]) //һ��������δ���ֵĶ���
        {
            queue Q; //���븨������
            lazymark[v] = DISCOVERED;
            Q.enqueue(v); //��ʼ�����
            while (!Q.empty())
            {
                int Village = Q.dequeue();
                for (Node<dat>* u = head[Village]->Head; u != NULL; u = u->Next) //ö��v�������ھ�u
                    if (UNDISCOVERED == lazymark[u->data.amount])   //��u��δ�����֣���
                    {
                        lazymark[u->data.amount] = DISCOVERED;
                        head[u->data.amount]->almax = head[Village]->almax + u->data.max;
                        if(head[u->data.amount]->almax > donfood)
                        {
                            longest = u->data.amount;
                            donfood = head[u->data.amount]->almax;
                        }
                        Q.enqueue(u->data.amount); //���ָö���
                    }
                lazymark[v] = VISITED; //���ˣ���ǰ����������
            }
        }
    while ((v-1) != (s = (++s % (n+1)))); //����ż�飬�ʲ�©����

    printf("%ld\n", donfood);
    return 0;
}