#include<stdio.h>
#include<stdlib.h>
#include "DoubleList.h"
struct node
{
    //建立结构体
    int num;
    struct node *next;
};

class Stack
{
public:
    Stack()
    {
        head = NULL;
    }
    bool empty();
    void push(int);
    int pop();
    int top();
private:
    node* head;
};

bool Stack::empty()//判断栈是否为空
{
    return NULL == head;
}
void Stack::push(int num) //将一个数字压入以head为头的堆栈
{
    node *nextNode = new node;
    nextNode->num = num;

    if(NULL == head)
    {
        nextNode->next = NULL;
        head = nextNode;
    }
    else
    {
        nextNode->next = head;//尾插法
        head = nextNode;
    }
}
int Stack::pop() ////弹出栈顶元素并返回其数值
{
    node *temp;
    int num;
    if(NULL != head)
    {
        num = head->num;
        temp = head->next;
        delete head;
        head = temp;
        return num;
    }
}
int Stack::top()//仅获取栈顶元素的值，但不弹出
{
    if(NULL != head)
    {
        return head->num;
    }
}
//*=======================================================================
//*关于堆结构：每一个节点的数据成员data有两个，为num和max；num记录着包括该节点指

//*向的队元素在内的它之前比它小的元素个数，max记录指向的队元素的大小。因此总体的

//*空间复杂度很小，可以认为是o(1).
//=======================================================================*/
class Queap
{
public:
    Queap(): length(0), heap(NULL) {}
    void enqueap(int);
    int dequeap();
    int max();
private:
    Stack s1, s2;
    int length;
    DoubleList<dat> *heap;
};
//*=======================================================================
//*   函 数 名:   int Queap::dequeap()
//*   功能描述:   dequeap操作时，在s1的队首元素出队的同时，只需判断当前出队的元素是否为堆

//*heap首节点所指向的元素（说是指向，实则用存储的元素的大小进行比较来判断），如果

//*是的话，则删除首节点；如果不是，则只需将首节点记录的节点数目--即可
//=======================================================================*/
int Queap::dequeap()
{
    int n;
    if (!s2.empty())
        n = s2.pop();
    else
    {
        while (!s1.empty())
            s2.push(s1.pop());
        n = s2.pop();
    }
    if(heap->Head->data.amount == 1)
    {
        heap->Delete(0);
    }
    else
    {
        heap->Head->data.amount--;
    }
    length--;
    return n;
}
//*=======================================================================
//*   enqueap操作时，在s1的队尾元素入队的同时，需要判断入队元素的大小：
//*如果入队元素小于之前队尾元素，则只需要插入新队尾元素，并且生成新的堆尾指针指向

//*新队尾即可。
//*如果大于队尾元素，则需要在堆里向前回溯，找到某一指针里*p存的元素小于入队元素

//*num,此时将生成新的堆指针*cur,cur存入*p指向的队里元素i和入队元素num之间的元素个数

//=======================================================================*/
void Queap::enqueap(int num)
{
    int i = 0;
    s1.push(num);
    if (length == 0)//队列初始化
    {
        dat d(num, 1);
        heap = new DoubleList<dat>;
        heap->Insert(d);
    }
    else
    {
        if(heap->Tail->data.max > num)
        {
            dat d(num, 1);
            heap->Insert(d);
        }
        else
        {
            int amount = 1;
            while((heap->Tail) && (heap->Tail->data.max < num))
            {
                amount += heap->Tail->data.amount;
                heap->DeleteLast();
            }
            dat d(num, amount);
            heap->Insert(d);
        }
    }
    length++;
}
int Queap::max()
{
    if(heap->Head != NULL)
        return heap->Head->data.max;
}

int main()
{
    int n, i = 0;
    Queap queap;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        char way;
        int m;
        scanf("%c", &way);
        if((way == '\n') || (way == ' '))
        {
            scanf("%c", &way);
        }
        switch(way)
        {
        case 'E':
            scanf("%d", &m);
            queap.enqueap(m);
            break;
        case 'D':
            printf("%d\n", queap.dequeap());
            break;
        case 'M':
            printf("%d\n", queap.max());
            break;
        default:
            break;
        }
    }
    return 0;
}
