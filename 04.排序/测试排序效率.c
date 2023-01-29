#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Sort_in_as(int a[], int n);
int main(void)
{
    clock_t start,end;
    int a[100000];
    int length, i;
    srand(1);
    length = sizeof(a) / sizeof(int);
    printf("\n生成100000个随机数.....\n");
    for (i = 0; i < length; i++)
    {
        a[i]=rand();
    }
    printf("随机数生成完毕\n\n");
    printf("进行插入排序.....\n");
    start = clock();
    Sort_in_as(a, length);
    end = clock();
    printf("排序完成\n");
    printf("排序所需的时间为: %f\n\n\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}

//插入排序
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


// // 冒泡排序
// void Sort_in_as(int a[], int n)
// {
//     int i, j, temp;
//     for (i = 1; i < n; i++)
//     {
//         for (j = 0; j < n-i; j++)
//         {
//             if (a[j] > a[j + 1])
//             {
//                 temp = a[j];
//                 a[j] = a[j + 1];
//                 a[j + 1] = temp;
//             }
//         }
//     }
// }


// //选择排序
// void Sort_in_as(int a[], int n)
// {
//     int i, j, min, temp;
//     for (i = 0; i < n - 1; i++)
//     {
//         min = i;
//         for (j = i + 1; j < n; j++)
//         {
//             if (a[min] > a[j])
//             {
//                 min = j;
//             }
//         }
//         temp = a[i];
//         a[i] = a[min];
//         a[min] = temp;
//     }
// }

