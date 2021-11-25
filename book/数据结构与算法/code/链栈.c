#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define NULL 0

typedef int SElemType;
typedef int Status;

typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
} StackNode;

typedef struct StackNode *LinkStackPtr;

typedef struct
{
    LinkStackPtr top;
    int count;
} LinkStack;

Status Push(LinkStack *S, SElemType e)
{
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(SElemType));
    s->data = e;
    s->next = S->top;
    S->top = s;
    S->count++;
    return OK;
}

Status Pop(LinkStack *S, SElemType *e)
{
    LinkStackPtr p;
    if (!StackEmpty(*S))
        return ERROR;
    *e = S->top->data;
    p = S->top;
    S->top = S->top->next;
    free(p);
    S->count--;
    return OK;
}

Status ClearStack(LinkStack *S)
{
    LinkStackPtr p, q;
    p = p->top;
    while (p)
    {
        q = p;
        p = p->next;
        free(p);
    }
    S->top = null;
    S->count = 0;
    return OK;
}