#include <iostream>
using namespace std;

class node
{
public:
	int id;
	node *next;
};

node *createtable(int n,int m);//����ͷβ�����������ʱ�뷽����ӣ�
void sort(node* tail,int n);//�������������в����ID
void free(node* tail,int n);//�ͷ�����

int main()
{
	int n,m;
	cin>>n>>m;//��������
	node *tail=createtable(n,m);
	sort(tail,n);
	free(tail,n);
	return 0;
}

node *createtable(int n,int m)
{
	node *temp[1000] = {0}, *tail = NULL, *head = NULL,*cur=NULL ;
	int id[1000]={0},i;
	for(i=0;i<n;i++)
	{
		cin>>id[i];
	}
    head = new node; 
	head->id = id[0];
    head->next = head;
    tail = head;
	if(n>1)
	{
		temp[0]=head;
		for ( i = 1; i < n; i ++) 
		{
			temp[i] = new node ;
			temp[i]->id = id[i];
			cur=temp[i-1];
			for(int j=1;j<m;j++)
			{
				cur=cur->next;
			}
			temp[i]->next=cur->next;
			cur->next=temp[i];
			tail=temp[i];
		}
	}
	return tail ;
}

void sort(node* tail,int n)//ѡ�������������������������ÿ�������ߵ�ID��������peo�У�Ȼ�����Ž�ID���������
{
	int peo[1000],i=0;
	node *cur=tail;
	for(i=0;i<n;i++)
	{
		peo[i]=cur->next->id;
		cur=cur->next;
	}
	for(i=n-1;i>0;i--)
	{
		cout<<peo[i]<<' ';
	}
	cout<<peo[0]<<endl;
}

void free(node* tail,int n)//�ͷ�ռ�õĿռ�
{
	int i=0;
	node *curnode=tail,*successor=NULL;
	for(i=0;i<n;i++)
	{
		successor=curnode->next;
		delete curnode;
		curnode=successor;
	}
}