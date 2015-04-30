#include"BinNode.h"
#include "stdlib.h"
#include "stdio.h"
#include<iostream>
using namespace std;
#define NULL 0
//实现一个BinNode<int>*类型的栈Stack1
struct node1
{
    //建立结构体
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

void Stack1::push(BinNode<int>* num) //将一个数字压入以head为头的堆栈
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
        nextNode->next = head;//尾插法
        head = nextNode;
    }
}

BinNode<int>* Stack1::pop() ////弹出栈顶元素并返回其该元素
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

BinNode<int>* Stack1::top()//仅获取栈顶元素的值，但不弹出
{
    if(NULL != head)
    {
        return head->num;
    }
}

int main()
{
    int InD[5010];
    int PoD[5010];//将中序遍历序列和后续遍历序列放在InD和PoD中
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
    p->data = PoD[i];//后续序列的最后一个节点为根节点，确定root；
    root = p; //p指向根节点
    while(i >= 0 || j >= 0)
    {
        S1.push(p);//PoD[i]进栈
        while(PoD[i] != InD[j])//而中序遍历序列中的最后一个节点为该二叉树最右下的节点InD[j]，在存放中序序列的数组InD中找到该节点，
        {
            i--;
            p = new BinNode<int>;
            p->data = PoD[i];
            S1.top()->rChild = p; //PoD[i-1]的右孩子为PoD[i]
            S1.push(p);//PoD[i]进栈
        }
        S1.top()->rChild = NULL; //PoD[i]的右孩子为空
        i--;
        j--;
        q = S1.pop(); //退栈
        while((j >= 0) && (InD[j] == S1.top()->data))
        {
            q->lChild = NULL; //q的左孩子为空
            q = S1.pop();
            j--;
        }
        if(i >= 0 || j >= 0)
        {
            p = new BinNode<int>;
            p->data = PoD[i]; //q的左孩子为PoD[i]
            q->lChild = p;
        }
        else q->lChild = NULL;
    }

    Stack1 S2; //辅助栈,利用中序遍历验证正确性
    p = root;
    i = 0;
    while (true)
        if (p)
        {
            S2.push(p); //根节点进栈
            p = p->lChild; //深入遍历左子树
        }
        else if (!S2.empty())
        {
            p = S2.pop(); //尚未访问的最低祖先节点退栈
            if(p->data != InD[i])
            {
                cout << -1;
                return 0;
            }
            p = p->rChild; //遍历祖先的右子树
            i++;
        }
        else break;

    Stack1 S; //辅助栈
    p = root;
    i = 0;
    if (p) S.push(p); //根节点入栈
    while (!S.empty())
    {
        //在栈变空之前反复循环
        p = S.pop();
        if(i < num - 1)
        {
            printf("%d ", p->data); //弹出并访问当前节点，其非空孩子的入栈次序为
            i++;
        }
        else
            printf("%d", p->data);
        if (HasRChild(*p))
            S.push(p->rChild);
        if (HasLChild(*p))
            S.push(p->lChild); //先右后左
    }

}


