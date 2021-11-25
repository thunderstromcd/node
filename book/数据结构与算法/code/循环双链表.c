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
typedef struct DulNode
{
    ElemType data;
    struct DulNode *next;
    struct DulNode *prior;
} DulNode;

typedef struct DulNode *DulLinkList; /* 定义DulLinkList */

Status InitList(DulLinkList *L)
{
    *L = (DulLinkList)malloc(sizeof(DulNode));
    if (!(*L))
        return ERROR;
    (*L)->prior = *L;
    (*L)->next = *L;
}

Status ListEmpty(DulLinkList L)
{
    if (L->next == L && L->prior == L)
        return TRUE;
    else
        return FALSE;
}

Status ClearList(DulLinkList *L)
{
    DulLinkList p = p->next;
    while (p != *L)
    {
        p = p->next;
        free(p->prior);
    }
    (*L)->prior = *L;
    (*L)->next = *L;
}

Status ListLength(DulLinkList L)
{
    DulLinkList p = L->next;
    int i;
    i = 1;
    while (p != L)
    {
        p = p->next;
        i++;
    }
    return i;
}

Status GetElem(DulLinkList L, int i, DulNode *e)
{
    DulLinkList p = L->next;
    DulLinkList q = L->prior;
    int j;
    if (i < Math.round(ListLength(L) / 2))
    {
        j = ListLength(L);
        while (j > i)
        {
            if (q->data == e)
                *e = q->data;
            q = q->prior;
            j--;
        }
    }
    else
    {
        j = 1;
        while (j < i)
        {
            if (q->data == e)
                *e = q->data;
            q = q->next;
            j++;
        }
    }
}

Status LocateElem() {}

Status ListInsert(DulLinkList *L, int i, DulNode e)
{
    DulLinkList p, s;
    p = *L;
    int j;
    j = 0;
    if (i < 1 || i > ListLength(L) + 1)
        return ERROR;
    while (p == *L && j < i - 1) // 找到i-1结点
    {
        p = p->next;
        j++;
    }
    s = (DulLinkList)malloc(sizeof(DulNode));
    s->data = e;

    s->prior = p;
    s->next = p->next;
    p->next->prior = s;
    p->next = s;
    return OK;
}

Status ListDelete(DulLinkList *L, int i, DulNode *e)
{
    DulLinkList p = *L->next;
    int j;
    j = 0;
    if (i < 1 || i > ListLength(L) + 1)
        return ERROR;
    while (p == *L && j < i - 1) // 找到i结点
    {
        p = p->next;
        j++;
    }
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}
