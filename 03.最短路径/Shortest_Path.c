#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 20
#define M 100
#define Max 0x3f3f3f3f
typedef struct MTgraph   // 邻接矩阵（有向图）
{
    char vexlist[N];
    int edge[N][N];
    int n,e;
} MTgraph;
typedef struct Node   // 最小堆的节点（包括节点下标及入队时的最短路径长度）
{
    int vex;          
    int length;
} Node;
typedef struct Heap   // 最小堆
{
    Node Q[M];
    int n;
} Heap;
void Info(void);
void Info_Dijkstra(void);
void Info_Floyd(void);
int  Input_choice_main(void);
int  Input_choice_Dijkstra(void);
int  Input_choice_Floyd(void);
int  Input_common(void);
int  Input_common(void);
void choose_Dijkstra(void);
void choose_Floyd(void);
void Create_MTgraph(MTgraph *G);
int  Dijkstra(MTgraph *G, int *D, int *P, int *S);
void Print_Dijkstra(MTgraph *G, int *D, int *P, int sour);
void My_intcpy(MTgraph *G, int j, int *a);
void Floyd(MTgraph *G, int D[][N], int P[][N]);
void Print_Floyd(MTgraph *G, int D[][N], int P[][N]);
void Path_index(int P[][N], int i, int j);
void Path_char(MTgraph *G, int P[][N], int i, int j);
void single_target_Floyd(MTgraph *G, int D[][N], int P[][N]);
void pair_vex(MTgraph *G, int D[][N], int P[][N]);
void Warshall(MTgraph *G, int D[][N]);
void Print_Warshall(MTgraph *G, int D[][N]);
void MakeNull_Heap(Heap *heap);
int  Empty_Heap(Heap *heap);
int  Full_Heap(Heap *heap);
void Insert_Heap(Heap *heap, int vex, int length);
Node DeleteMin_heap(Heap *heap);
int  Dijkstra_MinHeap(MTgraph *G, int *D, int *P, int *S);
int main(void)
{
    int choice;
    for(;;)
    {
        Info();
        choice = Input_choice_main();
        switch(choice)
        {
            case 1:
                system("cls");
                choose_Dijkstra();
                break;
            case 2:
                system("cls");
                choose_Floyd();
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
    printf("\t\t*-------------------【Shortest Path System】-------------------*\n");
    printf("\t\t|1.Dijkstra                                                    |\n");
    printf("\t\t|2.Floyd                                                       |\n");
    printf("\t\t|0.退出程序                                                    |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请选择其中一种算法：");
}

// 子菜单（Dijkstra）
void Info_Dijkstra(void)
{
    printf("\t\t*-------------------------【Dijkstra】-------------------------*\n");
    printf("\t\t|1.创建有向图                                                  |\n");
    printf("\t\t|2.生成算法                                                    |\n");
    printf("\t\t|3.最小堆优化Dijkstra                                          |\n");
    printf("\t\t|0.退出程序                                                    |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
}

// 子菜单（Floyd）
void Info_Floyd(void)
{
    printf("\t\t*--------------------------【Floyd】---------------------------*\n");
    printf("\t\t|1.创建有向图                                                  |\n");
    printf("\t\t|2.生成算法                                                    |\n");
    printf("\t\t|3.单目标最短路径                                              |\n");
    printf("\t\t|4.单顶点对间最短路径                                          |\n");
    printf("\t\t|5.Warshall---可达矩阵                                         |\n");
    printf("\t\t|0.退出程序                                                    |\n");
    printf("\t\t*--------------------------------------------------------------*\n");
    printf("请输入你的选择：");
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

// 输入检查（Dijkstra）
int  Input_choice_Dijkstra(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0 || choice >3)
        {
            while(getchar() != '\n');
            printf("输入无效！\n");
            printf("重新输入: ");
        }  
    } while (ret != 1 || choice < 0 || choice >3);
    return choice;
}

// 输入检查（Floyd）
int  Input_choice_Floyd(void)
{
    int choice, ret;
    do
    {
        ret = scanf("%d", &choice);
        if(ret != 1 || choice < 0 || choice >5)
        {
            while(getchar() != '\n');
            printf("输入无效！\n");
            printf("重新输入: ");
        }  
    } while (ret != 1 || choice < 0 || choice >5);
    return choice;
}

// 输入检查（>=0）
int  Input_common(void)
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

// 选择（Dijkstra）
void choose_Dijkstra(void)
{
    int choice, flag = 1, sour;
    int D[N], P[N], S[N] = {0};    // D为存放最短路径长度数组；P为存放最短路径数组；S为存放源点和已生成的终点
    MTgraph G;
    G.n = 0;
    for(;;)
    {
        Info_Dijkstra();
        choice = Input_choice_Dijkstra();
        switch(choice)
        {
            case 1:
                Create_MTgraph(&G);
                break;
            case 2:
                memset(S, 0, sizeof(S));
                sour = Dijkstra(&G, D, P, S);
                printf("\n");
                Print_Dijkstra(&G, D, P, sour);
                break;
            case 3:
                memset(S, 0, sizeof(S));
                sour = Dijkstra_MinHeap(&G, D, P, S);
                printf("\n");
                Print_Dijkstra(&G, D, P, sour);
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

// 选择（Floyd）
void choose_Floyd(void)
{
    int choice, flag = 1;
    int D[N][N], P[N][N];
    MTgraph G;
    G.n = 0;
    for(;;)
    {
        Info_Floyd();
        choice = Input_choice_Floyd();
        switch(choice)
        {
            case 1:
                Create_MTgraph(&G);
                break;
                
            case 2:
                Floyd(&G, D, P);
                Print_Floyd(&G, D, P);
                break;
            case 3:
                single_target_Floyd(&G, D, P);
                break;
            case 4:
                pair_vex(&G, D, P);
                break;
            case 5:
                Warshall(&G, D);
                Print_Warshall(&G, D);
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

// 创建有向图（邻接矩阵）
void Create_MTgraph(MTgraph *G)
{
    freopen("Directed_Graph.txt", "r", stdin);
    int i, j, ret, k, weight;
    printf("请输入图的顶点个数(n>0): \n");
    G->n = Input_common();
    printf("请输入图的边个数(e>=0): \n");
    G->e = Input_common();
    printf("请依次输入图的每个顶点\n");
    for(i = 0; i < G->n; i++)
    {
        while(getchar() != '\n');  // 清除缓冲区的字符（包括换行符）
        printf("顶点%d: \n", i+1);
        G->vexlist[i] = getchar();
    }
    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
        {
            if(i == j)
            {
                G->edge[i][j] = 0;  // 若i=j，则将其赋值为0
            }
            else
            {
                G->edge[i][j] = Max;  // 将矩阵的权值初始化位无穷大
            }
            
        }
    }
    for(k = 0; k < G->e; k++)
    {
        printf("请输入边ij的两个端点的编号及相应的权值(i j weight): \n");
        do
        {
            ret = scanf("%d %d %d", &i, &j, &weight);
            if(ret != 3 || i<=0 || i>G->n || j <=0 || j >G->n)  // 判断输入是否合法
            {
                while(getchar()!='\n');
                printf("输入有误！\n");
                printf("请重新输入: ");
            }
        } while (ret != 3 || i<=0 || i>G->n || j <=0 || j >G->n);
        G->edge[i-1][j-1] = weight;            // 输入权值
        printf("\n");
    }
    freopen("CON", "r", stdin);
}

// Dijkstra算法实现
int  Dijkstra(MTgraph *G, int *D, int *P, int *S)
{
    int i, j, sour, w = 0, temp, sum;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法操作！\n");
        return -1;
    }
    printf("请确认最短路径的源点(下标): ");
    sour = Input_common()-1;
    S[sour] = 1;                // 把源点加入顶点集S
    for(i = 0; i < G->n; i++)   // 初始化最短路径长度矩阵D
    {
        D[i] = G->edge[sour][i];
    }
    for(i = 0; i < G->n; i++)   // 初始化最短路径矩阵（最开始都置为源点）
    {
        P[i] = sour;
    }
    for(i = 0; i < G->n-1; i++)
    {
        temp = Max;
        for(j = 0; j < G->n; j++)   // 找出V-S中，使D[w]值最小的w
        {
            if(!S[j] && temp >= D[j])
            {
                temp = D[j];
                w = j;
            }
        }
        S[w] = 1;                  // 把点w加入S
        for(j = 0; j < G->n; j++) 
        {
            sum = D[w]+G->edge[w][j];
            if(!S[j] && D[j] > sum)
            {
                D[j] = sum;  // 更新最短路径
                P[j] = w;    // 把j的最短路径的前置节点置为w
            }
        }
    }
    return sour;
}

// 打印最短路径长度和最短路径（Dijkstra）
void Print_Dijkstra(MTgraph *G, int *D, int *P, int sour)
{
    int i, j, k, temp[N];
    for(i = 0; i < G->n; i++)
    {
        if(i != sour)
        {
            printf("%d--->%d: \n", sour+1, i+1);
            if(D[i] >= Max)
            {
                printf("不存在最短路径\n\n");
                continue;
            }
            printf("最短路径长度为: %d\n", D[i]);
            k = i;
            temp[N-1] = k;    // 该数组用来暂时存储路径（从后往前存储）
            j = N-2;
            while(k != sour)
            {
                k = P[k];    // 往前回溯
                temp[j] = k;
                j--;
            }
            printf("最短路径为: ");
            My_intcpy(G, j+1, temp);
            printf("\n\n");
        }
    }
}

// 从指定位置开始输出数组（Dijkstra）
void My_intcpy(MTgraph *G, int j, int *a)
{
    for(; j < N; j++)
    {
        printf("%c", G->vexlist[a[j]]);
    }
}

// Floyd算法实现
void Floyd(MTgraph *G, int D[][N], int P[][N])
{
    int i, j, k;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法操作！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
        {
            D[i][j] = G->edge[i][j];
            P[i][j] = -1;
        }
    }
    for(k = 0; k < G->n; k++)
    {
        for(i = 0; i < G->n; i++)
        {
            for(j = 0; j < G->n; j++)
            {
                if(D[i][k] + D[k][j] < D[i][j] && i != j)
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }
}

// 打印最短路径长度和最短路径（Floyd)
void Print_Floyd(MTgraph *G, int D[][N], int P[][N])
{
    int i, j;
    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
        {
            if(D[i][j] < Max && i != j)
            {
                printf("%c(%d)-->%c(%d)的最短路径长度: %d\n", G->vexlist[i], i+1, G->vexlist[j], j+1, D[i][j]);
                printf("最短路径: %c", G->vexlist[i]);
                Path_char(G, P, i, j);
                printf("%c\n\n", G->vexlist[j]);
            }
        }
    }
}

// 求最短路径（输出下标）
void Path_index(int P[][N], int i, int j)
{
    int k;
    k = P[i][j];
    if(k != -1)
    {
        Path_index(P, i, k);
        printf("%d", k+1);
        Path_index(P, k, j);
    }
}

// 求最短路径（输出字符）
void Path_char(MTgraph *G, int P[][N], int i, int j)
{
    int k;
    k = P[i][j];
    if(k != -1)
    {
        Path_char(G, P, i, k);
        printf("%c", G->vexlist[k]);
        Path_char(G, P, k, j);
    }
}

// 单目标最短路径（FLoyd）
void single_target_Floyd(MTgraph *G, int D[][N], int P[][N])
{
    int i, j, k;
    char target;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法操作！\n");
        return;
    }
    printf("请输入目标顶点: ");
    while(getchar()!='\n');
    target = getchar();
    for(i = 0; i < G->n; i++)
    {
        if(G->vexlist[i] == target)
        {
            k = i;
        }
    }
    Floyd(G, D, P);
    for(i = 0; i < G->n; i++)
    {
        if(i == k)
            continue;
        printf("\n**出发点为%c(%d)**\n", G->vexlist[i], i+1);
        if(D[i][k] >= Max)
        {
            printf("不存在最短路径\n");
        }
        else
        {
            printf("最短路径: ");
            printf("%c", G->vexlist[i]);
            Path_char(G, P, i, k);
            printf("%c\n", G->vexlist[k]);
            printf("最短路径长度: %d\n", D[i][k]);
        }
    }
}

// 单顶点对最短路径（Floyd）
void pair_vex(MTgraph *G, int D[][N], int P[][N])
{
    int i, j, s, t, temp;
    char sour, tar;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法操作！\n");
        return;
    }
    printf("请输入顶点对的字符(i j): ");
    while(getchar()!='\n');
    scanf("%c %c", &sour, &tar);
    for(i = 0; i < G->n; i++)   // 找到顶点对的下标
    {
        if(G->vexlist[i] == sour)
            s = i;
        if(G->vexlist[i] == tar)
            t = i;
    }
    Floyd(G, D, P);
    for(i = 0; i < 2; i++)
    {
        printf("\n%c(%d) ---> %c(%d)\n", G->vexlist[s], s+1, G->vexlist[t], t+1);
        if(D[s][t] >= Max)
        {
            printf("不存在最短路径！\n");
        }
        else
        {
            printf("最短路径: ");
            printf("%c", G->vexlist[s]);
            Path_char(G, P, s, t);
            printf("%c\n", G->vexlist[t]);
            printf("最短路径长度: %d\n", D[s][t]);
        }
        temp = s;
        s = t;
        t = temp;
    }
}

// 计算有向图的可达矩阵（Warshall）
void Warshall(MTgraph *G, int D[][N])
{
    int i, j, k;
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法操作！\n");
        return;
    }
    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
        {
            if(G->edge[i][j] < Max)   // 可达矩阵初始化
            {
                D[i][j] = 1;
            }
            else
            {
                D[i][j] = 0;
            }
        }
    }
    for(k = 0; k < G->n; k++)
    {
        for(i = 0; i < G->n; i++)
        {
            for(j = 0; j < G->n; j++)
            {
                D[i][j] = D[i][j] || (D[i][k] && D[k][j]);
            }
        }
    }
}

// 打印可达矩阵（Warshall）
void Print_Warshall(MTgraph *G, int D[][N])
{
    int i, j;
    for(i = 0; i < G->n; i++)
    {
        for(j = 0; j < G->n; j++)
        {
            printf("%-4d", D[i][j]);
        }
        printf("\n");
    }
}

// 创建一个空堆
void MakeNull_Heap(Heap *heap)
{
    heap->n = 0;
}

// 判断堆是否为空
int  Empty_Heap(Heap *heap)
{
    if(heap->n == 0)
        return 1;
    else
        return 0;
}

// 判断堆是否已满
int  Full_Heap(Heap *heap)
{
    if(heap->n == M-1)
        return 1;
    else
        return 0;
}

// 向堆中插入元素
void Insert_Heap(Heap *heap, int vex, int length)
{
    int k;
    if(!Full_Heap(heap))
    {
        k = heap->n + 1;
        while(k != 1 && heap->Q[k/2].length > length)
        {
            heap->Q[k].length = heap->Q[k/2].length;
            heap->Q[k].vex = heap->Q[k/2].vex;
            k = k/2;
        }
    }
    heap->n++;
    heap->Q[k].length = length;
    heap->Q[k].vex = vex;;
}

// 向堆中删除元素（同时返回最小元素）
Node DeleteMin_heap(Heap *heap)
{
    int parent = 1, child = 2;
    Node item, temp;
    if(!Empty_Heap(heap))
    {
        item.length = heap->Q[1].length;
        item.vex = heap->Q[1].vex;
        temp.length = heap->Q[heap->n].length;
        temp.vex = heap->Q[heap->n].vex;
        heap->n--;   // 删除节点
        while(child <= heap->n)
        {
            if(child < heap->n && heap->Q[child].length > heap->Q[child+1].length)  // 先找出左右儿子中最小的元素
            {
                child++;
            }
            if(temp.length < heap->Q[child].length)  // 已经找到最小的元素，跳出循环
                break;
            else
            {
                heap->Q[parent].length = heap->Q[child].length;
                heap->Q[parent].vex = heap->Q[child].vex;
                parent = child;
                child *= 2;
            }
        }
        heap->Q[parent].length = temp.length;
        heap->Q[parent].vex = temp.vex;
        return item;
    }
}

// 用最小堆优化Dijkstra算法
int  Dijkstra_MinHeap(MTgraph *G, int *D, int *P, int *S)
{
    int sour, i, sum;
    Heap heap;
    Node temp;
    MakeNull_Heap(&heap);
    if(G->n == 0)
    {
        printf("未创建图！\n");
        printf("无法操作！\n");
        return -1;
    }
    printf("请确认最短路径的源点(下标): ");
    sour = Input_common()-1;
    for(i = 0; i < G->n; i++)   // 初始化最短路径长度矩阵
    {
        if(i == sour)
            D[i] = 0;
        else
            D[i] = Max;
    }
    for(i = 0; i < G->n; i++)   // 初始化最短路径矩阵（最开始都置为源点）
    {
        P[i] = sour;
    }
    Insert_Heap(&heap, sour, 0);   // 先将源点插入最小堆
    while(!Empty_Heap(&heap))
    {
        temp = DeleteMin_heap(&heap);  // 返回堆顶元素，并将其出队
        if(S[temp.vex])
            continue;
        else
            S[temp.vex] = 1;      // 将使D[w]最小的w标记
        for(i = 0; i < G->n; i++)
        {
            sum = D[temp.vex]+G->edge[temp.vex][i];
            if(!S[i] && D[i] > sum)
            {
                D[i] = sum;  // 更新最短路径
                P[i] = temp.vex;    // 把j的最短路径的前置节点置为w
                Insert_Heap(&heap, i, D[i]);   // 把更新过的最短路径长度及相应的终点加入最小堆中
            }
        }
    }
    return sour;
}