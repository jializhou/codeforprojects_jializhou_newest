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
    Cyclic(int n1);//重载构造函数,创建循环队列(用双向链表构造）
    void take();//取出第一个元素
    void left();//队列左移
    void right();//队列右移
	~Cyclic();//释放队列
    node *head;
    int n;
};

Cyclic::Cyclic(int n1)
{
    n = n1;
    node *temp = NULL;
    head = new node ;
    head->num = 1;
    head->next = head;//当只有一个node时不构成循环,下一节点为null
    head->prior = head;
    if(n > 1)
    {
        for ( int i = 1; i < n; i ++) //当有若干节点时首尾相接
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
    if(head->next == head)//只有一个节点的情况
    {
        head = NULL;
        delete cur;
    }
    else //当有两个以上节点时
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
    int n, m, i = 0, a[5010] = {0}, count = 0, count1, count2; //n,m分别为规模和待取出的元素数目，a[5010]为从Q中依次取出的m个元素
    //count用来计算最少的移动次数，count1,count2分别作为单次左移或者右移移动次数的计数
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
        count1 = 0;//用count1计算取出一个元素左移所花的代价，count2=现有的元素个数-count1，比较count1与count2取较小者作为所选方案
        count2 = 0;
        head1 = C.head;//用head1复制了head指针
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


