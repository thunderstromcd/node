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