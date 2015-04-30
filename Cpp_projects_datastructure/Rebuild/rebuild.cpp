#include"BinNode.h"
#include "stdlib.h"
#include "stdio.h"
#include<iostream>
using namespace std;
#define NULL 0
//ʵ��һ��BinNode<int>*���͵�ջStack1
struct node1
{
    //�����ṹ��
    BinNode<int>* num;
    struct node1 *next;
};

class Stack1
{
public:
    Stack1()
    {
        head = NULL;
    }
    bool empty()
    {
        return NULL == head;
    }
    void push(BinNode<int>*);
    BinNode<int>* pop();
    BinNode<int>* top();
private:
    node1* head;
};

void Stack1::push(BinNode<int>* num) //��һ������ѹ����headΪͷ�Ķ�ջ
{
    node1 * nextNode = new node1;
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

BinNode<int>* Stack1::pop() ////����ջ��Ԫ�ز��������Ԫ��
{
    node1 *temp;
    BinNode<int>* num;
    if(NULL != head)
    {
        num = head->num;
        temp = head->next;
        delete head;
        head = temp;
        return num;
    }
}

BinNode<int>* Stack1::top()//����ȡջ��Ԫ�ص�ֵ����������
{
    if(NULL != head)
    {
        return head->num;
    }
}

int main()
{
    int InD[5010];
    int PoD[5010];//������������кͺ����������з���InD��PoD��
    int i, j , num;
    BinNode<int>* p = new BinNode<int>, *root, *q;
    Stack1 S1;
    p->data = -1;
    S1.push(p);
    scanf("%d", &num);
    for(i = 0; i < num; i++)
        scanf("%d", &InD[i]);
    for(i = 0; i < num; i++)
        scanf("%d", &PoD[i]);

    i = num - 1;
    j = num - 1;
    p = new BinNode<int>;
    p->data = PoD[i];//�������е����һ���ڵ�Ϊ���ڵ㣬ȷ��root��
    root = p; //pָ����ڵ�
    while(i >= 0 || j >= 0)
    {
        S1.push(p);//PoD[i]��ջ
        while(PoD[i] != InD[j])//��������������е����һ���ڵ�Ϊ�ö����������µĽڵ�InD[j]���ڴ���������е�����InD���ҵ��ýڵ㣬
        {
            i--;
            p = new BinNode<int>;
            p->data = PoD[i];
            S1.top()->rChild = p; //PoD[i-1]���Һ���ΪPoD[i]
            S1.push(p);//PoD[i]��ջ
        }
        S1.top()->rChild = NULL; //PoD[i]���Һ���Ϊ��
        i--;
        j--;
        q = S1.pop(); //��ջ
        while((j >= 0) && (InD[j] == S1.top()->data))
        {
            q->lChild = NULL; //q������Ϊ��
            q = S1.pop();
            j--;
        }
        if(i >= 0 || j >= 0)
        {
            p = new BinNode<int>;
            p->data = PoD[i]; //q������ΪPoD[i]
            q->lChild = p;
        }
        else q->lChild = NULL;
    }

    Stack1 S2; //����ջ,�������������֤��ȷ��
    p = root;
    i = 0;
    while (true)
        if (p)
        {
            S2.push(p); //���ڵ��ջ
            p = p->lChild; //�������������
        }
        else if (!S2.empty())
        {
            p = S2.pop(); //��δ���ʵ�������Ƚڵ���ջ
            if(p->data != InD[i])
            {
                cout << -1;
                return 0;
            }
            p = p->rChild; //�������ȵ�������
            i++;
        }
        else break;

    Stack1 S; //����ջ
    p = root;
    i = 0;
    if (p) S.push(p); //���ڵ���ջ
    while (!S.empty())
    {
        //��ջ���֮ǰ����ѭ��
        p = S.pop();
        if(i < num - 1)
        {
            printf("%d ", p->data); //���������ʵ�ǰ�ڵ㣬��ǿպ��ӵ���ջ����Ϊ
            i++;
        }
        else
            printf("%d", p->data);
        if (HasRChild(*p))
            S.push(p->rChild);
        if (HasLChild(*p))
            S.push(p->lChild); //���Һ���
    }

}


