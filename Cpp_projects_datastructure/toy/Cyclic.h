
#ifndef _Cyclic_H

#define _Cyclic_H
#define hashnum 9973
typedef class Dat
{
public:
    int up;
    int down;
	int clock;
Dat():up(0),down(0),clock(-1)
	{
	}
}dat;
typedef struct Node
{
    dat  num;
    Node* next, *prior;
}node;
typedef class cyclic
{
public:
    cyclic(int n1);//���ع��캯��,����ѭ������(��˫�������죩
    void take();//ȡ����һ��Ԫ��
    void left();//��������
    void right();//��������
	void down();
    void clockwise();//�м䲿��˳ʱ����ת
    void turn();//�м䲿����ʱ����ת
    void change(dat v);
    dat renum(int myclock);
    ~cyclic();//�ͷŶ���
    node *head;
    int n;//4λ
   /* Cyclic *b;*/
}Cyclic;


void Cyclic::change(dat v)
{
    node* temp1 = head;
    for(int i = 0; i < 4; i++)
    {
		int dot = v.up %10;
		v.up = v.up/10;
        temp1->num.down = dot;
        temp1 = temp1->next;
    }
	temp1= temp1->prior;
    for(int i = 0; i < 4; i++)
    {
		int dot = v.up %10;
		v.up = v.up/10;
        temp1->num.up = dot;
        temp1 = temp1->prior;
    }
}
void Cyclic::clockwise()
{
    node* temp = head;
    temp = temp->next;
    int change;
    change = temp->num.up;
    temp->num.up = temp->num.down;
    temp->num.down = temp->next->num.down;
    temp = temp->next;
    temp->num.down = temp->num.up;
    temp->num.up = change;
}
void Cyclic::turn()
{
    node* temp = head;
    temp = temp->next;
    int change;
    change = temp->num.up;
    temp->num.up = temp->next->num.up;
    temp->next->num.up = temp->next->num.down;
    temp->next->num.down = temp->num.down;
    temp->num.up = change;
}

Cyclic::cyclic(int n1)
{
    n = n1;
    node *temp = NULL;
    head = new node ;
    head->num.up = 1;
    head->num.down = n;
    head->next = head;//��ֻ��һ��nodeʱ������ѭ��,��һ�ڵ�Ϊnull
    head->prior = head;
    if(n > 1)
    {
        for ( int i = 1; i < n / 2; i ++) //�������ɽڵ�ʱ��β���
        {
            temp = new node ;
            temp->num.up = i + 1;
            temp->num.down = n - i;
            temp->prior = head->prior;
            temp->next = head;
            head->prior->next = temp;
            head->prior = temp;
        }
    }
    n = n1 / 2;
}
void Cyclic::take()
{
    node* cur = head;
    if(head->next == head)//ֻ��һ���ڵ�����
    {
        head = NULL;
        delete cur;
    }
    else //�����������Ͻڵ�ʱ
    {

        head->next->prior = head->prior;
        head->prior->next = head->next;
        head = head->next;
        delete cur;
    }
}
void Cyclic::left()
{
    head = head->next;
}
void Cyclic::right()
{
    head = head->prior;
}
Cyclic:: ~cyclic()
{
    while(head != NULL)
    {
        take();
    }
}

void Cyclic::down()
{
	node* temp =head;
	int dot;
	for(int i=0;i<4;i++)
	{
	dot = temp->num.down;
	temp->num.down=temp->num.up;
	temp->num.up = dot;
	temp=temp->next;
	}
}
dat Cyclic:: renum(int myclock)
{
    dat num1;
	num1.clock=myclock;
    num1.down = 0;
    num1.up = 0;
    node* temp = head;
    for(int i = 0; i < 4; i++)
    {
        num1.up = num1.up * 10 + temp->num.up;
        temp = temp->next;
    }
	temp=temp->prior;
    for(int i = 0; i < 4; i++)
    {
        num1.up = num1.up * 10 + temp->num.down;
        temp = temp->prior;
    }
    num1.down = num1.up % hashnum;
    return num1;
}
#endif