#include <stdio.h>
void Sort_in_as(int a[], int n);
int main(void)
{
    int a[] = {44, 22, 88, 53, 69, 74, 39, 80, 36, 13};
    int length, i;
    length = sizeof(a) / sizeof(int);
    printf("The previous datas:\n");
    for (i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
    Sort_in_as(a, length);
    printf("\nAfter Selection sort:\n");
    for (i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
void Sort_in_as(int a[], int n)
{
    if (n == 0)
    {
        return;
    }
    else
    {
        int i, temp, max = n-1;
        for (i = n - 2; i >= 0; i--)
        {
            if (a[max] < a[i])
            {
                max = i;
            }
        }
        temp = a[max];
        a[max] = a[n-1];
        a[n-1] = temp;
        Sort_in_as(a, n - 1);
    }
}
// 时间复杂度为O(n^2)
// 空间复杂度为O(n)