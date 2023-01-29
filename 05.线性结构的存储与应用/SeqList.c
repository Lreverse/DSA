#include<stdio.h>
#include<stdlib.h>
#define N 50
typedef struct List
{
    int a[N];
    int last;
}List;
int  Input_choice(void);
int  Input_common(void);
void Info(void);
void Print(List *L);
void Insert(List *L);
void Delete(List *L);
void Sort_in_as(List *L);
void Delete_repeated(List *L);
void Invert(List *L);
void Left_shift(List *L);
void Right_shift(List *L);
void Merge_lists(List *L1, List *L2);
int main(void)
{
    int choice;
    List L = {{30, 10, 50, 40, 60, 20, 30}, 6};
    List L1 = {{11, 22, 33, 44, 55, 66, 77, 88, 99}, 8};
    List L2 = {{8, 13, 26, 38, 41, 53, 66, 70, 84, 90}, 8};
    for(;;)
    {
        Info();
        choice = Input_choice();
        switch (choice)
        {
        case 1:
            printf("已有列表: \n");
            Print(&L);
            Insert(&L);
            printf("插入之后: \n");
            Print(&L);
            break;
        case 2:
            printf("已有列表: \n");
            Print(&L);
            Delete(&L);
            break;
        case 3:
            Print(&L);
            break;
        case 4:
            printf("已有列表: \n");
            Print(&L);
            Sort_in_as(&L);
            printf("升序之后: \n");
            Print(&L);
            break;
        case 5:
            printf("已有列表: \n");
            Print(&L);
            Delete_repeated(&L);
            printf("删除之后: \n");
            Print(&L);
            break;
        case 6:
            printf("已有列表: \n");
            Print(&L);
            Invert(&L);
            printf("逆置之后: \n");
            Print(&L);
            break;
        case 7:
            printf("已有列表: \n");
            Print(&L);
            Left_shift(&L);
            printf("左移之后: \n");
            Print(&L);
            break;
        case 8:
            printf("已有列表: \n");
            Print(&L);
            Right_shift(&L);
            printf("右移之后: \n");
            Print(&L);
            break;
        case 9:
            printf("List-1:\n");
            Print(&L1);
            printf("List-2:\n");
            Print(&L2);
            Merge_lists(&L1, &L2);
            printf("合并之后:\n");
            Print(&L1);
            break;
        default:
            exit(0);
        }
        printf("\n");
        system("pause");
    }
    return 0;
}

// 输入检查（有条件）
int  Input_choice(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(choice<0 || choice> 9 || ret != 1)
        {
            while (getchar() != '\n');
            printf("输入无效!\n");
            printf("重新输入: ");
        }
    } while (choice<0 || choice> 9 || ret != 1);
    return choice;
}

// 输入一般性检查
int  Input_common(void)
{
    int ret, x;
    do
    {
        ret = scanf("%d", &x);
        if (ret != 1)
        {
            while (getchar() != '\n');
            printf("输入无效!\n");
            printf("重新输入: ");
        }
    } while (ret != 1);
    return x;
}

// 显示菜单
void Info(void)
{
    printf("\t\t*--------------【Sequence List Operation System】-------------*\n");
    printf("\t\t|1.添加元素                                                   |\n");
    printf("\t\t|2.删除元素                                                   |\n");
    printf("\t\t|3.展示列表                                                   |\n");
    printf("\t\t|4.按升序进行排列                                             |\n");
    printf("\t\t|5.删除重复元素(已排好序)                                     |\n");
    printf("\t\t|6.逆置列表                                                   |\n");
    printf("\t\t|7.左移k位                                                    |\n");
    printf("\t\t|8.右移k位                                                    |\n");
    printf("\t\t|9.合并两个列表(已排好序)                                     |\n");
    printf("\t\t|0.退出程序                                                   |\n");
    printf("\t\t*-------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 打印列表数据
void Print(List *L)
{
    int i;
    for(i = 0; i <= L->last; i++)
    {
        printf("%-4d", L->a[i]);
    }
    printf("\n");
}

// 插入数据
void Insert(List *L)
{
    int x, p, ret1, ret2;
    printf("插入的数据：");
    x = Input_common();
    printf("插入的位置：");
    p = Input_common();
    if(L->last+1 >= N)
    {
        printf("列表已满！\n");
    }
    else if(p<=0 || p > L->last+2)
    {
        printf("不存在该位置\n");
    }
    else
    {
        int i;
        for (i = L->last; i >= p-1; i--)
        {
            L->a[i + 1] = L->a[i];
        }
        L->a[p-1] = x;
        L->last++;
    }
}

// 删除数据
void Delete(List *L)
{
    int x, i, j, flag = 0;
    printf("输入待删除数据：");
    x = Input_common();
    for(i=0; i<=L->last; i++)
    {
        if(L->a[i] == x)
        {
            for(j=i; j<L->last; j++)
            {
                L->a[j] = L->a[j+1];
            }
            L->last--;
            flag = 1;
        }
    }
    if(!flag)
    {
        printf("未查询到该数据!\n");
    }
    else
    {
        printf("删除之后: \n");
        Print(L);
    }
}

// 按升序进行排列(插入排序)
void Sort_in_as(List *L)
{
    int i, j, key;
    for(i=1; i<= L->last; i++)
    {
        key = L->a[i];
        j = i-1;
        while((j>=0) && (L->a[j]>key))
        {
            L->a[j+1] = L->a[j];
            j--;
        }
        L->a[j+1] = key;
    }
}

// 删除重复元素
void Delete_repeated(List *L)
{
    int key, i, j, h, flag;
    for(i=0; i<L->last; i++)
    {
        key = L->a[i];
        j = i+1;
        flag = 1;
        while(flag)
        {
            if(L->a[j]==key)     //找到相同的数，则进行删除操作
            {
                for(h=j; h<L->last; h++)
                {
                    L->a[h] = L->a[h+1];
                }
                L->last--;
            }
            else
            {
                flag = 0;
            }
        }
    }
}

// 逆置线性表
void Invert(List *L)
{
    int i, j, temp;
    for(i=0, j=L->last; i<j; i++,j--)
    {
        temp = L->a[i];
        L->a[i] = L->a[j];
        L->a[j] = temp;
    }
}

// 线性表循环左移k位
void Left_shift(List *L)
{
    int k, i, j, temp;
    printf("输入左移的位数k: ");
    k = Input_common() % (L->last+1);
    if(k<0)
    {
        printf("k<0, 无效数字！\n");
        return;
    }
    for(i=0, j=k-1; i<j; i++, j--)
    {
        temp = L->a[i];
        L->a[i] = L->a[j];
        L->a[j] = temp;
    }
    for(i=k, j=L->last; i<j; i++, j--)
    {
        temp = L->a[i];
        L->a[i] = L->a[j];
        L->a[j] = temp;
    }
    for(i=0, j=L->last; i<j; i++, j--)
    {
        temp = L->a[i];
        L->a[i] = L->a[j];
        L->a[j] = temp;
    }
}

// 线性表循环右移k位
void Right_shift(List *L)
{
    int k, i, j, temp;
    printf("输入右移的位数k: ");
    k = Input_common() % (L->last+1);
    if(k<0)
    {
        printf("k<0, 无效数字！\n");
        return;
    }
    for(i=0, j=L->last-k; i<j; i++, j--)
    {
        temp = L->a[i];
        L->a[i] = L->a[j];
        L->a[j] = temp;
    }
    for(i=L->last-k+1, j=L->last; i<j; i++, j--)
    {
        temp = L->a[i];
        L->a[i] = L->a[j];
        L->a[j] = temp;
    }
    for(i=0, j=L->last; i<j; i++, j--)
    {
        temp = L->a[i];
        L->a[i] = L->a[j];
        L->a[j] = temp;
    }
}

// 合并已排好序的线性表
void Merge_lists(List *L1, List *L2)
{
    int i, j, n1 = L1->last, n2 = L2->last;
    for(i=n1+1, j=0; i<=n1+n2+1; i++,j++)
    {
        L1->a[i] = L2->a[j];
    }
    L1->last = L1->last + L2->last + 1;
    Sort_in_as(L1);
}