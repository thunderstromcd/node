#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define NULL 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int SElemType;
typedef int Status;

typedef struct SqStack
{
    SElemType data[MAXSIZE];
    int top;
} SqStack;

Status InitStack(SqStack *S)
{
}

Status Push(SqStack *S, SElemType e)
{
    if (S->top == MAXSIZE - 1)
        return ERROR;
    S->top++;
    S->data[S->top] = e;
    return OK;
}

Status Pop(SqStack *S, SElemType *e)
{
    if (S->top == -1)
        return ERROR;
    *e = S->data[S->top];
    S->top--;
    return OK;
}

// 两栈共用空间
typedef struct SqDoubleStack
{
    SElemType data[MAXSIZE];
    int top1;
    int top2;
} SqDoubleStack;

// StackNumber代表栈号
Status Push(SqDoubleStack *S, int StackNumber, SElemType e)
{
    if (S->top1 + 1 == S->top2)
        return ERROR;
    if (StackNumber == 1)
        S->data[++S->top1] = e;
    else if (StackNumber == 2)
        S->data[--S->top2] = e;
    return OK;
}

Status Pop(SqDoubleStack *S, int StackNumber, SElemType *e)
{
    if (StackNumber == 1)
    {
        if (S->top1 == -1)
            return ERROR;
        *e = S->data[S->top1]; 
        S->top1--;
    }
    else if (StackNumber == 2)
    {
        if (S->top2 == MAXSIZE - 1)
            return ERROR;
        // *e = S->data[S->top2++]
        *e = S->data[S->top2];
        S->top2++;
    }
    return OK;
}