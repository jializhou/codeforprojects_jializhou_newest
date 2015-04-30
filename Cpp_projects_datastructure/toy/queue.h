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

bool Stack::empty()//�ж�ջ�Ƿ�Ϊ��
{
    return NULL == head;
}
void Stack::push(dat num) //��һ������ѹ����headΪͷ�Ķ�ջ
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
dat Stack::pop() ////����ջ��Ԫ�ز���������ֵ
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
dat Stack::top()//����ȡջ��Ԫ�ص�ֵ����������
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


