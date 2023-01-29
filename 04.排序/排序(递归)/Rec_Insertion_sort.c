#include<stdio.h>
void Sort_in_as(int a[], int n, int j);
int main(void)
{
    int a[] = {44, 22, 88, 53, 69, 74, 39, 80, 36, 13};
    int i, length, j=1;
    length = sizeof(a) / sizeof(int);
    printf("The previous datas:\n");
    for (i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
    Sort_in_as(a, length, j);
    printf("\nAfter Insertion sort:\n");
    for (i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
}
void Sort_in_as(int a[], int n, int j)
{
    if (j >= n)
    {
        return;
    }
    else
    {
        int i = j - 1, key = a[j];
        while ((i >= 0) && (a[i] > key))
        {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
        Sort_in_as(a, n, j+1);
    }
}
// 时间复杂度为O(n^2)
// 空间复杂度为O(n)