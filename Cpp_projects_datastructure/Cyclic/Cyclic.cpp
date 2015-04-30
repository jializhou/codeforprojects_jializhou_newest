#include<stdio.h>
#include<stdlib.h>

struct node
{
    int  num;
    node* next, *prior;
};
class Cyclic
{
public:
    Cyclic(int n1);//���ع��캯��,����ѭ������(��˫�������죩
    void take();//ȡ����һ��Ԫ��
    void left();//��������
    void right();//��������
	~Cyclic();//�ͷŶ���
    node *head;
    int n;
};

Cyclic::Cyclic(int n1)
{
    n = n1;
    node *temp = NULL;
    head = new node ;
    head->num = 1;
    head->next = head;//��ֻ��һ��nodeʱ������ѭ��,��һ�ڵ�Ϊnull
    head->prior = head;
    if(n > 1)
    {
        for ( int i = 1; i < n; i ++) //�������ɽڵ�ʱ��β���
        {
            temp = new node ;
            temp->num = i + 1;
            temp->prior = head->prior;
            temp->next = head;
            head->prior->next = temp;
            head->prior = temp;
        }
    }
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
Cyclic:: ~Cyclic()
{
    while(head != NULL)
    {
        take();
    }
}
int main()
{
    int n, m, i = 0, a[5010] = {0}, count = 0, count1, count2; //n,m�ֱ�Ϊ��ģ�ʹ�ȡ����Ԫ����Ŀ��a[5010]Ϊ��Q������ȡ����m��Ԫ��
    //count�����������ٵ��ƶ�������count1,count2�ֱ���Ϊ�������ƻ��������ƶ������ļ���
    scanf("%d\n", &n);
    scanf("%d\n", &m);
    Cyclic C(n);
    node *head1 = C.head;
    for(i = 0; i < m - 1; i++)
    {
        scanf("%d ", &a[i]);
    }
    scanf("%d", &a[m - 1]);
    for(i = 0; i < m; i++)
    {
        count1 = 0;//��count1����ȡ��һ��Ԫ�����������Ĵ��ۣ�count2=���е�Ԫ�ظ���-count1���Ƚ�count1��count2ȡ��С����Ϊ��ѡ����
        count2 = 0;
        head1 = C.head;//��head1������headָ��
        while(head1->num != a[i])
        {
            head1 = head1->next;
            count1++;
        }
        count2 = C.n - count1;
        if(count1 > count2)
        {
            count += count2;
        }
        else
        {
            count += count1;
        }
        C.head = head1;
        C.take();
        C.n--;
    }
    printf("%d\n", count);
    C.~Cyclic();
    return 0;
}


