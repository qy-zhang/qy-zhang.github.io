/**
* @File : BSTreeToDoubleList.cpp
* @Author : zhangqianyi
* @Date : 2016/11/22
* @Description :
把二元查找树转变成排序的双向链表
题目：
输入一颗二元查找树，将该二元查找树转换成一个排序的双向链表。
要求不能创建任何新的节点，只调整指针的指向。
*/

#include <iostream>

using namespace std;

struct BSTreeNode
{
    int m_nValue; // value of node
    struct BSTreeNode* m_pLeft; // left child of node
    struct BSTreeNode* m_pRight; // right child of node
};

typedef struct BSTreeNode DoubleList;
DoubleList* pHead;
DoubleList* pListIndex;

// 创建二元查找树
void addBSTreeNode(struct BSTreeNode * &pCurrent, int value)
{
    if (pCurrent == NULL) // 初始化根结点
    {
        BSTreeNode* pBSTree = new BSTreeNode();
        pBSTree->m_pLeft = pBSTree->m_pRight = NULL;
        pBSTree->m_nValue = value;
        pCurrent = pBSTree;
    }
    else // 递归调用addBSTreeNode函数添加节点
    {
        if (pCurrent->m_nValue > value)
            addBSTreeNode(pCurrent->m_pLeft, value);
        else if (pCurrent->m_nValue < value)
            addBSTreeNode(pCurrent->m_pRight, value);
        else
            cout << "Duplicated data was ignored!" << endl;
    }
}

// 二叉树转换成list
void convertToDoubleList(struct BSTreeNode * pCurrent)
{
    if (pListIndex == NULL) // 第一次被调用，表示在最左边的节点，即双向表的表头
        pHead = pCurrent;
    else  // 不是第一次调用，那就把上次的双向表指针的右指针指向当前的节点
        pListIndex->m_pRight = pCurrent;

    // 由于是双向链表，还要把当前节点pCurrent的左指针指向上次的双向表指针
    pCurrent->m_pLeft = pListIndex;

    // 把双向表指针指向pCurrent，向前移动一个节点
    pListIndex = pCurrent;
    
    cout << pCurrent->m_nValue << endl;
}

// 遍历二元查找树 中序：（左 转换 右）
void ergodicBSTree(struct BSTreeNode * pCurrent)
{
    if (pCurrent == NULL) return;
    if (pCurrent->m_pLeft != NULL) ergodicBSTree(pCurrent->m_pLeft);

    // 节点接到链表尾部
    convertToDoubleList(pCurrent);

    if (pCurrent->m_pRight != NULL) ergodicBSTree(pCurrent->m_pRight);
}

int main(int argc, char const *argv[])
{
    struct BSTreeNode* pRoot = NULL;
    pListIndex = NULL;
    pHead = NULL;
    addBSTreeNode(pRoot, 10); // 第一个数字，根结点
    addBSTreeNode(pRoot, 6);
    addBSTreeNode(pRoot, 4);
    addBSTreeNode(pRoot, 8);
    addBSTreeNode(pRoot, 12);
    addBSTreeNode(pRoot, 14);
    addBSTreeNode(pRoot, 15);
    addBSTreeNode(pRoot, 16);
    addBSTreeNode(pRoot, 10); // 重复的节点，忽略掉

    ergodicBSTree(pRoot);

    delete pRoot;
    return 0;
}