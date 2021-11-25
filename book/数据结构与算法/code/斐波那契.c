//  1 1 2 3 5 8 13
// 前面两项之和构成后一项的值
int idx;
idx = 20;

int Fbl(int i)
{
    if (i <= 1)
        return i == 1 ? 1 : 0;
    return Fbl(i - 1) + Fbl(i - 2)
}
int arr,sum;
arr = [];
sum=0;
for (int i = 1; i < idx; i++)
{
    arr.push(Fbl(i));
    sum += arr[i]
}
