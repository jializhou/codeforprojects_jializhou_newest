#include <iostream>
using namespace std;

struct node
{
	int  num;
	node *next;
};
node *create(int n);//创建链表
node *adaptive(int m,node*head,int k,int *b,int j);//查询链表中的元素并将其移到最前端
void free(node* head,int n);//释放链表

int main()
{
	int n,m,i=0;
	int b[100],a[100];
	cin>>n>>m;
	node*head=create(n);
	while(i<m)
	{
		cin>>a[i];//读入数字
		head=adaptive(a[i],head,n,b,i);
		i++;
	}
	for(i=0;i<m;i++)
	{
		cout<<b[i]<<endl;
	}
	free(head,n);
	return 0;
}

node *create(int n)
{
	node *temp = NULL, *tail = NULL, *head = NULL ;
	int num[100];
	for(int i=0;i<n;i++)
	{
		cin>>num[i];
	}
    head = new node ; 
	head->num = num[0];
    head->next = NULL;
    tail = head;
	if(n>1)
	{
		for ( int i = 1; i < n; i ++) 
		{
			temp = new node ;  
			temp->num = num[i];
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}
	}
	return head ;
}
node *adaptive(int m,node*head,int k,int*b,int j)
{
	node*curnode=head;
	int i=1,n=k;
	while((n!=0)&&(curnode->num != m))
	{
		i++;
		curnode=curnode->next;
		n--;
	}
	if(n==0) b[j]=-1;
	else
	{
		b[j]=i;
		if(i!=1)
		{
			node*front=head,*back=curnode->next;
			while(front->next!=curnode)
			{
				front=front->next;
			}
			front->next=back;
			curnode->next=head;
			head=curnode;
		}
	}
	return head;
}
void free(node* head,int n)
{
	int i=0;
	node *curnode=head,*successor=NULL;
	for(i=0;i<n;i++)
	{
		successor=curnode->next;
		delete curnode;
		curnode=successor;
	}
}