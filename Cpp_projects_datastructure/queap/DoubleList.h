#ifndef NULL
#define NULL 0
#endif

typedef unsigned int UNINT;

struct dat//max��¼ָ��ָ����������ֵ��amount��¼ǰ���м�����maxС����������max����
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



template <class DataType>//���캯��
DoubleList<DataType>::DoubleList()
{
    Head = Tail = NULL;
    nwLength = 0;
}


template <class DataType>
DoubleList<DataType>::~DoubleList()//��������
{
    DeleteAll();
}

//*=======================================================================
//*   �� �� ��:   int CDoubleList<DataType>::Insert(DataType newNode)
//*   ��������:   ������׷�ӽڵ�
//*   ��    ��:   <DataType> newNode  -  ����ڵ������
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
//*   �� �� ��:   void CDoubleList<DataType>::Insert(UNINT nwIndex, DataType newNode)
//*   ��������:   ��ָ��λ�ò���ڵ�,��nwIndex������,��������׷�ӽڵ�
//*   ��    ��:   UNINT nwIndex       -  ����ڵ�λ��,��0��ʼ.
//*               <DataType> newNode  -  ����ڵ������
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

    if (Temp->Pre == NULL)              /*��ͷ������ڵ�*/
    {
        NewNode->Next  =  Head;
        Head             =  NewNode;
    }
    else                                    /*���м����ڵ�*/
    {
        Temp->Pre->Next    =  NewNode;
        NewNode->Pre       =  Temp->Pre;
        NewNode->Next      =  Temp;
        Temp->Pre          =  NewNode;
    }

    ++ nwLength;

}

//*=======================================================================
//*   �� �� ��:   void CDoubleList<DataType>::DeleteAll()
//*   ��������:   ɾ�����нڵ�
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
//*   �� �� ��:   size_t CDoubleList<DataType>::Delete(UNINT nwIndex)
//*   ��������:   ɾ�������е�ָ���ڵ�,��nwIndex������,��ɾ��β�ڵ�
//*   ��    ��:   UNINT nwIndex  -  ����ɾ���Ľڵ��±�,��0��ʼ.

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

    if (Temp->Pre == NULL)              /*ɾ��ͷ���         (�ѱ�֤�ý�㲻��β�ڵ�)*/
    {
        Head         =  Head->Next;
        Head->Pre  =  NULL;
    }
    else                                    /*ɾ���м�ڵ�       (�ѱ�֤�ý�㲻��β�ڵ�) */
    {
        Temp->Pre->Next  =  Temp->Next;
        Temp->Next->Pre  =  Temp->Pre;
    }
    delete Temp;


    -- nwLength;
}

//*=======================================================================
//*   �� �� ��:   void CDoubleList<DataType>::DeleteLast()
//*   ��������:   ɾ�����������һ���ڵ�
//*   ��    ��:   ��

//=======================================================================*/
template <class DataType>
void DoubleList<DataType>::DeleteLast()
{
    if (Tail == NULL)
        return;

    if (Tail == Head /*<=>  lpTail->lpPre == NULL   <=>  nwLength == 1 */)
    {
        delete Head;                      /*ɾ��Ψһ�ڵ�       (�ýڵ����ͷ�������β�ڵ�)*/
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
//*   �� �� ��:   DataType &CDoubleList<DataType>::GetAt(UNINT nwIndex)
//*   ��������:   ����������ָ���ڵ������,��nwIndex������,�򷵻�β�ڵ������
//*   ��    ��:   UNINT nwIndex  -  Ҫ���صĽڵ��±�,��0��ʼ
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
//*   �� �� ��:   void CDoubleList<DataType>::SetAt(UNINT nwIndex, DataType newNode)
//*   ��������:   �޸�������ָ���±������,��nwIndex������,���޸�β�ڵ������
//*   ��    ��:   UNINT nwIndex       -  Ҫ�޸ĵĽڵ���±�,��0��ʼ
//*               <DataType> newNode  -  Ҫ�޸ĵĽڵ������

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

