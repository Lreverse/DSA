#include<stdio.h>
#include<stdlib.h>
#define N 50
int visited[N];      // 定义标记数组
int dfn[N];          // 定义先深编号
int bfn[N];          // 定义先广编号
int count_DFS;
int count_BFS;
typedef struct MTgraph  // 邻接矩阵
{
    char vexlist[N];
    int edge[N][N];
    int n,e;
} MTgraph;
typedef struct EdgeNode  // 边表节点
{
    int adjvex;
    struct EdgeNode *next;
} EdgeNode;
typedef struct VertexNode  // 顶点表节点
{
    char vertex;
    EdgeNode *first;
} VertexNode;
typedef struct Adjgraph  // 邻接表
{
    VertexNode vexlist[N];
    int n,e;
} Adjgraph;
typedef struct queueNode  // 队列节点
{
    int adjvex;
    struct queueNode *next;
} queueNode;
typedef struct queue   // 队列
{
    queueNode *front;
    queueNode *rear;
} queue;
typedef struct stack  // 栈
{
    int adjvex;
    struct stack *next;
} stack;
Adjgraph Tree_Adj; // 生成树或森林（邻接表）
Adjgraph Tree_MT;  // 生成树或森林（邻接矩阵）
void Info(void);
void Info_MT(void);
void Info_Adj(void);
void choose_MT(void);
void choose_Adj(void);
int Input_choice_main(void);
int Input_choice_sub(void);
int Input_common(void);
void Create_MTgraph(MTgraph *G);
void Print_MTgraph(MTgraph *G);
void Create_Adjgraph(Adjgraph *G);
void Insert_EdgeNode(VertexNode *head, int tail);
void Print_Adjgraph(Adjgraph *G);
void Transform_to_Adj(MTgraph *G);
void Transform_to_MT(Adjgraph *G);
void Treeinit_Adj(Adjgraph *Tree, Adjgraph *G); 
void Treeinit_MT(Adjgraph *Tree, MTgraph *G); 
void DFS_Adj(Adjgraph *G);
void DFS_Adj_search(Adjgraph *G, int i);
void DFS_MT(MTgraph *G);
void DFS_MT_search(MTgraph *G, int i);
void NDFS_Adj(Adjgraph *G);
void NDFS_Adj_search(Adjgraph *G, int i);
void NDFS_MT(MTgraph *G);
void NDFS_MT_search(MTgraph *G, int i);
void BFS_Adj(Adjgraph *G);
void BFS_Adj_search(Adjgraph *G, int i);
void BFS_MT(MTgraph *G);
void BFS_MT_search(MTgraph *G, int i);
void MakeNull_Q(queue *Q);
int  Empty_Q(queue *Q);
int  Front(queue *Q);
void EnQueue(queue *Q, int i);
void DeQueue(queue *Q);
stack* MakNull_S(void);
int  Empty_S(stack *S);
int  Top(stack *S);
void Push(stack *S, int i);
void Pop(stack *S);
void Cal_degree_Adj(Adjgraph *G);
void Cal_degree_MT(MTgraph *G);
int main(void)
{
    int choice;
    for(;;)
    {
        Info();
        choice = Input_choice_main();
        switch (choice)
        {
        case 1:
            system("cls");
            choose_MT();
            break;
        case 2:
            system("cls");
            choose_Adj();
            break;
        default:
            exit(0);
            break;
        }
    }
    return 0;
}

// 主菜单
void Info(void)
{
    printf("\t\t*------------【Undirected Graph Operation System】-------------*\n");
    printf("\t\t|1.邻接矩阵                                                    |\n");
    printf("\t\t|2.邻接表                                                      |\n");
    printf("\t\t|0.退出程序                                                    |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请选择其中一种存储方式：");
}

// 子菜单--邻接矩阵
void Info_MT(void)
{
    printf("\t\t*-------------------------【MT-Graph】-------------------------*\n");
    printf("\t\t|1.创建无向图                                                  |\n");
    printf("\t\t|2.打印邻接矩阵                                                |\n");
    printf("\t\t|3.邻接矩阵-->邻接表                                           |\n");
    printf("\t\t|4.深度优先搜索--递归                                          |\n");
    printf("\t\t|5.深度优先搜索--非递归                                        |\n");    
    printf("\t\t|6.广度优先搜索                                                |\n");
    printf("\t\t|7.计算各顶点的度                                              |\n");
    printf("\t\t|0.返回主菜单                                                  |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 子菜单--邻接表
void Info_Adj(void)
{
    printf("\t\t*-------------------------【Adj-Graph】------------------------*\n");
    printf("\t\t|1.创建无向图                                                  |\n");
    printf("\t\t|2.打印邻接表                                                  |\n");
    printf("\t\t|3.邻接表-->邻接矩阵                                           |\n");
    printf("\t\t|4.深度优先搜索--递归                                          |\n");
    printf("\t\t|5.深度优先搜索--非递归                                        |\n");   
    printf("\t\t|6.广度优先搜索                                                |\n");
    printf("\t\t|7.计算各顶点的度                                              |\n");   
    printf("\t\t|0.返回主菜单                                                  |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 选择--邻接矩阵
void choose_MT(void)
{
    MTgraph G1;
    G1.n = 0;
    int choice, flag = 1;
    for(;;)
    {
        Info_MT();
        choice = Input_choice_sub();
        switch (choice)
        {
        case 1:
            Create_MTgraph(&G1);
            break;
        case 2:
            Print_MTgraph(&G1);
            break;
        case 3:
            Transform_to_Adj(&G1);
            break;
        case 4:
            DFS_MT(&G1);
            break;
        case 5:
            NDFS_MT(&G1);
            break;
        case 6:
            BFS_MT(&G1);
            break;
        case 7:
            Cal_degree_MT(&G1);
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

// 选择--邻接表
void choose_Adj(void)
{
    Adjgraph G2;
    G2.n = 0;
    int choice, flag = 1;
    for(;;)
    {
        Info_Adj();
        choice = Input_choice_sub();
        switch (choice)
        {
        case 1:
            Create_Adjgraph(&G2);
            break;
        case 2:
            Print_Adjgraph(&G2);
            break;
        case 3:
            Transform_to_MT(&G2);
            break;
        case 4:
            DFS_Adj(&G2);
            break;
        case 5:
            NDFS_Adj(&G2);
            break;
        case 6:
            BFS_Adj(&G2);
            break;
        case 7:
            Cal_degree_Adj(&G2);
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

// 输入检查（主菜单）
int Input_choice_main(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0 || choice >2)
        {
            while(getchar() != '\n');
            printf("输入无效！\n");
            printf("重新输入: ");
        }  
    } while (ret != 1 || choice < 0 || choice >2);
    return choice;
}

// 输入检查（子菜单）
int Input_choice_sub(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0 || choice >7)
        {
            while(getchar() != '\n');
            printf("输入无效！\n");
            printf("重新输入: ");
        }  
    } while (ret != 1 || choice < 0 || choice >7);
    return choice;   
}

// 输入检查（>=0） 
int Input_common(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0)
        {
            while(getchar() != '\n');
            printf("输入无效！\n");
            printf("重新输入: ");
        }
    } while (ret != 1 || choice < 0);
    return choice;
}

// 创建图（邻接矩阵）
void Create_MTgraph(MTgraph *G)
{
    int i, j, k, w, ret;
    printf("请输入图的顶点个数(n>0): ");
    G->n = Input_common();
    printf("请输入图的边数(e>=0): ");
    G->e = Input_common();
    printf("请依次输入图的每个顶点\n");
    for(i = 0; i < G->n; i++)
    {
        while(getchar() != '\n');    // 清除缓冲区的字符(包括换行符)
        printf("顶点%d: ", i+1);
        G->vexlist[i] = getchar();    // 向顶点表存入每个顶点字符
    }
    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
        {
            G->edge[i][j] = 0;      // 初始化邻接矩阵
        }
    }
    for(k = 0; k < G->e; k++)
    {
        printf("请输入边ij的两个端点的编号(i j): ");
        do
        {
            ret = scanf("%d %d", &i, &j);
            if(ret != 2 || i<=0 || i>=G->n || j <=0 || j >G->n)
            {
                while(getchar()!='\n');
                printf("输入有误！\n");
                printf("请重新输入: ");
            }
        } while (ret != 2 || i<=0 || i>=G->n || j <=0 || j >G->n);
        G->edge[i-1][j-1] = 1;
        G->edge[j-1][i-1] = 1;
    }
}

// 打印邻接矩阵
void Print_MTgraph(MTgraph *G)
{
    int i,j;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法打印！\n");
        return;
    }
    printf("   ");
    for(i = 0; i < G->n; i++)
    {
        printf("%-4c", G->vexlist[i]);
    }
    printf("\n");
    for(i = 0; i < G->n; i++)
    {
        printf("%c  ", G->vexlist[i]);
        for(j = 0; j < G->n; j++)
        {
            printf("%-4d", G->edge[i][j]);
        }
        printf("\n");
    }
}

// 创建图（邻接表）
void Create_Adjgraph(Adjgraph *G)
{
    int i, head, tail;
    printf("请输入图的顶点个数: ");
    G->n = Input_common();
    printf("请输入图的边数: ");
    G->e = Input_common();
    printf("请依次输入图的每个顶点\n");
    for(i = 0; i < G->n; i++)
    {
        while(getchar()!='\n');           // 清除缓冲区的字符(包括换行符)
        printf("顶点%d: ", i+1);
        G->vexlist[i].vertex = getchar();  // 向顶点表存入每个顶点字符
        G->vexlist[i].first = NULL;        // 同时将每个指针域初始化为null
    }
    for(i = 0; i < G->e; i++)
    {
        printf("请输入边ij的两个端点的编号(i j): ");
        head = Input_common() - 1;
        tail = Input_common() - 1;
        Insert_EdgeNode(&G->vexlist[head], tail);
        Insert_EdgeNode(&G->vexlist[tail], head);
    }
}

// 向顶点表的顶点插入边表节点（邻接表）
void Insert_EdgeNode(VertexNode *head, int tail)
{
    EdgeNode *p = NULL;
    p = (EdgeNode*)malloc(sizeof(EdgeNode));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存!\n");
        exit(0);
    }
    p->adjvex = tail;
    p->next = head->first;
    head->first = p;
}

// 打印邻接表
void Print_Adjgraph(Adjgraph *G)
{
    int i;
    EdgeNode *k = NULL;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法打印！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        printf("顶点%d: %c", i+1, G->vexlist[i].vertex);
        k = G->vexlist[i].first;
        if(k == NULL)
        {
            printf("\n");
            continue;
        }
        else
        {
            while(k!=NULL)
            {
                printf("--->%d", k->adjvex+1);
                k = k->next;
            }
            printf("\n");
        }
    }
}

// 将邻接矩阵转换为邻接表
void Transform_to_Adj(MTgraph *G)
{
    Adjgraph G0;
    int i, j;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法转换！\n");
        return;
    }
    G0.e = G->e;
    G0.n = G->n;
    for(i = 0; i < G0.n; i++)
    {
        G0.vexlist[i].vertex = G->vexlist[i];  // 将邻接矩阵的字符转移到邻接表
        G0.vexlist[i].first = NULL;            // 初始化邻接表的顶点表的指针域
    }
    for(i = 0; i < G0.n; i++)
    {
        for(j = i+1; j < G0.n; j++)
        {
            if(G->edge[i][j] == 1)
            {
                Insert_EdgeNode(&G0.vexlist[i], j);
                Insert_EdgeNode(&G0.vexlist[j], i);
            }
        }
    }
    printf("转换成功！\n");
    printf("转换后的邻接表如下: \n");
    Print_Adjgraph(&G0);
}

// 将邻接表转换为邻接矩阵
void Transform_to_MT(Adjgraph *G)
{
    MTgraph G0;
    int i, j;
    EdgeNode *k = NULL;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法转换！\n");
        return;
    }
    G0.e = G->e;
    G0.n = G->n;
    for (i = 0; i < G0.n; i++)
    {
        G0.vexlist[i] = G->vexlist[i].vertex;  // 将邻接表的字符转移到邻接矩阵
    }
    for (i = 0; i < G->n; i++)
    {
        for (j = 0; j < G->n; j++)
        {
            G0.edge[i][j] = 0;        // 初始化邻接矩阵
        }
    }
    for(i = 0; i < G0.n; i++)
    {
        k = G->vexlist[i].first;
        if(k == NULL)
        {
            continue;
        }
        else
        {
            while(k != NULL)
            {
                G0.edge[i][k->adjvex] = 1;
                k = k->next;
            }
        }
    }
    printf("转换成功！\n");
    printf("转换后的邻接矩阵如下: \n");
    Print_MTgraph(&G0);
}

// 初始化生成森林（邻接表）
void Treeinit_Adj(Adjgraph *Tree, Adjgraph *G)
{
    int i;
    Tree->e = G->e;
    Tree->n = G->n;
    for(i = 0; i < G->n; i++)
    {
        Tree->vexlist[i].vertex = G->vexlist[i].vertex;
        Tree->vexlist[i].first = NULL;
    }
}

// 初始化生成森林（邻接矩阵）
void Treeinit_MT(Adjgraph *Tree, MTgraph *G)
{
    int i;
    Tree->e = G->e;
    Tree->n = G->n;
    for(i = 0; i < G->n; i++)
    {
        Tree->vexlist[i].vertex = G->vexlist[i];
        Tree->vexlist[i].first = NULL;
    }
}

// 深度优先搜索主算法--递归（邻接表）
void DFS_Adj(Adjgraph *G)
{
    int i;
    Treeinit_Adj(&Tree_Adj, G);
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法搜索！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        visited[i] = 0;   // 初始化标记数组
    }
    printf("**深度优先序列**\n");
    for(i = 0; i < G->n; i++)
    {
        if(!visited[i])
        {
            DFS_Adj_search(G, i);
        }
    }
    printf("\n\n**深度优先编号**\n");
    for(i = 0; i < G->n; i++)
    {
        printf("%c: %d\n", G->vexlist[i].vertex, dfn[i]);
    }
    printf("\n**深度优先生成森林**\n");
    Print_Adjgraph(&Tree_Adj);
}

// 先深搜索--递归（邻接表）
void DFS_Adj_search(Adjgraph *G, int i)
{
    EdgeNode *k = NULL, *t = NULL;
    static int count = 0;
    printf("%c", G->vexlist[i].vertex);  // 访问当前节点
    visited[i] = 1;      // 将当前节点置为访问过
    dfn[i] = count;      // 先深编号
    count++;
    k = G->vexlist[i].first;
    while(k != NULL)    // 依次搜索当前节点的所有邻接点
    {
        if (!visited[k->adjvex])
        {
            DFS_Adj_search(G, k->adjvex);
            Insert_EdgeNode(&Tree_Adj.vexlist[i], k->adjvex);  // 把边插入到生成树中
        }
        k = k->next;
    }
}

// 深度优先搜索主算法--非递归（邻接表）
void NDFS_Adj(Adjgraph *G)
{
    int i;
    Treeinit_Adj(&Tree_Adj, G);
    count_DFS = 0;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法搜索！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        visited[i] = 0;   // 初始化标记数组
    }
    printf("**深度优先序列**\n");
    for(i = 0; i < G->n; i++)
    {
        if(!visited[i])
        {
            NDFS_Adj_search(G, i);
        }
    }
    printf("\n\n**深度优先编号**\n");
    for(i = 0; i < G->n; i++)
    {
        printf("%c: %d\n", G->vexlist[i].vertex, dfn[i]);
    }
    printf("\n**深度优先生成森林**\n");
    Print_Adjgraph(&Tree_Adj);
}

// 先深搜索--非递归（邻接表）
void NDFS_Adj_search(Adjgraph *G, int i)
{
    stack *S = NULL;
    EdgeNode *k = NULL;
    int j;
    S = MakNull_S();
    printf("%c", G->vexlist[i].vertex);  // 访问当前节点
    visited[i] = 1;      // 将当前节点置为访问过
    dfn[i] = count_DFS;      // 先深编号
    count_DFS++;
    Push(S, i);
    while(!Empty_S(S))
    {
        j = Top(S);
        k = G->vexlist[j].first;
        while(k != NULL)    // 对节点j的边表进行遍历，若一遇到未访问的，则立马退出循环，并将其入栈
        {
            if(!visited[k->adjvex])
            {
                break;
            }
            k = k->next;
        }
        if(k == NULL)
        {
            Pop(S);
        }
        else
        {
            printf("%c", G->vexlist[k->adjvex].vertex);
            visited[k->adjvex] = 1;
            dfn[k->adjvex] = count_DFS;
            count_DFS++;
            Insert_EdgeNode(&Tree_Adj.vexlist[j], k->adjvex);  // 把边插入到生成树中
            Push(S, k->adjvex);
        }
    }
}

// 深度优先搜素主算法--递归（邻接矩阵）
void DFS_MT(MTgraph *G)
{
    int i;
    Treeinit_MT(&Tree_MT, G);
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法搜索！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        visited[i] = 0;   // 初始化标记数组
    }
    printf("**深度优先序列**\n");
    for(i = 0; i < G->n; i++)
    {
        if(!visited[i])
        {
            DFS_MT_search(G, i);
        }
    }
    printf("\n\n**深度优先编号**\n");
    for(i = 0; i < G->n; i++)
    {
        printf("%c: %d\n", G->vexlist[i], dfn[i]);
    }
    printf("\n**深度优先生成森林**\n");
    Print_Adjgraph(&Tree_MT);
}

// 先深搜索--递归（邻接矩阵)
void DFS_MT_search(MTgraph *G, int i)
{
    static int count = 0;
    int j;
    printf("%c", G->vexlist[i]);  // 访问当前节点
    visited[i] = 1;      // 将当前节点置为访问过
    dfn[i] = count;      // 先深编号
    count++;
    for(j = 0; j < G->n; j++)
    {
        if(G->edge[i][j] == 1 && !visited[j])
        {
            DFS_MT_search(G, j);
            Insert_EdgeNode(&Tree_MT.vexlist[i], j);  // 把边插入到生成树中
        }
    }
}

// 深度优先搜索主算法--非递归（邻接矩阵）
void NDFS_MT(MTgraph *G)
{
    int i;
    Treeinit_MT(&Tree_MT, G);
    count_DFS = 0;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法搜索！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        visited[i] = 0;   // 初始化标记数组
    }
    printf("**深度优先序列**\n");
    for(i = 0; i < G->n; i++)
    {
        if(!visited[i])
        {
            NDFS_MT_search(G, i);
        }
    }
    printf("\n\n**深度优先编号**\n");
    for(i = 0; i < G->n; i++)
    {
        printf("%c: %d\n", G->vexlist[i], dfn[i]);
    }
    printf("\n**深度优先生成森林**\n");
    Print_Adjgraph(&Tree_MT);
}

// 先深搜索--非递归（邻接矩阵)
void NDFS_MT_search(MTgraph *G, int i)
{
    stack *S = NULL;
    int j, k;
    S = MakNull_S();
    printf("%c", G->vexlist[i]);  // 访问当前节点
    visited[i] = 1;      // 将当前节点置为访问过
    dfn[i] = count_DFS;      // 先深编号
    count_DFS++;
    Push(S, i);
    while(!Empty_S(S))
    {
        j = Top(S);
        for(k = 0; k < G->n; k++)
        {
            if(G->edge[j][k] == 1 && !visited[k])
            {
                break;   // 对节点j的边表进行遍历，若一遇到未访问的，则立马退出循环，并将其入栈
            }
        }
        if(k == G->n)
        {
            Pop(S);
        }
        else
        {
            printf("%c", G->vexlist[k]);
            visited[k] = 1;
            dfn[k] = count_DFS;
            count_DFS++;
            Insert_EdgeNode(&Tree_MT.vexlist[j], k);  // 把边插入到生成树中
            Push(S, k);
        }
    }
}

// 广度优先搜索主算法（邻接表）
void BFS_Adj(Adjgraph *G)
{
    int i;
    Treeinit_Adj(&Tree_Adj, G);
    count_BFS = 0;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法搜索！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        visited[i] = 0;   // 初始化标记数组
    }
    printf("**广度优先序列**\n");
    for(i = 0; i < G->n; i++)
    {
        if(!visited[i])
        {
            BFS_Adj_search(G, i);
        }
    }
    printf("\n\n**广度优先编号**\n");
    for(i = 0; i < G->n; i++)
    {
        printf("%c: %d\n", G->vexlist[i].vertex, bfn[i]);
    }
    printf("\n**广度优先生成森林**\n");
    Print_Adjgraph(&Tree_Adj);
}

// 先广搜索（邻接表）
void BFS_Adj_search(Adjgraph *G, int i)
{
    int j;
    EdgeNode *k = NULL;
    queue Q;
    MakeNull_Q(&Q);
    printf("%c", G->vexlist[i].vertex);  // 访问当前节点
    visited[i] = 1;      // 将当前节点置为访问过
    bfn[i] = count_BFS;
    count_BFS++;
    EnQueue(&Q, i);
    while(!Empty_Q(&Q))
    {
        j = Front(&Q);
        DeQueue(&Q);
        k = G->vexlist[j].first;
        while(k!=NULL)   // 遍历下标为j的节点的边表
        {
            if(!visited[k->adjvex])   // 若未访问，则进行访问
            {
                printf("%c", G->vexlist[k->adjvex].vertex);   // 访问当前节点
                visited[k->adjvex] = 1;
                bfn[k->adjvex] = count_BFS;
                count_BFS++;
                Insert_EdgeNode(&Tree_Adj.vexlist[j], k->adjvex);  // 把边插入到生成树中
                EnQueue(&Q, k->adjvex);  // 把访问过的节点入队
            }
            k = k->next;
        }
    }
}

// 广度优先搜索主算法（邻接矩阵）
void BFS_MT(MTgraph *G)
{
    int i;
    Treeinit_MT(&Tree_MT, G);
    count_BFS = 0;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法搜索！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        visited[i] = 0;   // 初始化标记数组
    }
    printf("**广度优先序列** \n");
    for(i = 0; i < G->n; i++)
    {
        if(!visited[i])
        {
            BFS_MT_search(G, i);
        }
    }
    printf("\n\n**广度优先编号**\n");
    for(i = 0; i < G->n; i++)
    {
        printf("%c: %d\n", G->vexlist[i], bfn[i]);
    }
    printf("\n**广度优先生成森林**\n");
    Print_Adjgraph(&Tree_MT);
}

// 先广搜索（邻接矩阵）
void BFS_MT_search(MTgraph *G, int i)
{
    int j, k;
    queue Q;
    MakeNull_Q(&Q);
    printf("%c", G->vexlist[i]);  // 访问当前节点
    visited[i] = 1;      // 将当前节点置为访问过
    bfn[i] = count_BFS;
    count_BFS++;
    EnQueue(&Q, i);
    while(!Empty_Q(&Q))
    {
        j = Front(&Q);
        DeQueue(&Q);
        for(k = 0; k < G->n; k++)
        {
            if(G->edge[j][k]==1 && !visited[k])
            {
                printf("%c", G->vexlist[k]);   // 访问当前节点
                visited[k] = 1;
                bfn[k] = count_BFS;
                count_BFS++;
                Insert_EdgeNode(&Tree_MT.vexlist[j], k);  // 把边插入到生成树中
                EnQueue(&Q, k);  // 把访问过的节点入队
            }
        }
    }
}

// 置空队列
void MakeNull_Q(queue *Q)
{
    Q->front = (queueNode*)malloc(sizeof(queueNode));
    if(Q->front == NULL)
    {
        printf("没有足够的存储空间分配内存！\n");
        exit(0);
    }
    Q->front->next = NULL;
    Q->rear = Q->front;
}

// 判断队列是否为空
int  Empty_Q(queue *Q)
{
    if(Q->front == Q->rear)
        return 1;
    else
        return 0;
}

// 返回队首元素
int  Front(queue *Q)
{
    if(Q->front->next != NULL)
    {
        return Q->front->next->adjvex;
    }
    else
    {
        printf("队列为空！\n");
        return -1;
    }
}

// 入队
void EnQueue(queue *Q, int i)
{
    queueNode *p = NULL;
    p = (queueNode*)malloc(sizeof(queueNode));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    p->adjvex = i;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

// 出队
void DeQueue(queue *Q)
{
    queueNode *p = Q->front->next;
    if(Empty_Q(Q))
    {
        printf("队列为空！\n");
        printf("没有可出队的元素！\n");
    }
    else
    {
        Q->front->next = p->next;
        free(p);
        if(Q->front->next == NULL)
        {
            Q->rear = Q->front;
        }
    }
}

// 计算顶点度（邻接表）
void Cal_degree_Adj(Adjgraph *G)
{
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法计算！\n");
        return;
    }
    int degree[N], i, j;
    EdgeNode *k = NULL;
    printf("各个顶点的度如下: \n");
    for(i = 0; i < G->n; i++)
    {
        j = 0;
        k = G->vexlist[i].first;
        while(k != NULL)
        {
            j++;
            k = k->next;
        }
        degree[i] = j;
        printf("%c: %d\n", G->vexlist[i].vertex, degree[i]);
    }
}

// 计算顶点度（邻接矩阵）
void Cal_degree_MT(MTgraph *G)
{
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法计算！\n");
        return;
    }
    int degree[N], i, j, k;
    printf("各个顶点的度如下: \n");
    for(i = 0; i < G->n; i++)
    {
        k = 0;
        for(j = 0; j < G->n; j++)
        {
            if(G->edge[i][j] == 1)
            {
                k++;
            }
        }
        degree[i] = k;
        printf("%c: %d\n", G->vexlist[i], degree[i]);
    }
}

// 置空栈
stack* MakNull_S(void)
{
    stack *p = NULL;
    p = (stack*)malloc(sizeof(stack));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    p->next = NULL;
    return p;
}

// 判断栈是否为空
int  Empty_S(stack *S)
{
    if(S->next == NULL)
        return 1;
    else
        return 0;
}

// 返回栈顶元素
int  Top(stack *S)
{
    if(S->next == NULL)
    {
        printf("栈为空！\n");
        return -1;
    }
    else
    {
        return S->next->adjvex;
    }
}

// 入栈
void Push(stack *S, int i)
{
    stack *p = NULL;
    p = (stack*)malloc(sizeof(stack));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    p->adjvex = i;
    p->next = S->next;
    S->next = p;
}

// 出栈
void Pop(stack *S)
{
    stack *temp = S->next;
    if(temp != NULL)
    {
        S->next = temp->next;
        free(temp);
    }
}

