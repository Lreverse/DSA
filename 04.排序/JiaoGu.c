#include<stdio.h>
#include<stdlib.h>
#define N 1000
int fun(int n);
int searchMax(int a[], int x);
int main(void)
{
    int i, n, x, count[N], flag, ret;
    printf("请输入想要测试的最大值(x>=1): ");
    do
    {
        ret = scanf("%d", &x);
        if(ret==0 || x<=0)
        {
            while(getchar()!='\n');
            printf("检测到非法字符，请重新输入: ");
        }
    } while (ret == 0 || x <= 0);
    printf("\n");
    for (i = 1; i <= x; i++)
    {
        printf("%d:\n", i);
        n = i;
        count[i-1] = 0;
        do
        {
            n = fun(n);
            printf("%d ", n);
            count[i-1]++;
        } while (n != 1);
        printf("\ncount:%d\n\n", count[i-1]);
    }
    flag = searchMax(count, x);
    printf("最长序列是当n=%d时取得的, 其序列长为%d\n", flag+1, count[flag]);
    return 0;
}
int fun(int n)
{
    if(n % 2 ==0)
    {
        return n/2;
    }
    else
    {
        return 3*n+1;
    }
}
int searchMax(int a[], int x)
{
    int i, flag = 0, max=a[0];
    for(i=1; i<x; i++)
    {
        if(max<a[i])
        {
            max = a[i];
            flag = i;
        }
    }
    return flag;
}

// 最长序列是等n=97时，共有118个数字