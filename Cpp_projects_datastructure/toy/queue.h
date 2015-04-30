#ifndef NULL
#define NULL 0
#endif
#include"Cyclic.h"

class Stack
{
public:
    Stack()
    {
        head = NULL;
    }
    bool empty();
    void push(dat);
    dat pop();
    dat top();
private:
    node* head;
};

bool Stack::empty()//判断栈是否为空
{
    return NULL == head;
}
void Stack::push(dat num) //将一个数字压入以head为头的堆栈
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
dat Stack::pop() ////弹出栈顶元素并返回其数值
{
    node *temp;
    dat num;
    if(NULL != head)
    {
        num = head->num;
        temp = head->next;
        delete head;
        head = temp;
        return num;
    }
}
dat Stack::top()//仅获取栈顶元素的值，但不弹出
{
    if(NULL != head)
    {
        return head->num;
    }
}
class queue
{
public:
    queue(): length(0),head(NULL) {}
    void enqueue(dat);
    dat dequeue();
    int length;
    node* head;
	bool empty()
	{
		return length==0;
	}
	Stack s1,s2;
};

dat queue::dequeue()
{
	dat n;
	if(!s2.empty())
		n=s2.pop();
	else
	{
		while(!s1.empty())
			s2.push(s1.pop());
		n=s2.pop();
	}
	length--;
	return n;
}
void queue::enqueue(dat num)
{
	int i=0;
	s1.push(num);
	length ++;
}


