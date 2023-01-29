#include<stdio.h>
void hanoi(int n, char from, char to , char temp);
int main(void)
{
    int n, i;
    printf("请输入堆叠的总盘数(n>0): ");
    do
    {
        i = scanf("%d", &n);
        if(i==0 || n<=0)
        {
            while(getchar()!='\n');
            printf("检测到非法字符，请重新输入: ");
        }
    } while (i == 0 || n <= 0);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
void hanoi(int n, char from, char to, char temp)
{
    static int i = 1;
    if(n == 1)
    {
        printf("第%d次移动: %c---->%c\n", i, from, to);
        i++;
    }
    else
    {
        hanoi(n-1, from, temp, to);
        printf("第%d次移动: %c---->%c\n", i, from, to);
        i++;
        hanoi(n-1, temp, to, from);
    }
}
//时间复杂度：O(2^n)
//空间复杂度：O(n)