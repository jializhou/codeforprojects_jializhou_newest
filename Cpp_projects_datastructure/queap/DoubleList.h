#ifndef NULL
#define NULL 0
#endif

typedef unsigned int UNINT;

struct dat//max记录指针指向的最大数的值，amount记录前面有几个比max小的数，包括max本身
{
public:
    int x1,x2,y1,y2;
    dat()
    {
        x1 = 0;
        x2 = 0;
		y1=0;
		y2=0;
    }
    dat(int x1, int y1,int x2,int y2): x1(x1),y1(y1),x2(x2),y2(y2)
    {
    }
	dat(int x1,int y1):x1(x1),y1(y1),x2(0),y2(0)
};

template <class DataType>
class Node
{
public:
    Node();
    Node(dat data, Node *Next, Node *Pre) ;
    ~Node();
    DataType  data;
    Node*    Next;
    Node*    Pre;
};
template<class DataType>
Node<DataType>::Node()
{
    dat p;
    data = p;
    Next = NULL;
    Pre = NULL;
}

template<class DataType>
Node<DataType>::Node(dat data, Node *Next, Node *Pre) : data(data), Next(Next), Pre(Pre) { }

template <class DataType>
Node<DataType>::~Node()
{
}

template <class DataType>
class DoubleList
{
public:
    DoubleList();
    ~DoubleList();

    int              Insert(dat  newNode);
    void             Insert(UNINT nwIndex, DataType newNode);
    void             Delete(UNINT nwIndex);
    void             DeleteAll();
    void             DeleteLast();

    DataType         &GetAt(UNINT nwIndex);
    void             SetAt(UNINT nwIndex, DataType newNode);


    size_t           nwLength;
    Node<DataType>  *Head;
    Node<DataType>  *Tail;
};



template <class DataType>//构造函数
DoubleList<DataType>::DoubleList()
{
    Head = Tail = NULL;
    nwLength = 0;
}


template <class DataType>
DoubleList<DataType>::~DoubleList()//析构函数
{
    DeleteAll();
}

//*=======================================================================
//*   函 数 名:   int CDoubleList<DataType>::Insert(DataType newNode)
//*   功能描述:   向链表追加节点
//*   参    数:   <DataType> newNode  -  插入节点的数据
//=======================================================================*/
template <class DataType>
int DoubleList<DataType>::Insert(dat  e)
{
    Node<dat>* NewNode = new Node<dat>;
    NewNode->data = e;
    if (Head == NULL)
        Head     =  NewNode;
    else if (Tail != NULL)
        Tail->Next  =  NewNode;
    NewNode->Pre  =  Tail;
    Tail     =  NewNode;

    ++ nwLength;
    return 1;

}

//*=======================================================================
//*   函 数 名:   void CDoubleList<DataType>::Insert(UNINT nwIndex, DataType newNode)
//*   功能描述:   向指定位置插入节点,若nwIndex不存在,则向链表追加节点
//*   参    数:   UNINT nwIndex       -  插入节点位置,从0开始.
//*               <DataType> newNode  -  插入节点的数据
//=======================================================================*/
template <class DataType>
void DoubleList<DataType>::Insert(UNINT nwIndex, DataType newNode)
{
    if (nwIndex >= nwLength)
        return Insert(newNode);

    Node<DataType> *Temp, *NewNode;
    Temp     =  Head;
    NewNode  =  new Node<DataType>;
    if (NewNode == NULL)
        return 0;

    NewNode->data = newNode;

    for (UNINT nI = 0; nI < nwIndex && Temp->Next; nI ++)
        Temp = Temp->Next;

    if (Temp->Pre == NULL)              /*在头部插入节点*/
    {
        NewNode->Next  =  Head;
        Head             =  NewNode;
    }
    else                                    /*在中间插入节点*/
    {
        Temp->Pre->Next    =  NewNode;
        NewNode->Pre       =  Temp->Pre;
        NewNode->Next      =  Temp;
        Temp->Pre          =  NewNode;
    }

    ++ nwLength;

}

//*=======================================================================
//*   函 数 名:   void CDoubleList<DataType>::DeleteAll()
//*   功能描述:   删除所有节点
//=======================================================================*/
template <class DataType>
void DoubleList<DataType>::DeleteAll()
{
    if (Head == NULL)
        return;

    Node<DataType> *Temp;
    while (Head)
    {
        Temp  =  Head->Next;
        delete Head;
        Head  =  Temp;
    }

    Head = Tail = NULL;
    nwLength = 0;
}


//*=======================================================================
//*   函 数 名:   size_t CDoubleList<DataType>::Delete(UNINT nwIndex)
//*   功能描述:   删除链表中的指定节点,若nwIndex不存在,则删除尾节点
//*   参    数:   UNINT nwIndex  -  即将删除的节点下标,从0开始.

//=======================================================================*/
template <class DataType>
void DoubleList<DataType>::Delete(UNINT nwIndex)
{
    if (Head == NULL)
        return;

    if (nwIndex >= nwLength - 1)
        return DeleteLast();

    Node<DataType> *Temp;
    Temp = Head;

    for (UNINT nI = 0; nI < nwIndex && Temp->Next; nI ++)
        Temp = Temp->Next;

    if (Temp->Pre == NULL)              /*删除头结点         (已保证该结点不是尾节点)*/
    {
        Head         =  Head->Next;
        Head->Pre  =  NULL;
    }
    else                                    /*删除中间节点       (已保证该结点不是尾节点) */
    {
        Temp->Pre->Next  =  Temp->Next;
        Temp->Next->Pre  =  Temp->Pre;
    }
    delete Temp;


    -- nwLength;
}

//*=======================================================================
//*   函 数 名:   void CDoubleList<DataType>::DeleteLast()
//*   功能描述:   删除链表中最后一个节点
//*   参    数:   无

//=======================================================================*/
template <class DataType>
void DoubleList<DataType>::DeleteLast()
{
    if (Tail == NULL)
        return;

    if (Tail == Head /*<=>  lpTail->lpPre == NULL   <=>  nwLength == 1 */)
    {
        delete Head;                      /*删除唯一节点       (该节点既是头结点又是尾节点)*/
        Head = Tail = NULL;
    }
    else
    {
        Tail          =  Tail->Pre;
        delete Tail->Next;
        Tail->Next  =  NULL;
    }

    -- nwLength;
}

//*=======================================================================
//*   函 数 名:   DataType &CDoubleList<DataType>::GetAt(UNINT nwIndex)
//*   功能描述:   返回链表中指定节点的数据,若nwIndex不存在,则返回尾节点的数据
//*   参    数:   UNINT nwIndex  -  要返回的节点下标,从0开始
//=======================================================================*/
template <class DataType>
DataType &DoubleList<DataType>::GetAt(UNINT nwIndex)
{
    if (nwIndex == 0)
        return Head->data;

    if (nwIndex == nwLength - 1)
        return Tail->data;

    Node<DataType> *Temp;
    Temp = Head;

    for (UNINT nI = 0; nI < nwIndex && Temp->Next; nI ++)
        Temp = Temp->Next;

    return Temp->data;
}

//*=======================================================================
//*   函 数 名:   void CDoubleList<DataType>::SetAt(UNINT nwIndex, DataType newNode)
//*   功能描述:   修改链表中指定下标的数据,若nwIndex不存在,则修改尾节点的数据
//*   参    数:   UNINT nwIndex       -  要修改的节点的下标,从0开始
//*               <DataType> newNode  -  要修改的节点的数据

//=======================================================================*/
template <class DataType>
void DoubleList<DataType>::SetAt(UNINT nwIndex, DataType newNode)
{
    if (Head == NULL)
        return;

    Node<DataType> *Temp;
    Temp = Head;

    if (nwIndex == nwLength - 1)
        Temp = Tail;
    else
        for (UNINT nI = 0; nI < nwIndex && Temp->Next; nI ++)
            Temp = Temp->Next;

    Temp->data = newNode;
}

