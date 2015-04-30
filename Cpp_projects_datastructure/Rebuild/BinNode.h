//引用并修改了邓俊辉老师binTree程序的头文件BinNode.h及相关头文件
#pragma once
#define NULL 0


/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define BinNodePosi(T) BinNode<T>* //节点位置
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))

template <typename T>
struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
   T data; //数值
   BinNodePosi(T) parent; BinNodePosi(T) lChild; BinNodePosi(T) rChild; //父节点及左、右孩子
// 构造函数
   BinNode() : parent(NULL), lChild(NULL), rChild(NULL){ }
   BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL)
      : data(e), parent(p), lChild(lc), rChild(rc){ }
// 操作接口
   int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
   BinNodePosi(T) insertAsLC(T const &); //作为当前节点的左孩子插入新节点
   BinNodePosi(T) insertAsRC(T const &); //作为当前节点的右孩子插入新节点
};
template <typename T> //将e作为当前节点的左孩子插入二叉树
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e) {  return lChild = new BinNode(e, this);  }

template <typename T> //将e作为当前节点的右孩子插入二叉树
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e) {  return rChild = new BinNode(e, this);  }




