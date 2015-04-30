#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;
#define maxname 10010
#define maxnum 1010
char first[maxname];
int out[maxnum];//��¼��Ҫ����ı��
char name[2 * maxname];
unsigned int hashnum;
int n , m ;
int* buildNext(char* P);
void getMin(char* S)
{
    int i = 0, j = 1;
    int len=n;
    while(i < len && j < len)
    {
        int k = 0;
        while(k < len && S[i + k] == S[j + k])
            ++k;
        if(k >= len)
            break;
        if(S[i + k] > S[j + k])
            i = (i + k + 1 > j + 1) ? i + k + 1 : j + 1;
        else
            j = (i + 1 > j + k + 1) ? i + 1 : j + k + 1;
    }
    int pos = (i < j) ? i : j;
	if(pos<=len)
	{
    for(int i = 0; i < len; ++i)
        first[i] = S[pos++];
	}
}
struct Node//��¼ÿ������������ֵ�����ʱ��
{
    int ftime;//��¼ÿ�����ֵ�һ�γ��ֵı��
    char name[maxname];
    Node* next;
    Node()
    {
        ftime = -1;
        memset(name, 0, maxname);
        next = NULL;
    }
};
class list//��hash�õ���������Node���
{
public:
    int n;
    Node* cur;
    Node* head;
    void insert(char* name, int time)
    {
        Node*   node = new Node;
        if(head == NULL)
        {
            cur = node;
            head = node;
        }
        else
        {
            cur->next = node;
            cur = node;
        }
        strcpy(cur->name, name);//��ʼʱ�������if֮ǰ�������˷��ʴ���
        node->ftime = time;
    }
    list()
    {
        cur = NULL;
        head = NULL;
        n = 0;//��¼�м����ڵ�
    }
};
int main()
{
    cin >> m >> n;
	bool lazymark[maxname]={false};
	list* diary[maxname];
    for(int i = 0; i < m; i++)
    {
        scanf("%s",name);
        hashnum = 0; //�ǵ�Ҫ��ʼ�� 
        for(int j = 0; j < n-1 ; j++) //¼������
        {
            name[j + n] = name[j];
        }
        getMin(name);
        for(int j = 1; j < n; j++)
        {
            hashnum += (int)first[j] >>j; //hash����
        }
        int serial = hashnum % 10007;
        if(lazymark[serial] == false)//��lazymark(�����ǣ���¼�������Ƿ��Ѿ������������δ������������ӽڵ�
        {
            lazymark[serial] = true;
            diary[serial] = new list();
            diary[serial]->insert(first, i + 1);
            diary[serial]->n++;
            out[i] = 0;
        }
        else//����ֱ���ڽڵ��������
        {
            Node* temp = diary[serial]->head;
			int j=0;
            for(j; j < diary[serial]->n; j++)
            {
                if(strcmp(temp->name, first) == 0)
                {
                    out[i] = temp->ftime;
                    break;
                }
                temp = temp->next;
            }
            if(j==diary[serial]->n)
            {
                diary[serial]->insert(first, i + 1);
                out[i] = 0;
				diary[serial]->n++;
            }
        }
    }
    for(int i = 0; i < m; i++)
    {
        cout << out[i] << endl;
    }
	//system("pause");
    return 0;
}

