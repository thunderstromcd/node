#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define OVERFLOW 2
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int QElemType; /* SElemType类型根据实际情况而定，这里假设为int */

typedef struct QNode //
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct LinkQueue
{
    QNode front, rear;
} LinkQueue;

Status InitQueue(LinkQueue *Q)
{
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    Q->front = Q->rear = s;
    if (!Q->front)
        return OVERFLOW;
    Q->front = Q->rear = null;
    return OK;
}
// ??????????????????? 销毁和清空不同 清空是free到空链表 销毁是全部free
Status DestroyQueue(LinkQueue *Q)
{
    while (Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

// !!!!!!!!!!!!!!
Status ClearQueue(LinkQueue *Q)
{
    QueuePtr p, q;
    Q->rear = Q->front;
    p = Q->rear->next;
    Q->front->next = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    return OK;
}

Status EnQueue(LinkQueue *Q, QNode e)
{
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    return OK;
}
x
Status DeQueue(LinkQueue *Q, QNode *e)
{
    if (Q->front == Q->rear)
        return ERROR;
    // LinkQueue p; FIX:注意这里声明的是结点类型 不是整个链表
    QueuePtr p;
    // 将要删除的结点给p暂存 Q->front是头结点 是要保存的
    p = Q->front->next;
    *e = p->data;
    // *e = Q->front;
    // p = Q->front;
    Q->front->next = p->next;
    /* 若队头就是队尾，则删除后将rear指向头结点 */
    if (Q->rear == p)
        Q->front == Q->rear;
    free(p);
    return OK;
}