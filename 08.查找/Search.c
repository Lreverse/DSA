#include<stdio.h>
#include<stdlib.h>
#define N 3000
typedef struct BSTnode  // 二叉查找树的节点
{
    int data;
    struct BSTnode *lchild;
    struct BSTnode *rchild;
} BSTnode;
typedef struct SeqList  // 线性表
{
    int a[N];
    int n;  // n代表节点个数
} SeqList;
typedef struct ASL  // 存储成功与失败时的ASL
{
    float succ;
    float fail;
} ASL;
SeqList list;
ASL  test[3];
void Info(void);
void Info_BST(void);
void Info_Half(void);
void Info_test(void);
int  Input_menu(void);
int  Input_sub1(void);
int  Input_sub2(void);
int  Input(void);
void choose_BST(void);
void choose_Half(void);
void choose_test(void);
BSTnode* Insert(BSTnode *BST, int key);
BSTnode* Create_BST(void);
BSTnode* Search_BST(BSTnode *BST, int key);
int  DeleteMin(BSTnode *F);
void Delete(BSTnode *BST, int key);
void InOrder(BSTnode *BST);
void Create_Seq(SeqList *L);
int  Search_Half(SeqList *L, int key);
void Sort_in_as(SeqList *L);
BSTnode* Create_test_1(void);
BSTnode* Create_test_2(void);
void ASL_BST(BSTnode *BST, ASL *test);
int  Search_BST_ASL(BSTnode *BST, int key);
void InOrder_test(BSTnode *BST);
void ASL_Half(ASL *test);
int  Search_Half_ASL(int key);
int main(void)
{
    for(;;)
    {
        int choice;
        Info();
        choice = Input_menu();
        switch (choice)
        {
        case 1:
            system("cls");
            choose_BST();
            break;
        case 2:
            system("cls");
            choose_Half();
            break;
        case 3:
            system("cls");
            choose_test();
            break;
        default:
            exit(0);
        }
    }
    return 0;
}

// 主菜单
void Info(void)
{
    printf("\t\t*--------------------------【Search】--------------------------*\n");
    printf("\t\t|1.BST查找                                                     |\n");
    printf("\t\t|2.折半查找                                                    |\n");
    printf("\t\t|3.测试                                                        |\n");
    printf("\t\t|0.退出程序                                                    |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 子菜单（BST）
void Info_BST(void)
{
    printf("\t\t*----------------------------【BST】---------------------------*\n");
    printf("\t\t|1.创建BST                                                     |\n");
    printf("\t\t|2.插入                                                        |\n");
    printf("\t\t|3.查找                                                        |\n");
    printf("\t\t|4.删除                                                        |\n");
    printf("\t\t|5.排序                                                        |\n");
    printf("\t\t|0.返回主菜单                                                  |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 子菜单（折半查找）
void Info_Half(void)
{
    printf("\t\t*--------------------【Half-Interval Search】------------------*\n");
    printf("\t\t|1.创建顺序表                                                  |\n");
    printf("\t\t|2.查找                                                        |\n");
    printf("\t\t|0.返回主菜单                                                  |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 子菜单（测试）
void Info_test(void)
{
    printf("\t\t*--------------------------【Test】----------------------------*\n");
    printf("\t\t|1.BST的建立(递增序列)                                         |\n");
    printf("\t\t|2.BST的建立(随机序列)                                         |\n");
    printf("\t\t|3.两棵BST的平均查找长度(成功与失败)                           |\n");
    printf("\t\t|4.折半查找的平均查找长度(成功与失败)                          |\n");
    printf("\t\t|5.算法性能比对                                                |\n");
    printf("\t\t|0.返回主菜单                                                  |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 输入检验（主菜单）
int  Input_menu(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0 || choice > 3)
        {
            printf("输入无效! \n");
            printf("重新输入: ");
        }
    } while(ret != 1 || choice < 0 || choice > 3);
    return choice;
}

// 输入检验（子菜单--5个选择）
int  Input_sub1(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0 || choice > 5)
        {
            printf("输入无效! \n");
            printf("重新输入: ");
        }
    } while(ret != 1 || choice < 0 || choice > 5);
    return choice;
}

// 输入检验（2个选择）
int  Input_sub2(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0 || choice > 2)
        {
            printf("输入无效! \n");
            printf("重新输入: ");
        }
    } while(ret != 1 || choice < 0 || choice > 2);
    return choice;
}

// 输入检验（>=0）
int  Input(void)
{
    int data, ret;
    do
    {
        ret = scanf("%d", &data);
        if(ret != 1 || data < 0)
        {
            printf("输入无效! \n");
            printf("重新输入: ");
        }
    } while(ret != 1 || data < 0);
    return data;
}

// BST菜单的选择
void choose_BST(void)
{
    BSTnode *BST = NULL;
    int flag = 1, key;
    for(;;)
    {
        int choice;
        Info_BST();
        choice = Input_sub1();
        switch (choice)
        {
        case 1:
            BST = Create_BST();
            break;
        case 2:
            printf("请输入待插入的数据: ");
            key = Input();
            Insert(BST, key);
            printf("插入成功!\n");
            break;
        case 3:
            printf("请输入待查找的数据: ");
            key = Input();
            Search_BST(BST, key);
            break;
        case 4:
            printf("请输入待删除的数据: ");
            key = Input();
            Delete(BST, key);
            break;
        case 5:
            InOrder(BST);
            break;
        default:
            flag = 0;
            break;
        }
        if(!flag)
        {
            system("cls");
            break;
        }
        printf("\n");
        system("pause");
    }
}

// 折半查找菜单的选择
void choose_Half(void)
{
    SeqList L;
    int flag = 1, key;
    L.n = 0;
    for(;;)
    {
        int choice;
        Info_Half();
        choice = Input_sub2();
        switch (choice)
        {
        case 1:
            Create_Seq(&L);
            Sort_in_as(&L);
            printf("已完成排序...\n");
            break;
        case 2:
            printf("请输入待查找的数据: ");
            key = Input();
            Search_Half(&L, key);
            break;
        default:
            flag = 0;
            break;
        }
        if(!flag)
        {
            system("cls");
            break;
        }
        printf("\n");
        system("pause");
    }
}

// 测试菜单的选择
void choose_test(void)
{
    BSTnode *T1 = NULL, *T2 = NULL;
    int flag = 1, key;
    list.n = 1024;
    for(;;)
    {
        int choice;
        Info_test();
        choice = Input_sub1();
        switch (choice)
        {
        case 1:
            T1 = Create_test_1();
            break;
        case 2:
            T2 = Create_test_2();
            break;
        case 3:
            ASL_BST(T1, &test[0]);
            ASL_BST(T2, &test[1]);
            printf("递增序列ASL\n查找成功: %f\n查找失败: %f\n\n", test[0].succ, test[0].fail);
            printf("随机序列ASL\n查找成功: %f\n查找失败: %f\n", test[1].succ, test[1].fail);
            break;
        case 4:
            InOrder_test(T1);
            ASL_Half(&test[2]);
            printf("折半查找ASL\n查找成功: %f\n查找失败: %f\n\n", test[2].succ, test[2].fail);
            break;
        case 5:
            printf("递增序列ASL\n查找成功: %f\n查找失败: %f\n\n", test[0].succ, test[0].fail);
            printf("随机序列ASL\n查找成功: %f\n查找失败: %f\n\n", test[1].succ, test[1].fail);
            printf("折半查找ASL\n查找成功: %f\n查找失败: %f\n\n", test[2].succ, test[2].fail);
            break;
        default:
            flag = 0;
            break;
        }
        if(!flag)
        {
            system("cls");
            break;
        }
        printf("\n\n");
        system("pause");
    }  
}

// 插入节点（BST）
BSTnode* Insert(BSTnode *BST, int key)
{
    if(BST == NULL)
    {
        BST = (BSTnode*)malloc(sizeof(BSTnode));
        if(BST == NULL)
        {
            printf("没有足够的空间分配内存! \n");
            exit(0);
        }
        BST->data = key;
        BST->lchild = NULL;
        BST->rchild = NULL;
        return BST;
    }
    else if(key < BST->data)
    {
        BST->lchild = Insert(BST->lchild, key);
    }
    else
    {
        BST->rchild = Insert(BST->rchild, key);
    }
}

// 创建BST
BSTnode* Create_BST(void)
{
    BSTnode *BST = NULL;
    int key = 1;
    while(key)
    {
        printf("请输入待插入元素(>0): ");
        key = Input();
        if(key)
            BST = Insert(BST, key);
    }
    return BST;
}

// 查找节点（BST）
BSTnode* Search_BST(BSTnode *BST, int key)
{
    if(BST == NULL)
    {
        printf("查无此数据!\n");
        return NULL;
    }
    else if(key == BST->data)
    {
        printf("查询成功! \n");
        return BST;
    }
    else if(key < BST->data)
    {
        Search_BST(BST->lchild, key);
    }
    else
    {
        Search_BST(BST->rchild, key);
    }
}

// 删除该树的最小值节点，并返回最小值（以右子树最左下方的节点作为继承节点）
int  DeleteMin(BSTnode *F)
{
    if(F->lchild == NULL)
    {
        BSTnode *P = NULL;
        int temp;
        P = F->rchild;
        temp = F->data;
        *F = *(F->rchild);
        free(P);
        printf("删除成功！\n");
        return temp;
    }
    else
    {
        DeleteMin(F->lchild);
    }
}

// 删除节点（BST）
void Delete(BSTnode *BST, int key)
{
    if(BST != NULL)
    {
        if(key < BST->data)
            Delete(BST->lchild, key);  // 查找
        else if(key > BST->data)
            Delete(BST->rchild, key);  // 查找
        else  // 找到待删除节点
        {
            BSTnode *p = NULL;
            if(BST->lchild == NULL)
            {
                p = BST->rchild;
                *BST = *(BST->rchild);
                free(p);
                printf("删除成功！\n");
            }
            else if(BST->rchild == NULL)
            {
                p = BST->lchild;
                *BST = *(BST->lchild);
                free(p);
                printf("删除成功！\n");
            }
            else  // 如果存在两棵子树
            {
                BST->data = DeleteMin(BST->rchild);
            }
        }
    }
    else
    {
        printf("查无此数据!\n");
        printf("无法删除!\n");
    }
}

// 排序（中根遍历）
void InOrder(BSTnode *BST)
{
    if(BST != NULL)
    {
        InOrder(BST->lchild);
        printf("%-4d", BST->data);
        InOrder(BST->rchild);
    }
}

// 创建线性表
void Create_Seq(SeqList *L)
{
    int i;
    printf("请输入元素个数: \n");
    L->n = Input();
    printf("请依次输入元素\n");
    for(i = 0; i < L->n; i++)
    {
        L->a[i] = Input();
    }
}

// 折半查找（顺序式线性表）
int  Search_Half(SeqList *L, int key)
{
    int low = 0, up = L->n-1, mid;
    while(low <= up)
    {
        mid = (low + up) / 2;
        if(key < L->a[mid])
        {
            up = mid - 1;
        }
        else if(key > L->a[mid])
        {
            low = mid + 1;
        }
        else
        {
            printf("查询成功!\n");
            return mid;
        }
    }
    printf("数据不存在!\n");
    printf("查询失败!\n");
    return -1;
}

// 排序（使之变成顺序线性表---插入排序）
void Sort_in_as(SeqList *L)
{
    int i, j, temp;
    for(i = 1; i < L->n; i++)
    {
        temp = L->a[i];
        j = i-1;
        while((j >= 0) && (L->a[j] > temp))
        {
            L->a[j+1] = L->a[j];
            j--;
        }
        L->a[j+1] = temp;
    }
}

// 建立BST（递增序列）
BSTnode* Create_test_1(void)
{
    BSTnode *T1 = NULL;
    int i;
    for(i = 1; i <= 1024; i++)
    {
        T1 = Insert(T1, 2*i-1);
        list.a[i-1] = 2*i-1;
        printf("%-5d", 2*i-1);
    }
    return T1;
}

// 建立BST（随机序列）
BSTnode* Create_test_2(void)
{
    BSTnode *T2 = NULL;
    int i, temp, m;
    for(i = 0; i < 1024; i++)
    {
        m = rand()%1024;
        temp = list.a[i];
        list.a[i] = list.a[m];
        list.a[m] = temp;
    }
    for(i = 0; i < 1024; i++)
    {       
        T2 = Insert(T2, list.a[i]);
        printf("%-5d", list.a[i]);
    }
    return T2;
}

// 平均查找长度---BST（包括成功与失败）
void ASL_BST(BSTnode *BST, ASL *test)
{
    int i, sum = 0;
    for(i = 1; i < 2048; i=i+2)
    {
        sum += Search_BST_ASL(BST, i);  // 查找成功
    }
    test->succ = (float)sum / 1024;
    sum = 0;
    for(i = 0; i <= 2048; i=i+2)
    {
        sum += Search_BST_ASL(BST, i);  // 查找失败
    }
    test->fail = (float)sum / 1025;
}

// BST查找（计算ASL）
int  Search_BST_ASL(BSTnode *BST, int key)
{
    if(BST == NULL)
    {
        return 0;
    }
    else if(key == BST->data)
    {
        return 1;
    }
    else if(key < BST->data)
    {
        return Search_BST_ASL(BST->lchild, key) + 1;
    }
    else
    {
        return Search_BST_ASL(BST->rchild, key) + 1;
    }
}

// 创建测试顺序表（以BST的中根遍历作为输入）
void InOrder_test(BSTnode *BST)
{
    static int count = 0;
    if(BST != NULL)
    {
        InOrder_test(BST->lchild);
        list.a[count] = BST->data;
        count++;
        InOrder_test(BST->rchild);
    }
}

// 平均查找长度---折半查找（包括成功与失败）
void ASL_Half(ASL *test)
{
    int i, sum = 0;
    for(i = 1; i < 2048; i=i+2)
    {
        sum += Search_Half_ASL(i);  // 查找成功
    }
    test->succ = (float)sum / 1024;
    sum = 0;
    for(i = 0; i <= 2048; i=i+2)
    {
        sum += Search_Half_ASL(i);  // 查找失败
    }
    test->fail = (float)sum / 1025;
}

// 折半查找（计算ASL）
int  Search_Half_ASL(int key)
{
    int low = 0, up = list.n-1, mid, count = 0;
    while(low <= up)
    {
        mid = (low + up) / 2;
        if(key < list.a[mid])
        {
            up = mid - 1;
            count++;
        }
        else if(key > list.a[mid])
        {
            low = mid + 1;
            count++;
        }
        else
        {
            count++;
            return count;
        }
    }
    return count;
}