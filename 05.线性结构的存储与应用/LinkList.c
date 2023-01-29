#include<stdio.h>
#include<stdlib.h>
typedef struct link
{
    int data;
    struct link *next;
}link;
int  Input_choice(void);
int  Input_common(void);
void Info(void);
link* AppendNode(link *head);
void DisplayNode(link *head);
link* DeleteNode(link *head, int data);
link* Sort_in_as(link *head);
link* Delete_repeated(link *head);
link* Invert(link *head);
link* Left_shift(link *head);
link* Right_shift(link *head);
void  Merge_lists(link *head1, link *head2);
void  FreeNode(link *head);
int main(void)
{
    link *head = NULL;
    link *head1 = NULL, *head2 = NULL;
    int choice, data;
    for(;;)
    {
        Info();
        choice = Input_choice();
        switch (choice)
        {
        case 1:
            head = AppendNode(head);
            break;
        case 2:
            DisplayNode(head);
            break;
        case 3:
            printf("输入待删除数据：");
            data = Input_common();
            head = DeleteNode(head, data);
            break;
        case 4:
            head = Sort_in_as(head);
            printf("排序后的数据如下：\n");
            DisplayNode(head);
            break;
        case 5:
            head = Delete_repeated(head);
            printf("操作后的数据如下：\n");
            DisplayNode(head);
            break;
        case 6:
            head = Invert(head);
            printf("逆置后的链表如下：\n");
            DisplayNode(head);
            break;
        case 7:
            head = Left_shift(head);
            printf("移位后的链表如下：\n");
            DisplayNode(head);
            break;
        case 8:
            head = Right_shift(head);
            printf("移位后的链表如下：\n");
            DisplayNode(head);
            break;
        case 9:
            Merge_lists(head1, head2);
            break;
        default:
            FreeNode(head);
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
    int ret, choice;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice >9 || choice<0)
        {
            while(getchar() != '\n');
            printf("输入无效!\n");
            printf("重新输入: ");
        }
    } while (ret != 1 || choice >9 || choice<0);
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

// 菜单列表
void Info(void)
{
    printf("\t\t*----------------【Link List Operation System】----------------*\n");
    printf("\t\t|1.添加节点                                                    |\n");
    printf("\t\t|2.展示节点                                                    |\n");
    printf("\t\t|3.删除节点                                                    |\n");
    printf("\t\t|4.按升序进行排列                                              |\n");
    printf("\t\t|5.删除重复元素(已排好序)                                      |\n");
    printf("\t\t|6.逆置链表                                                    |\n");
    printf("\t\t|7.左移k位                                                     |\n");
    printf("\t\t|8.右移k位                                                     |\n");
    printf("\t\t|9.合并两个链表(已排好序)                                      |\n");
    printf("\t\t|0.退出程序                                                    |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 添加节点
link* AppendNode(link *head)
{
    link *pr = head, *p = NULL;
    p = (link*)malloc(sizeof(link));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存! \n");
        exit(0);
    }
    if(head == NULL)
    {
        head = p;
    }
    else
    {
        while(pr->next != NULL)
        {
            pr = pr->next;
        }
        pr->next = p;
    }
    printf("输入数据：");
    p->data = Input_common();
    p->next = NULL;
    return head;
}

// 显示节点
void DisplayNode(link *head)
{
    link *p = head;
    int i = 1;
    while(p != NULL)
    {
        printf("%-3d%-3d\n", i, p->data);
        p = p->next;
        i++;
    }
}

// 删除节点
link* DeleteNode(link *head, int data)
{
    link *p=head, *pr=head;
    if(head == NULL)
    {
        printf("链表为空! \n");
        return head;
    }
    while(data != p->data && p->next != NULL)
    {
        pr = p;
        p = p->next;
    }
    if(data == p->data)
    {
        if(p == head)
        {
            head = p->next;
        }
        else
        {
            pr->next = p->next;
        }
        free(p);
        printf("删除成功！\n");
    }
    else
    {
        printf("未查询到该数据!\n");
    }
    return head;
}

// 按升序进行排序（改变每个节点的数据域）
link* Sort_in_as(link * head)
{
    link *pr = head, *p = head->next;
    int temp;
    if(head == NULL)
    {
        printf("链表为空!\n");
        return head;
    }
    if(p == NULL)
    {
        return head;
    }
    while(pr->next != NULL)
    {
        while(p != NULL)
        {
            if (pr->data > p->data)
            {
                temp = p->data;
                p->data = pr->data;
                pr->data = temp;
            }
            p = p->next;
        }
        pr = pr->next;
        p = pr->next;
    }
    return head;
}

// 删除重复元素
link* Delete_repeated(link *head)
{
    link *pr = head, *p = head->next;
    if(pr == NULL)
    {
        printf("链表为空！\n");
        exit(0);
    }
    while(pr->next != NULL)
    {
        int flag = 1;
        while(flag && p != NULL)
        {
            if(pr->data == p->data)
            {
                pr->next = p->next;
                free(p);
                flag = 1;
            }
            else
            {
                flag = 0;
            }
            p = pr->next;
        }
        pr = pr->next;
        p = pr->next;
    }
    return head;
}

// 逆置链表（改变每个节点的指针域）
link* Invert(link *head)
{
    link *pr = head, *p = head->next, *temp = NULL;
    if(head == NULL)
    {
        printf("链表为空! \n");
        return head;
    }
    if(p == NULL)
    {
        return head;
    }
    pr->next = NULL;    // 把原链表的头节点变成新链表的末节点
    while(p != NULL)
    {
        temp = p->next;
        p->next = pr;
        pr = p;
        p = temp;
    }
    head = pr;         // 让头指针指向原链表的末节点
    return head;
}

// 链表循环左移k位
link* Left_shift(link *head)
{
    link *p = head;
    int k, i, j=1, temp;
    printf("输入左移的位数k: ");
    k = Input_common();
    if(k<0)
    {
        printf("k<0, 无效数字！\n");
        return head;
    }
    while(p->next != NULL)
    {
        p = p->next;
        j++;           // 记录节点个数，以便后续移位进行模运算
    }
    p->next = head;    // 使链表首尾相连（变成环形链表，便于移动）
    p = head;          // 让指针p重新指向头节点
    for(i=1; i<(k%j); i++)
    {
        p = p->next;
    }
    head = p->next;   // 让头指针指向移动后的头节点
    p->next = NULL;   // 同时把环形链表断开
    return head;
}

// 链表循环右移k位
link* Right_shift(link *head)
{
    link *p = head;
    int k, i, j=1, temp;
    printf("输入右移的位数k: ");
    k = Input_common();
    if(k<0)
    {
        printf("k<0, 无效数字！\n");
        return head;
    }
    while(p->next != NULL)
    {
        p = p->next;
        j++;           // 记录节点个数，以便后续移位进行模运算
    }
    p->next = head;    // 使链表首尾相连（变成环形链表，便于移动）
    p = head;          // 让指针p重新指向头节点
    for(i=1; i<j-(k%j); i++)
    {
        p = p->next;
    }
    head = p->next;    // 让头指针指向移动后的头节点
    p->next = NULL;    // 同时把环形链表断开
    return head;
}

// 合并链表
void  Merge_lists(link *head1, link *head2)
{
    int i, n1, n2;
    printf("请输入链表1的长度: ");
    do
    {
        n1 = Input_common();
        if(n1 < 1)
        {
            printf("输入无效！\n");
            printf("重新输入：");
        }
    } while (n1 < 1);
    for(i=1; i<=n1; i++)
    {
        head1 = AppendNode(head1);
    }
    printf("请输入链表2的长度: ");
    do
    {
        n2 = Input_common();
        if(n2 < 1)
        {
            printf("输入无效！\n");
            printf("重新输入：");
        }
    } while (n2 < 1);
    link *p = head1;
    for(i=1; i<=n2; i++)
    {
        head2 = AppendNode(head2);
    }
    while(p->next != NULL)
    {
        p = p->next;
    }
    p->next = head2;                // 让链表1的末节点指向链表2的头节点
    head1 = Sort_in_as(head1);      // 对合并完后的链表进行排序
    printf("合并后的链表：\n");
    DisplayNode(head1);
    FreeNode(head1);
}

// 释放内存
void  FreeNode(link *head)
{
    link *p = head, *pr = NULL;
    while(p != NULL)
    {
        pr = p;
        p = p->next;
        free(pr);
    }
}