#ifndef NULL
#define NULL 0
#endif

typedef unsigned int UNINT;

struct dat//max��¼ָ��ָ����������ֵ��amount��¼ǰ���м�����maxС����������max����
{
public:
    float x1, x2, y1, y2;
    int serial;
    dat()
    {
        x1 = 0;
        x2 = 0;
        y1 = 0;
        y2 = 0;
        serial = 0;
    }
    dat(float x1, float y1, float x2, float y2, int serial): x1(x1), y1(y1), x2(x2), y2(y2), serial(serial)
    {
    }
    dat(float x1, float y1, int serial): x1(x1), y1(y1), x2(0), y2(0), serial(serial)
    {
    }
};

template <class DataType>
class Node
{
public:
    Node();
    Node(dat data, Node *Next, Node *Pre) ;
    ~Node();
    dat  data;
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
    Node<dat>*             Delete(Node<dat>* node);
    void             DeleteAll();
    Node<dat>*             DeleteLast();

    DataType         &GetAt(UNINT nwIndex);
    void             SetAt(UNINT nwIndex, DataType newNode);


    int           nwLength;
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
Node<dat>* DoubleList<DataType>::Delete(Node<dat>* node)
{
    if (Head == NULL)
        return NULL;

    if (node->Next == NULL)
        return DeleteLast();

    if (node->Pre == NULL)              /*ɾ��ͷ���         (�ѱ�֤�ý�㲻��β�ڵ�)*/
    {
        Head         =  Head->Next;
        delete Head->Pre;
        Head->Pre  =  NULL;
        -- nwLength;
        return Head;
    }
    else                                    /*ɾ���м�ڵ�       (�ѱ�֤�ý�㲻��β�ڵ�) */
    {
        Node<dat>* cur;
        node->Pre->Next  =  node->Next;
        cur = node->Next;
        node->Next->Pre  =  node->Pre;
        delete node;
        -- nwLength;
        return cur;
    }



}

//*=======================================================================
//*   �� �� ��:   void CDoubleList<DataType>::DeleteLast()
//*   ��������:   ɾ�����������һ���ڵ�
//*   ��    ��:   ��

//=======================================================================*/
template <class DataType>
Node<dat>* DoubleList<DataType>::DeleteLast()
{
    if (Tail == NULL)
        return NULL;

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
    return Tail;
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

