#include<stdio.h>
#include<stdlib.h>
#include "Cyclic.h"
#include"queue.h"
#include<iostream>
#include<string>
using namespace std;
//int hash_cal(int num);
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } Status;
Status lazymark[hashnum + 1] = {UNDISCOVERED};
int N;
int num[1001]={-1};

class hash//由hash得到的链表，由node组成
{
public:
    node* cur;
    node* head;
    void insert(dat v)
    {
        node* node1 = new node;
        if(head == NULL)
        {
            cur = node1;
            head = node1;
            node1->next = NULL;
        }
        else
        {
            cur->next = node1;
            cur = node1;
            node1->next = NULL;
        }
        cur->num.up = v.up;//up记录12345678
        cur->num.down = v.down;//hash
        cur->num.clock = v.clock;//clock记录最少要用的次数
    }
    hash()
    {
        cur = NULL;
        head = NULL;
    }
} myhash[hashnum + 1];

void BFS(dat u, queue* Q)
{
    if (UNDISCOVERED == lazymark[u.down]) //一旦遇到尚未发现的顶点
    {
        lazymark[u.down] = DISCOVERED;
        Q->enqueue(u);
    }
    else
    {
        node* temp = myhash[u.down].head;
        for(temp; temp != NULL; temp = temp->next)
        {
            if(temp->num.up == u.up)
            {
                break;
            }
        }
        if(temp == NULL)
        {
            Q->enqueue(u);
        }
    }
}
class toy
{
public:
    toy()
    {
        c = new Cyclic(8);
    }
    dat num(int myclock)
    {
        return c->renum(myclock);
    }
    Cyclic *c;
};

int main()
{
    int myclock = 0;
    dat v;
    toy mytoy;
    v.up = 12345678;
    v.down = v.up % hashnum;
    v.clock = 0;
	dat u;
    queue Q;
    lazymark[v.down] = DISCOVERED;
    Q.enqueue(v);
    while (!Q.empty())
    {
		  dat v = Q.dequeue();

        mytoy.c->change(v);//initialize mytoy
        node* temp = myhash[v.down].head;
        for(temp; temp != NULL; temp = temp->next)
        {
            if(temp->num.up == v.up)
            {
                goto classover;
            }
        }
        if(temp == NULL)
        {
            myhash[v.down].insert(v);
            myclock = v.clock + 1;
        }

        mytoy.c->down();
        u = mytoy.num(myclock);
        BFS(u, &Q);
        mytoy.c->down();

        mytoy.c->right();
        u = mytoy.num(myclock);
        BFS(u, &Q);
        mytoy.c->left();


        mytoy.c->clockwise();
        u = mytoy.num(myclock);
        BFS(u, &Q);
        mytoy.c->turn();

classover:
		lazymark[v.down] = VISITED;
    }

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        dat temp;
        temp.up = 0;
		int dot1[9],dot2[9];
        for(int j = 1; j < 9; j++)
        {
            scanf("%d", &dot1[j]);
			dot2[dot1[j]]=j;
        }
        for(int j = 1; j < 9; j++)
        {
			temp.up = temp.up * 10 + dot2[j];
        }
        temp.down = temp.up % hashnum;
        node* cur = myhash[temp.down].head;
        for(cur; cur != NULL; cur = cur->next)
        {
            if(cur == NULL)
                break;
            else if(temp.up == cur->num.up)
            {
                num[i]=cur->num.clock;
                break;
            }
        }
    }
	for(int i=0;i<N;i++)
	{
		printf("%d\n",num[i]);
	}
    return 0;
}


