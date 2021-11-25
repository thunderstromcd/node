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

typedef struct
{
    QElemType data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

Status InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

int QueueLength(SqQueue Q)
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

Status EnQueue(SqQueue *Q, QElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return OVERFLOW;
    Q.data[Q->rear] = e;
    // Q->rear = (Q->rear +1) % MAXSIZE;
    Q->rear = Q->rear == MAXSIZE - 1 ? 0 : Q->rear + 1;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e)
{
    if (Q->rear == Q->front)
        return ERROR;
    *e = Q.data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

