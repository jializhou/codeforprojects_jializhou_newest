#include<stdio.h>
#include<stdlib.h>
#include "DoubleList.h"
struct node
{
    //�����ṹ��
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

bool Stack::empty()//�ж�ջ�Ƿ�Ϊ��
{
    return NULL == head;
}
void Stack::push(int num) //��һ������ѹ����headΪͷ�Ķ�ջ
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
        nextNode->next = head;//β�巨
        head = nextNode;
    }
}
int Stack::pop() ////����ջ��Ԫ�ز���������ֵ
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
int Stack::top()//����ȡջ��Ԫ�ص�ֵ����������
{
    if(NULL != head)
    {
        return head->num;
    }
}
//*=======================================================================
//*���ڶѽṹ��ÿһ���ڵ�����ݳ�Աdata��������Ϊnum��max��num��¼�Ű����ýڵ�ָ

//*��Ķ�Ԫ�����ڵ���֮ǰ����С��Ԫ�ظ�����max��¼ָ��Ķ�Ԫ�صĴ�С����������

//*�ռ临�ӶȺ�С��������Ϊ��o(1).
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
//*   �� �� ��:   int Queap::dequeap()
//*   ��������:   dequeap����ʱ����s1�Ķ���Ԫ�س��ӵ�ͬʱ��ֻ���жϵ�ǰ���ӵ�Ԫ���Ƿ�Ϊ��

//*heap�׽ڵ���ָ���Ԫ�أ�˵��ָ��ʵ���ô洢��Ԫ�صĴ�С���бȽ����жϣ������

//*�ǵĻ�����ɾ���׽ڵ㣻������ǣ���ֻ�轫�׽ڵ��¼�Ľڵ���Ŀ--����
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
//*   enqueap����ʱ����s1�Ķ�βԪ����ӵ�ͬʱ����Ҫ�ж����Ԫ�صĴ�С��
//*������Ԫ��С��֮ǰ��βԪ�أ���ֻ��Ҫ�����¶�βԪ�أ����������µĶ�βָ��ָ��

//*�¶�β���ɡ�
//*������ڶ�βԪ�أ�����Ҫ�ڶ�����ǰ���ݣ��ҵ�ĳһָ����*p���Ԫ��С�����Ԫ��

//*num,��ʱ�������µĶ�ָ��*cur,cur����*pָ��Ķ���Ԫ��i�����Ԫ��num֮���Ԫ�ظ���

//=======================================================================*/
void Queap::enqueap(int num)
{
    int i = 0;
    s1.push(num);
    if (length == 0)//���г�ʼ��
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
