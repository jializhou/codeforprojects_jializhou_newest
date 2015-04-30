//���ò��޸��˵˿�����ʦbinTree�����ͷ�ļ�BinNode.h�����ͷ�ļ�
#pragma once
#define NULL 0


/******************************************************************************************
 * BinNode״̬�����ʵ��ж�
 ******************************************************************************************/
#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))

template <typename T>
struct BinNode { //�������ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
   T data; //��ֵ
   BinNodePosi(T) parent; BinNodePosi(T) lChild; BinNodePosi(T) rChild; //���ڵ㼰���Һ���
// ���캯��
   BinNode() : parent(NULL), lChild(NULL), rChild(NULL){ }
   BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL)
      : data(e), parent(p), lChild(lc), rChild(rc){ }
// �����ӿ�
   int size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
   BinNodePosi(T) insertAsLC(T const &); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
   BinNodePosi(T) insertAsRC(T const &); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
};
template <typename T> //��e��Ϊ��ǰ�ڵ�����Ӳ��������
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e) {  return lChild = new BinNode(e, this);  }

template <typename T> //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e) {  return rChild = new BinNode(e, this);  }




