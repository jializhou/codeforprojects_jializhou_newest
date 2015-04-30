#include<stdio.h>
#include<stdlib.h>

struct Node
{
    //建立结构体
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

bool Stack::empty()//判断栈是否为空
{
    return NULL == head;
}
void Stack::push(int num) //将一个数字压入以head为头的堆栈
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
        nextNode->next = head;//尾插法
        head = nextNode;
    }
}
int Stack::pop() ////弹出栈顶元素并返回其数值
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
int Stack::top()//仅获取栈顶元素的值，但不弹出
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
    Stack A, B, S;//构建了A,B,S三个栈。先将输入的样例数据放入一个数组中。初始化栈A，使之为1，2，...，n
    scanf("%d", &n);
    scanf("%d", &m);
    while(i < n)
    {
        scanf("%d", &num[i]);
        i++;
    }
    i = 0;
    while(i < n)//模拟栈混洗，在S中的Node不超过m节的条件下，用push,pop操作看是否能生成B（数据的比较在中间完成）
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
