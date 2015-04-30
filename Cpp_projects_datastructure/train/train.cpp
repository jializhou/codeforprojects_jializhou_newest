#include<stdio.h>
#include<stdlib.h>

struct Node
{
    //�����ṹ��
    int num;
    struct Node *next;
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
    Node* head;
};

bool Stack::empty()//�ж�ջ�Ƿ�Ϊ��
{
    return NULL == head;
}
void Stack::push(int num) //��һ������ѹ����headΪͷ�Ķ�ջ
{
    Node *nextNode = new Node;
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
    Node *temp;
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
    else return 0;
}


int main()
{
    int n, m, i = 0, j = 0, num[100100] = {0};
    Stack A, B, S;//������A,B,S����ջ���Ƚ�������������ݷ���һ�������С���ʼ��ջA��ʹ֮Ϊ1��2��...��n
    scanf("%d", &n);
    scanf("%d", &m);
    while(i < n)
    {
        scanf("%d", &num[i]);
        i++;
    }
    i = 0;
    while(i < n)//ģ��ջ��ϴ����S�е�Node������m�ڵ������£���push,pop�������Ƿ�������B�����ݵıȽ����м���ɣ�
    {
        if(0 == num[i])
            break;
        A.push(n - i);
        i++;
    }
    for(i = 0; i < n; i++)
    {
        j = 0;
        if(S.top() == num[i])
        {
            A.push(S.pop());
        }
        else
        {
            while((j < m) && (A.top() != num[i]) && (A.top() != 0))
            {
                S.push(A.pop());
                j++;
            }
            if(A.top() == num[i])
            {
                B.push(A.pop());
            }
            else
            {
                printf("No\n");
                goto end;
            }
        }
    }
    printf("Yes\n");
end:
    return 0;
}
