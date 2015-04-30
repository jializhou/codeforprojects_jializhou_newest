#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;

struct Node//记录每个姓名及其出现的次数
{
    int times;
    char name[9];//得是9位，如果是8位则出现corrupted
    Node* next;
    Node()
    {
        times = 0;
        memset(name, 0, 9);
        next = NULL;
    }
};
class list//由hash得到的链表，由node组成
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
        strcpy(cur->name, name);//开始时这个放在if之前，出现了访问错误
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
		hash=0;//记得要初始化
        for(int j = 0; j < strlen(name); j++)//录入姓名
        {
            hash = hash * 131 + (int)name[j];//hash函数
        }
        int serial = hash % 10007;
        if(lazymark[serial] == false)//用lazymark(懒惰标记）记录该姓名是否已经产生过。如果未产生，可以添加节点
        {
            lazymark[serial] = true;
            diary[serial] = new list();
            diary[serial]->insert(name);
            diary[serial]->n++;
        }
        else//否则直接在节点里面操作
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