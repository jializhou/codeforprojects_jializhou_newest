#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;

struct Node//��¼ÿ������������ֵĴ���
{
    int times;
    char name[9];//����9λ�������8λ�����corrupted
    Node* next;
    Node()
    {
        times = 0;
        memset(name, 0, 9);
        next = NULL;
    }
};
class list//��hash�õ���������node���
{
public:
    int n;
    Node* cur;
    Node* head;
    void insert(char* name)
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
        node->times = 1;
    }
    list()
    {
        cur = NULL;
        head = NULL;
        n = 0;
    }
};
int main()
{
    int n=0, maxtimes=0;
    char maxname[9], name[9];
    unsigned long long hash = 0;
    bool lazymark[10007] = {false};
    list* diary[10007];
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        scanf("%s", name);
		hash=0;//�ǵ�Ҫ��ʼ��
        for(int j = 0; j < strlen(name); j++)//¼������
        {
            hash = hash * 131 + (int)name[j];//hash����
        }
        int serial = hash % 10007;
        if(lazymark[serial] == false)//��lazymark(�����ǣ���¼�������Ƿ��Ѿ������������δ������������ӽڵ�
        {
            lazymark[serial] = true;
            diary[serial] = new list();
            diary[serial]->insert(name);
            diary[serial]->n++;
        }
        else//����ֱ���ڽڵ��������
        {
            Node* temp = diary[serial]->head;
            int j = 0;
            for(temp; j < diary[serial]->n; j++)
            {
                if(strcmp(temp->name, name) == 0)
                {
                    temp->times++;
                    if(maxtimes < temp->times)
                    {
                        maxtimes = temp->times;
                        strcpy(maxname, temp->name);
                    }
                    break;
                }
                temp = temp->next;
            }
        }
    }
    printf("%s %ld\n", maxname, maxtimes);
    return 0;
}