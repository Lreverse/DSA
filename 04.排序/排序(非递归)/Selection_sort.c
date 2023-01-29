#include <stdio.h>
void Sort_in_as(int a[], int n);
int main(void)
{
    int a[] = {98, 32, 54, 134, 110, 45, 33, 85, 66, 55};
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
}
void Sort_in_as(int a[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[min] > a[j])
            {
                min = j;
            }
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}
// 时间复杂度为O(n^2)
// 空间复杂度为O(1)