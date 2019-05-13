#include "stdio.h"
#include "stdlib.h"
#include "linearlist.h"

/*返回一个线性表的第 倒数K 个节点*/
// 思路：定义两个变量，都从头开始，让一个先移K位
// 然后两个一起移，直到第一个移到尾
LNode * lastKNode (LNode* L, int k) {
    LNode* p;
    LNode* q;
    p = L;
    q = L;

    while (k--) {
        if (p != NULL)
            p = p->next;
        else
            break;
    }

    if (p == NULL) return NULL;
    else {
        while(p) {
            p = p->next;
            q = q->next;
        }
        return q;
    }
}

int main(int argc, char *argv[])
{
    LNode* L = (LNode*)malloc(sizeof(LNode));
    createList(L, 5);

    LNode* p;
    p = lastKNode(L, 3);
    printf ("The value of the last %d node is %d\n", 3, p->data);
    return 0;
}
