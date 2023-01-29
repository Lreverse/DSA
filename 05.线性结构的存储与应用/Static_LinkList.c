#include<stdio.h>
#include<stdlib.h>
#define N 50
typedef struct List
{
    int data;
    int next;
}List;
void Info(void);
int  Input_choice(void);
int  Input_common(void);
void Initial(List *space);
int  GetNode(List *space);
void Insert(List *space, int head);
int  Display(List *space, int head);
void Free(List *space, int x);
void Delete(List *space, int head, int position);
void Invert(List *space, int head);
int main(void)
{
    int head = -1, n, i, choice, position;    // n代表链表的长度
    List space[N];
    Initial(space);
    head = GetNode(space);                    // 先得到头节点（不存储数据，只是充当一个头指针）
    for (;;)
    {
        Info();
        choice = Input_choice();
        switch (choice)
        {
        case 1:
            Insert(space, head);
            printf("链表如右：");
            n = Display(space, head);
            break;
        case 2:
            n = Display(space, head);
            break;
        case 3:
            if (space[head].next == -1)
            {
                printf("该链表为空！\n");
                printf("无法删除！\n");
                break;
            }
            printf("输入要删除的数据位置: ");
            do
            {
                position = Input_common();
                if (position < 1 || position > n)
                {
                    printf("不存在该位置！\n");
                    printf("请重新输入：");
                }
            } while (position < 1 || position > n);
            Delete(space, head, position);
            printf("删除完毕！\n");
            n = n - 1;                           // 删除完毕后，长度减少一位
            break;
        case 4:
            Invert(space, head);
            break;
        default:
            for (i = 1; i <= n; i++)
            {
                if (space[head].next == -1)
                {
                    break;
                }
                Delete(space, head, i); // 删除该静态链表的所有节点
            }
            Free(space, head); // 删除头节点
            exit(0);
        }
        printf("\n");
        system("pause");
    }
    return 0;
}

// 菜单显示
void Info(void)
{
    printf("\t\t*-----【Static link List Operation System】------*\n");
    printf("\t\t|1.添加节点                                       |\n");
    printf("\t\t|2.展示节点                                       |\n");
    printf("\t\t|3.删除节点                                       |\n");
    printf("\t\t|4.逆置链表                                       |\n");
    printf("\t\t|0.退出程序                                       |\n");
    printf("\t\t*------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 输入检查（选择）
int  Input_choice(void)
{
    int ret, choice;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice >4 || choice<0)
        {
            while(getchar() != '\n');
            printf("输入无效!\n");
            printf("重新输入: ");
        }
    } while (ret != 1 || choice >4 || choice<0);
    return choice;
}

// 输入一般性检查
int  Input_common(void)
{
    int ret, x;
    do
    {
        ret = scanf("%d", &x);
        if(ret != 1)
        {
            while(getchar() != '\n');
            printf("输入无效!\n");
            printf("重新输入: ");
        }
    } while (ret!=1);
    return x;
}

// 初始化数组为可用空间表
void Initial(List *space)
{
    int i;
    for(i=0; i<N-1; i++)
    {
        space[i].next = i+1;
    }
    space[i].next = -1;
}

// 向可用空间表申请节点
int  GetNode(List *space)
{
    int p;
    if(space[0].next == -1)
    {
        printf("没有足够空间分配内存！\n");
        p = -1;
    }
    else
    {
        p = space[0].next;
        space[0].next = space[p].next;
    }
    return p;
}

// 插入节点
void Insert(List *space, int head)
{
    int p = head, x;
    x = GetNode(space);                    // 先向可用空间表申请一个节点
    if(x == -1)
    {
        return;                           // 说明可用线性表已空
    }
    while(space[p].next != -1)            // 将p移动到链表的末尾
    {
        p = space[p].next;
    }
    printf("输入数据：");
    space[x].data = Input_common();
    space[p].next = x;
    space[x].next = -1;
}

// 展示节点
int  Display(List *space, int head)
{
    int p = space[head].next, n=0;
    if(p == -1)
    {
        printf("该线性表为空\n");
        return 0;
    }
    while(p != -1)
    {
        printf("%-4d",space[p].data);
        p = space[p].next;
        n ++;
    }
    return n;
}

// 释放节点（即把节点重新插回可用空间表）
void Free(List *space, int x)
{
    space[x].next = space[0].next;
    space[0].next = x;   
}

// 删除节点（position代表链表的顺序结构的位置，不是存储数组的位置）
void Delete(List *space, int head, int position)
{
    int i, p = head, pr = head;
    for(i = 1; i<=position; i++)
    {
        pr = p;
        p = space[p].next;
    }
    space[pr].next = space[p].next;
    Free(space, p);
}

// 逆置链表
void Invert(List *space, int head)
{
    int pr = space[head].next, p = space[pr].next , temp;
    if(pr == -1)
    {
        printf("该链表为空！\n");
        return ;
    }
    space[pr].next = -1;
    while(p != -1)
    {
        temp = space[p].next;    // 存储p下一个节点位置
        space[p].next = pr;
        pr = p;
        p =temp;
    }
    space[head].next = pr;
    printf("逆置成功！\n");
}