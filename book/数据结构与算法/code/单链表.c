#include "string.h"
#include "ctype.h"      

#include "stdio.h"    
#include "stdlib.h"   

#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define NULL 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int ElemType;

// 结点类型
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct Node *LinkList; /* 定义LinkList */

Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));
    if (!(*L)) /* 存储分配失败 */
        return ERROR;
    (*L)->next = NULL; /* 指针域为空 */

    return OK;
}

Status ListEmpty(LinkList L)
{
    if (L->next)
        return FALSE;
    else
        return TRUE;
}

Status ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next; /*  p指向第一个结点 */
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;
    return OK;
}

int ListLength(LinkList L)
{
    int i;
    LinkList p = L->next;
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}

// i是逻辑位序
Status GetElem(LinkList L, int i, ElemType *e)
{
    int j = 1;
    LinkList p;
    p = L->next;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (j > i || !p)
        return ERROR;
    *e = p->data;
    return OK;
}

int LocateElem(LinkList L, ElemType e)
{
    int i = 1;
    LinkList p = L->next;
    while (p)
    {
        if (p->data == e)
            break;
        i++;
        p = p->next;
    }
    return i;
}

// 插入要注意给插入的结点开辟内存 并将 s->data = e;
Status ListInsert(LinkList *L, int i, ElemType e)
{
    // LinkList p = (*L)->next;
    // int j = 1;
    // while (p && j < i)
    // {
    //     p = p->next;
    //     j++;
    // }
    // if (!p || j > i)
    //     return ERROR;

    // s = p->next;
    // p->next = e;
    // e->next = s;
    // return OK;

    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    while (p && j < i) /* 寻找第i个结点 */
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;                   /* 第i个元素不存在 */
    s = (LinkList)malloc(sizeof(Node)); /*  生成新结点(C语言标准函数) */
    s->data = e;
    s->next = p->next; /* 将p的后继结点赋值给s的后继  */
    p->next = s;       /* 将s赋值给p的后继 */
    return OK;
}

Status ListDelete(LinkList *L, int i, ElemType *e)
{
    LinkList p, q;
    int j;
    j = 1;
    p = *L;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
        return ERROR;
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

void ListTraverse()
{
}

void CreateListHead()
{
}

void CreateListTail()
{
}