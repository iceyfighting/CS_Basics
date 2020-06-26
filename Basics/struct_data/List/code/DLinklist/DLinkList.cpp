#include<iostream>
using namespace std;

//定义数据类型
//typedef void DLinkList;
//定义双向链表节点的数据类型
typedef struct tag_dLinkListNode
{
    struct tag_dLinkListNode *prev;
    struct tag_dLinkListNode *next;
    int data;
}DLinkList;

//将tail设置为全局变量
DLinkList *tail = NULL;

DLinkList*  DLinkList_Create(int n,DLinkList *head)
{
    if(n < 0)
    {
        cout << "输入结点个数错误!" << endl;

    }
    else
    {
        // 头插法建立双向链表
        
        DLinkList *ptemp = NULL;
        for(int i = 0;i< n;i++)
        {
            ptemp = new DLinkList;
            ptemp->data = i;

            if(head == NULL)
            {
                head = ptemp;
            }
            else
            {
                tail->next = ptemp;
                ptemp->prev= tail;
            }
            tail = ptemp;
        }
        
    }
    return head;
}

void DLinkListPrint(DLinkList *head)
{
    while(head)
    {
        cout << head->data << " ";
        head = head->next;
    }
}


void DLinkListPrintTail()
{
    while(tail)
    {
        cout << tail->data << " ";
        tail = tail->prev;
    }
}
//指定节点的前面插入
void DLinkList_Insert(DLinkList* head,int i,int data)
{
    int j;
    DLinkList *p,*s;
    p = head;
    j = 1;
    while(p && j < i)
    {
        p = p->next;
        ++j;
    }
    if( p==NULL || j>i)
    {
        return ;
    }
    s = (DLinkList*)malloc(sizeof(DLinkList));
    s->data = data;
    //断开1 连接4和5
    p->prev->next = s;//4
    s->next       = p;//5
    //断开2 连接3和6
    s->prev       = p->prev;//3
    p->prev       = s;//6
}

void DLinkList_Delete(DLinkList *head,int i)
{
    int j = 1;
    DLinkList *p;
    p = head;
    while(p && j < i)
    {
        p = p->next;
        ++j;
    }
    if(!p || j >i)
    {
        return;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
}

int main()
{
    DLinkList *head;
    head = NULL;
    int n = 5;
    head = DLinkList_Create(n,head);
    DLinkListPrint(head);
    cout << endl;

    DLinkListPrintTail();
    cout << endl;
    //在第一个位置添加元素10
    DLinkList_Insert(head,3,10);
    cout << "在第三个位置插入元素:10" << endl;
    DLinkListPrint(head);
    cout << endl;

    //在第4个位置删除元素
    DLinkList_Delete(head,4);
    cout << "在第四个位置删除元素:" << endl;
    DLinkListPrint(head);
    cout << endl;
}
