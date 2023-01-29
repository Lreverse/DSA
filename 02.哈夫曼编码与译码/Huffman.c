#include<stdio.h>
#include<stdlib.h>
#define N 63
typedef struct ch_Table
{
    char ch;
    int fre;
    float p;
} ch_Table;
typedef struct HTnode
{
    char ch;
    float weight;
    int lchild;
    int rchild;
    int parent;
} HTnode;
typedef struct Codenode
{
    char ch;
    char bits[N-1];       // 由于内节点始终比外节点的个数少一，所以编码长最多不超过N-1
} Codenode;
void Initialize_FrequencyList(ch_Table *CH);
int  Create_FrequencyList(ch_Table *CH);
int  Print_FrequencyList(ch_Table *CH);
void Init_HT(HTnode *HT, int m);
void InputW(HTnode *HT, ch_Table *CH);
void Create_HT(HTnode *HT, int n);
void SelectMin(HTnode *HT, int n, int *p1, int *p2);
void Print_HT(HTnode *HT, int m);
void Create_CharsetTable(HTnode *HT, Codenode *Code, int n);
void My_strcpy(char *ch, char *code, int i);
void Print_CharsetTable(Codenode *Code, int n);
void Encoding(Codenode *Code, int n);
void Decoding(HTnode *HT, int m);
void Count_AverageLength(HTnode *HT, Codenode *Code, int n);
void Count_Compressibility(void);
void WriteToFile(HTnode *HT, Codenode *Code, int total, int n);
int main(void)
{
    ch_Table CH[N];
    int n, m, total;
    Initialize_FrequencyList(CH);
    total = Create_FrequencyList(CH);  // 得到总的输入个数
    printf("输入的总个数为: %d\n\n", total);
    n = Print_FrequencyList(CH);
    m = 2 * n - 1;                 // 得到哈夫曼树的总结点个数
    printf("\n需要进行编码的个数为: %d\n\n", n);
    HTnode HT[m];
    Init_HT(HT, m);
    InputW(HT, CH);
    Create_HT(HT, n);
    Print_HT(HT, m);
    printf("\n");
    Codenode Code[n];
    Create_CharsetTable(HT, Code, n);
    Print_CharsetTable(Code, n);
    printf("\n");
    printf("文件压缩中....\n");
    Encoding(Code, n);
    printf("文件解压中....\n\n");
    Decoding(HT, m);
    Count_AverageLength(HT, Code, n);
    Count_Compressibility();
    WriteToFile(HT, Code, total, n);
    return 0;
}

// 初始化字符频率表
void Initialize_FrequencyList(ch_Table *CH)
{ 
    FILE *fp;
    fp = freopen("standard.txt", "r", stdin);
    while(!feof(fp))
    {
        CH->ch = getchar();
        CH->fre = 0;
        CH->p = 0;
        CH++;
    }
    freopen("CON", "r", stdin);
}

// 建立对应的字符频率表
int  Create_FrequencyList(ch_Table *CH)
{
    FILE *fp;
    ch_Table *p = CH;
    char temp;
    int i = -1, j;
    fp = freopen("Input.txt", "r", stdin);
    while(!feof(fp))
    {
        temp = getchar();
        while(temp != p->ch)     // 把读入的每个字符与频率表的字符进行比对
        {
            p++;
        }
        p->fre++;                // 若找到对应的字符，则频数+1
        p = CH;
        i++;                     // 记录输入的字符总数，以便后续求解各个字符的使用频率
    }
    for(j = 0; j < N; j++)
    {
        CH->p = (float)CH->fre / i;     // 计算每个字符的使用频率
        CH++;
    }
    freopen("CON", "r", stdin);
    return i;
}

// 打印字符频率表
int  Print_FrequencyList(ch_Table *CH)
{
    int i, n = 0;
    printf("**字符频率表**\n");
    printf("字符  频数  频率\n");
    for(i = 0; i< N; i++)
    {
        if (CH->fre != 0)
        {
            printf("%-6c%-6d%-10f\n", CH->ch, CH->fre, CH->p);
            n++; // 计算需要编码的个数
        }
        CH++;
    }
    return n;
}

// 初始化哈夫曼树
void Init_HT(HTnode *HT, int m)
{
    int i;
    for(i = 0; i < m; i++)
    {
        HT->ch = '#';            // 代表空节点，区别于需要编码的字符
        HT->lchild = -1;
        HT->rchild = -1;
        HT->parent = -1;
        HT++;
    }
}

// 往哈夫曼树里存储字符频率
void InputW(HTnode *HT, ch_Table *CH)
{
    int i;
    for(i = 0; i < N; i++)
    {
        if(CH->fre == 0)
        {
            CH++;
            continue;
        }
        HT->ch = CH->ch;
        HT->weight = CH->p;
        HT++;
        CH++;
    }
}

// 建立哈夫曼树
void Create_HT(HTnode *HT, int n)
{
    int i, p1 = 0, p2 = 0;
    for (i = n; i < 2 * n - 1; i++)
    {
        SelectMin(HT, i, &p1, &p2);
        (HT+p1)->parent = (HT+p2)->parent = i;
        (HT+i)->lchild = p1;
        (HT+i)->rchild = p2;
        (HT+i)->weight = (HT+p1)->weight + (HT+p2)->weight; 
    }
}

// 从哈夫曼树中选出权值最小的两个元素
void SelectMin(HTnode *HT, int n, int *p1, int *p2)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if ((HT + i)->parent == -1)
        {
            *p1 = i;                  // 寻找还未处理过的节点
            break;
        }
    }
    for (j = i + 1; j < n; j++)
    {
        if ((HT + j)->parent == -1)
        {
            *p2 = j;                // 寻找还未遍历过的节点，同时该节点不等于p1
            break;
        }
    }
    for (i = *p1 + 1; i < n; i++)
    {
        if ((HT + *p1)->weight > (HT + i)->weight && (HT + i)->parent == -1 && i != *p2)
        {
            *p1 = i;                // 寻找第一个最小的节点
        }
    }
    for (j = 0; j < n; j++)
    {
        if ((HT + *p2)->weight > (HT + j)->weight && (HT + j)->parent == -1 && j != *p1)
        {
            *p2 = j;                // 寻找第二个最小的节点
        }
    }
}

// 打印哈夫曼树
void Print_HT(HTnode *HT, int m)
{
    int i;
    printf("**哈夫曼树的静态链表**\n");
    printf("字符    权重        父亲   左儿子  右儿子\n");
    for(i=0; i<m; i++)
    {
        printf("%-8c%-12f%-8d%-8d%-8d\n", (HT+i)->ch, (HT+i)->weight, (HT+i)->parent, (HT+i)->lchild, (HT+i)->rchild);
    }
}

// 建立字符集的哈夫曼编码表
void Create_CharsetTable(HTnode *HT, Codenode *Code, int n)
{
    int i, p, c, k;
    char temp[N-1] = {0};          // 对暂时存放编码的数组进行初始化（令其全部为'\0'）
    for(i = 0; i<n; i++)           // 从哈夫曼树静态链表的第一个字符开始建立编码表
    {
        k = N-3;
        (Code+i)->ch = (HT+i)->ch;   // 把对应的字符填入编码表中
        c = i;
        p = (HT+i)->parent;
        while((HT+c)->parent != -1)   // 从外节点开始往上回溯，直到根节点停止
        {
            temp[k] = ((HT+p)->lchild == c) ? '0' : '1';         // 若为左儿子，则置'0'，否则置'1'
            c = p; 
            p = (HT+c)->parent;
            k--;                      // 从后往前存储字符对应的编码
        }
        My_strcpy(temp, (Code+i)->bits, k+1);  // 将得到的编码复制给哈夫曼编码表
    }
}

// 对指定位置的字符串进行复制
void My_strcpy(char *ch, char *code, int i)
{
    for(;*(ch+i) != '\0'; i++)
    {
        *code = *(ch+i);
        *(ch+i) = '\0';        // 同时对ch字符数组重新置'\0'
        code++;
    }
    *code = '\0';
}

// 打印哈夫曼编码表
void Print_CharsetTable(Codenode *Code, int n)
{
    int i;
    printf("**哈夫曼编码表**\n");
    for(i = 0; i < n; i++)
    {
        printf("%-6c", (Code+i)->ch);
        puts((Code+i)->bits);
    }
}

// 对文本文件进行编码
void Encoding(Codenode *Code, int n)
{
    FILE *fp;
    char ch;
    int i;
    fp = freopen("Input.txt", "r", stdin);
    freopen("Huffman_encoding.txt", "w", stdout);
    while(!feof(fp))
    {
        ch = getchar();
        for(i = 0; i < n; i++)
        {
            if(ch == (Code+i)->ch)
            {
                printf("%s", (Code+i)->bits);
            }
        }
    }
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
}

// 对文本文件进行译码
void Decoding(HTnode *HT, int m)
{
    FILE *fp;
    char ch;
    int i = m-1;     // 令i为根节点的位置（根节点总在最后一位）
    fp = freopen("Huffman_encoding.txt", "r", stdin);
    freopen("Huffman_decoding.txt", "w", stdout);
    while(!feof(fp))
    {
        if ((HT + i)->lchild == -1 && (HT + i)->rchild == -1)
        {
            printf("%c", (HT + i)->ch);   // 若判断已经走到了外节点，则将对应的字符输出
            i = m - 1;                    // 同时将i重新置回根节点的位置
        }
        ch = getchar();
        if (ch == '0')              // 如果读入'0'，则走左支
        {
            i = (HT + i)->lchild;
        }
        else if(ch == '1')         // 如果读入'1'，则走右支
        {
            i = (HT + i)->rchild;
        }
    }
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
}

// 计算平均编码长度
void Count_AverageLength(HTnode *HT, Codenode *Code, int n)
{
    int i, j;
    float sum = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; *((Code+i)->bits+j)!='\0'; j++);
        sum += (HT+i)->weight * j;
    }
    printf("平均编码长度: %f\n", sum);
}

// 计算文件压缩率
void Count_Compressibility(void)
{
    FILE *fp;
    int i = -1, j = -1;
    float compress;
    fp = freopen("Input.txt", "r", stdin);
    while(!feof(fp))
    {
        getchar();
        i++;
    }
    fp = freopen("Huffman_encoding.txt", "r", stdin);
    while(!feof(fp))
    {
        getchar();
        j++;
    }
    compress = (float)j / (8*i);
    printf("文件压缩率: %f%%\n", compress*100);
    freopen("CON", "r", stdin);
}

// 把哈夫曼树和哈夫曼编码的信息存储到文件中
void WriteToFile(HTnode *HT, Codenode *Code, int total, int n)
{
    freopen("Tree&Table.txt", "w", stdout);
    printf("输入的总个数为: %d\n", total);
    printf("需要进行编码的个数为: %d\n\n", n);
    Print_HT(HT, 2*n-1);
    printf("\n");
    Print_CharsetTable(Code, n);
    printf("\n");
    Count_AverageLength(HT, Code, n);
    Count_Compressibility();
    freopen("CON", "w", stdout);
}