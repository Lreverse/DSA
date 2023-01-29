#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct polynode
{
    float coef;            // 系数
    int exp;               // 指数
    struct polynode * next;
}poly;
poly* AppendNode(poly *end, float coef, int exp);
void  InsertNode(poly *pr, float coef, int exp);
void  CreatePoly(poly *head1, poly *head2);
void  PrintPoly(poly *head);
void  desPower(poly *head);
poly* PolyAdd(poly *head1, poly *head2);
poly* PolySub(poly *head1, poly *head2);
poly* PolyMul(poly *head1, poly *head2);
poly* Get_Kth_Derivatives(poly *head, int k);
float Calculate(poly *head, float x);
void  Delete_0(poly *head);
void  DeletePoly(poly *head);
int main(void)
{
    freopen("polyIn.txt", "r", stdin);             // 将输入流重定向到polyIn.txt文件中
    freopen("polyOut.txt", "w", stdout);           // 将输出流重定向到polyOut.txt文件中
    poly head1, head2;
    CreatePoly(&head1, &head2);
    poly *p1 = head1.next, *p2 = head2.next;
    poly *p3 = NULL, *p4 = NULL, *p5 = NULL, *p6 = NULL;
    float x, y;
    int k;
    desPower(p1);
    Delete_0(p1);
    desPower(p2);
    Delete_0(p2);

    printf("多项式p1:\n");
    PrintPoly(p1);
    printf("\n\n");

    printf("多项式p2:\n");
    PrintPoly(p2);
    printf("\n\n");

    printf("多项式相加(p1+p2):\n");
    p3 = PolyAdd(p1, p2);
    Delete_0(p3);
    PrintPoly(p3);
    printf("\n\n");

    printf("多项式相减(p2-p1):\n");
    p4 = PolySub(p1, p2);
    Delete_0(p4);
    PrintPoly(p4);
    printf("\n\n");

    printf("多项式相乘(p1*p2):\n");
    p5 = PolyMul(p1, p2);
    Delete_0(p5);
    PrintPoly(p5);
    printf("\n\n");

    scanf("%d", &k);
    printf("多项式p1的%d阶导函数:\n", k);
    p6 = Get_Kth_Derivatives(p1, k);
    PrintPoly(p6);
    printf("\n\n");

    scanf("%f", &x);
    printf("多项式p1在x=%.3f下的值:\n", x);
    y = Calculate(p1, x);
    printf("%f\n", y);

    DeletePoly(p1);
    DeletePoly(p2);
    DeletePoly(p3);
    DeletePoly(p4);
    DeletePoly(p5);
    DeletePoly(p6);
    return 0;
}

// 添加节点
poly* AppendNode(poly *end, float coef, int exp)
{
    poly *p = NULL;
    p = (poly*)malloc(sizeof(poly));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存! \n");
        exit(0);
    }
    end->next = p;
    p->coef = coef;
    p->exp = exp;
    p->next = NULL;
    return p;
}

// 插入节点
void  InsertNode(poly *pr, float coef, int exp)
{
    poly *p = NULL;
    p = (poly*)malloc(sizeof(poly));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    p->coef = coef;
    p->exp = exp;
    p->next = pr->next;
    pr->next = p;
}

// 创建多项式（采用文件重定向）
void  CreatePoly(poly *head1, poly *head2)
{
    int exp;
    float coef;
    poly *p1 = head1, *p2 = head2;
    do
    {
        scanf("%f%d", &coef, &exp);
        if(coef != 0)
        {
            p1 = AppendNode(p1, coef, exp);
        }
    } while (coef != 0);
    do
    {
        scanf("%f%d", &coef, &exp);
        if(coef != 0)
        {
            p2 = AppendNode(p2, coef, exp);
        }
    } while (coef != 0);
}

// 打印多项式
void  PrintPoly(poly *head)
{
    poly *p = head;
    while(p != NULL)
    {
        if(p->exp == 0)                 // 判断指数是否为0（即是否为常数项）
        {
            printf("%.0f", p->coef);
        }
        else                            // 非常数项的输出
        {
            printf("%.0fx^%d", p->coef, p->exp);
        }
        if(p->next != NULL)             // 这里需要注意，两个判别式不能用&&写在一起，否则会出现越界访问
        {
            if(p->next->coef > 0)
                printf("+");            // 如果后一项系数大于0，则自动添加“+”
        }
        p = p->next;
    }
}

// 对多项式进行降幂排列
void  desPower(poly *head)
{
    poly *pr = head, *p = pr->next, *temp = pr;
    float coef;
    int exp;
    while(pr->next != NULL)
    {
        while(p != NULL)
        {
            if(pr->exp < p->exp)
            {
                coef = p->coef;
                exp = p->exp;
                p->coef = pr->coef;
                p->exp = pr->exp;
                pr->coef = coef;
                pr->exp = exp;
            }
            else if (pr->exp == p->exp)       // 合并同类项
            {
                pr->coef += p->coef;
                temp->next = p->next;
                free(p);
                p = temp->next;
                continue;
            }
            temp = p;
            p = p->next;
        }
        pr = pr->next;
        temp = pr;
        p = pr->next;
    }
    
}

// 多项式加法
poly* PolyAdd(poly *head1, poly *head2)
{
    poly *p1 = head1, *p2 = head2, *p3 = NULL, *temp = NULL;
    p3 = (poly*)malloc(sizeof(poly));
    temp = p3;                             // 记录新产生的多项式的无数据头节点（不存储数据，起头指针作用）
    if(p3 == NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    while(p1 != NULL && p2 != NULL)
    {
        if(p1->exp > p2->exp)
        {
            p3 = AppendNode(p3, p1->coef, p1->exp);
            p1 = p1->next;
        }
        else if(p1->exp < p2->exp)
        {
            p3 = AppendNode(p3, p2->coef, p2->exp);
            p2 = p2->next;
        }
        else
        {
            p3 = AppendNode(p3, p1->coef+p2->coef, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while(p1 != NULL)
    {
        p3 = AppendNode(p3, p1->coef, p1->exp);
        p1 = p1->next;
    }
    while(p2 != NULL)
    {
        p3 = AppendNode(p3, p2->coef, p2->exp);
        p2 = p2->next;
    }
    p3 = temp->next;                      // 记录下有数据的头节点的地址
    free(temp);                           // 释放无数据头节点
    return p3;
}

// 多项式减法
poly* PolySub(poly *head1, poly *head2)
{
    poly *p = head1, *p4 = NULL;
    while(p != NULL)                 // 将多项式p1的系数全部取反
    {
        p->coef = -p->coef;
        p = p->next;
    }
    p4 = PolyAdd(head1, head2);      // 然后，进行相加
    p = head1;
    while(p != NULL)                 // 对多项式p1再次取反，回到原样
    {
        p->coef = -p->coef;
        p = p->next;
    }
    return p4;
}

// 多项式乘法
poly* PolyMul(poly *head1, poly *head2)
{
    poly *p1 = head1, *p2 = head2, *p5 = NULL, *pr = NULL, *temp = NULL;
    float coef;
    int exp, flag;
    p5 = (poly*)malloc(sizeof(poly));
    temp = p5;
    if(p5 ==NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    while(p2!=NULL)
    {
        coef = p1->coef * p2->coef;
        exp = p1->exp + p2->exp;
        p5 = AppendNode(p5, coef, exp);
        p2 = p2->next;
    }
    p1 = p1->next;
    while(p1 != NULL)
    {
        p2 = head2;
        while(p2 != NULL)
        {
            pr = temp;
            p5 = temp->next;
            flag = 0;
            coef = p1->coef * p2->coef;
            exp = p1->exp + p2->exp;
            while (!flag)                            // 插入成功则把flag置为1，否则继续遍历
            {
                if (exp > p5->exp)
                {
                    InsertNode(pr, coef, exp);
                    flag = 1;
                }
                else if (exp < p5->exp)
                {
                    pr = p5;
                    p5 = p5->next;
                    if(p5 == NULL)                   // 若已经遍历到最后一个节点，则直接插入末尾
                    {
                        InsertNode(pr, coef, exp);
                        flag = 1;
                    }
                }
                else                                 // 指数相等的情况，则系数直接相加
                {
                    p5->coef += coef;
                    flag = 1;
                }
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    p5 = temp->next;
    free(temp);
    return p5;
}

// 求解多项式的k阶导数
poly* Get_Kth_Derivatives(poly *head, int k)
{
    poly *p = head, *p6 = NULL, *temp = NULL, *pr = NULL;
    float coef;
    int i, exp;
    p6 = (poly*)malloc(sizeof(poly));
    temp = p6;
    if(p6 ==NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    if (k > p->exp)                       // 若k大于项最大次数，则直接返回只有常熟0的多项式
    {
        p6->coef = 0;
        p6->exp = 0;
        return p6;
    }
    else
    {
        while (p != NULL)                 // 求一阶导数（同时也是创建一个新的链表）
        {
            coef = p->coef * p->exp;
            exp = p->exp - 1;
            if (exp == -1)                // 当阶数变为-1时，不添加节点。直接跳出循环
            {
                break;
            }
            p6 = AppendNode(p6, coef, exp);
            p = p->next;
        }
        for (i = 1; i < k; i++)           // 求k阶导数，直接在新链表上操作
        {
            pr = temp;
            p6 = temp->next;
            while (p6 != NULL)
            {
                p6->coef = p6->coef * p6->exp;
                p6->exp = p6->exp - 1;
                if (p6->exp == -1)        // 当阶数变为-1时，删除该节点
                {
                    pr->next = NULL;
                    free(p6);
                    break;
                }
                pr = p6;
                p6 = p6->next;
            }
        }
        p6 = temp->next;
        free(temp);
        return p6;
    }
}

// 计算多项式在x点处的值
float Calculate(poly *head, float x)
{
    poly *p = head;
    float y = 0.0;
    while(p != NULL)
    {
        y += p->coef * pow(x, p->exp);
        p = p->next;
    }
    return y;
}

// 删除多项式中系数为0的项
void  Delete_0(poly *head)
{
    poly *p = head, *pr = head;
    while(p != NULL)
    {
        if(fabs(p->coef)< 1e-6)              // 浮点数判断是否等于0
        {
            if(p == head)
            {
                head = p->next;
                free(p);
                pr = head;
                p = pr->next;
                continue;
            }
            else
            {
                pr->next = p->next;
                free(p);
                p = pr->next;
                continue;
            }
        }
        pr = p;
        p  = p->next;
    }
}

// 删除多项式，释放内存
void  DeletePoly(poly *head)
{
    poly *p = head, *pr = NULL;
    while(p != NULL)
    {
        pr = p;
        p = p->next;
        free(pr);
    }
}
