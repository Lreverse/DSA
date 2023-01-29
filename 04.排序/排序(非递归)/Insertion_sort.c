#include<stdio.h>
void Sort_in_as(int a[], int n);
int main(void)
{
    int a[] = {86, 65, 34, 54, 12, 109, 47, 95, 29, 77};
    int length, i;
    length = sizeof(a) / sizeof(int);
    printf("The previous datas:\n");
    for (i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
    Sort_in_as(a, length);
    printf("\nAfter Insertion sort:\n");
    for (i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
}
void Sort_in_as(int a[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        while ((j >= 0) && (a[j] > key))
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
// 时间复杂度为O(n^2)
// 空间复杂度为O(1)