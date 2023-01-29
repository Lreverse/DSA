#include<stdio.h>
#include<stdlib.h>
#define N 50
typedef struct BTnode    // 该二叉树用来存储字符序列
{
    char data;
    struct BTnode *lchild;
    struct BTnode *rchild;
} BTnode;
typedef struct stack
{
    int top;
    BTnode *pt[N];
} stack;
typedef struct Node      // 队列的节点
{
    BTnode *pt;
    struct Node *next;
} Node;
typedef struct queue
{
    Node *front;
    Node *rear;
} queue;
void MakeNull_S(stack *s);
int  Empty_S(stack *s);
BTnode* Top(stack *s);
void Pop(stack *s);
void Push(BTnode *BT, stack *s);
void MakeNull_Q(queue *Q);
int  Empty_Q(queue *Q);
BTnode* Front(queue *Q);
void EnQueue(BTnode *BT, queue *Q);
void DeQueue(queue *Q);
BTnode* PreCreateBT();
void Print(BTnode *BT);
void PreOrder(BTnode *BT);
void InOrder(BTnode *BT);
void PostOrder(BTnode *BT);
void NPreOrder(BTnode *BT);
void NInOrder(BTnode *BT);
void NPostOrder(BTnode *BT);
void LevelOrder(BTnode *BT);
int  IsCompleteBT(BTnode *BT);
int  MaxLevel(BTnode *BT);
int  Length_Q(queue *Q);
int main(void)
{
    BTnode *BT = NULL;
    printf("请输入二叉树的扩展先根序列:\n");
    BT = PreCreateBT();
    printf("\n**递归算法**");
    printf("\n先根遍历:\n");
    PreOrder(BT);
    printf("\n中根遍历\n");
    InOrder(BT);
    printf("\n后根遍历\n");
    PostOrder(BT);
    printf("\n\n**非递归算法**");
    printf("\n先根遍历:\n");
    NPreOrder(BT);
    printf("\n中根遍历:\n");
    NInOrder(BT);
    printf("\n后根遍历\n");
    NPostOrder(BT);
    printf("\n\n层序遍历\n");
    LevelOrder(BT);
    printf("\n\n该二叉树是否为完全二叉树: ");
    if(IsCompleteBT(BT))
        printf("是\n");
    else
        printf("不是\n");
    printf("\n该二叉树的宽度为: ");
    printf("%d", MaxLevel(BT));
    printf("\n");
    return 0;
}

// 置空栈
void MakeNull_S(stack *s)
{
    s->top = N;
}

// 判断栈是否为空
int  Empty_S(stack *s)
{
    if(s->top >= N)
        return 1;
    else
        return 0;
}

// 返回栈顶元素
BTnode* Top(stack *s)
{
    if(Empty_S(s))
        return NULL;
    else
        return s->pt[s->top];
}

// 入栈
void Push(BTnode *BT, stack *s)
{
    if(s->top == 0)
    {
        printf("栈已满！\n");
    }
    else
    {
        s->top--;
        s->pt[s->top] = BT;
    }
}

// 出栈
void Pop(stack *s)
{
    if(Empty_S(s))
    {
        printf("栈为空！\n");
    }
    else
    {
        s->top++;
    }
}



// 置空队列
void MakeNull_Q(queue *Q)
{
    Node *p = NULL;
    p = (Node*)malloc(sizeof(Node));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    Q->front = p;
    p->next = NULL;
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
BTnode* Front(queue *Q)
{
    if(Empty_Q(Q))
    {
        printf("队列为空！\n");
        return NULL;
    }
    else
    {
        return Q->front->next->pt;
    }
}

// 入队（队尾）
void EnQueue(BTnode *BT, queue *Q)
{
    Node *p = NULL;
    p = (Node*)malloc(sizeof(Node));
    if(p == NULL)
    {
        printf("没有足够的空间分配内存！\n");
        exit(0);
    }
    Q->rear->next = p;
    p->pt = BT;
    p->next = NULL;
    Q->rear = p;
}

// 出队（队首）
void DeQueue(queue *Q)
{
    Node *temp = NULL;
    if(Empty_Q(Q))
    {
        printf("队列为空！\n");
    }
    else
    {
        temp = Q->front->next;
        Q->front->next = temp->next;
        free(temp);
        if(Q->front->next == NULL)
        {
            Q->rear = Q->front;
        }
    }
}



// 采用扩展先根序列存储二叉树（递归）
BTnode* PreCreateBT()
{
    BTnode *p = NULL;
    char ch;
    ch = getchar();
    if (ch == '#' || ch == '\n')       // 记得标记输入结束时的状态（'\n'代表输入结束）
    {
        p = NULL;
    }
    else
    {
        p = (BTnode *)malloc(sizeof(BTnode));
        if (p == NULL)
        {
            printf("没有足够的空间分配内存！\n");
            exit(0);
        }
        p->data = ch;
        p->lchild = PreCreateBT();
        p->rchild = PreCreateBT();
    }
    return p;
}

// 打印二叉数
void Print(BTnode *BT)
{
    
}

// 先根遍历（递归）
void PreOrder(BTnode *BT)
{
    if(BT != NULL)
    {
        printf("%c ", BT->data);
        PreOrder(BT->lchild);
        PreOrder(BT->rchild);
    }
}

// 中根遍历（递归）
void InOrder(BTnode *BT)
{
    if(BT != NULL)
    {
        InOrder(BT->lchild);
        printf("%c ", BT->data);
        InOrder(BT->rchild);
    }
}

// 后根遍历（递归）
void PostOrder(BTnode *BT)
{
    if(BT != NULL)
    {
        PostOrder(BT->lchild);
        PostOrder(BT->rchild);
        printf("%c ", BT->data);
    }
}

// 先根遍历（非递归）
void NPreOrder(BTnode *BT)
{
    stack s;
    MakeNull_S(&s);
    while(!Empty_S(&s) || BT != NULL)     // 以栈为空且指针BT也为空为结束标志
    {
        if(BT != NULL)
        {
            printf("%c ", BT->data);
            Push(BT, &s);
            BT = BT->lchild;            // 将BT移动到最左边
        }
        else
        {
            BT = Top(&s);
            Pop(&s);
            BT = BT->rchild;
        }
    }
}

// 中跟遍历（非递归）
void NInOrder(BTnode *BT)
{
    stack s;
    MakeNull_S(&s);
    while(!Empty_S(&s) || BT!=NULL)
    {
        if(BT!=NULL)
        {
            Push(BT, &s);
            BT = BT->lchild;
        }
        else
        {
            BT = Top(&s);
            Pop(&s);
            printf("%c ", BT->data);
            BT = BT->rchild;
        }
    }
}

// 后根遍历（非递归）
void NPostOrder(BTnode *BT)
{
    int reg = 1;
    stack s;
    BTnode *temp;
    MakeNull_S(&s);
    while(!Empty_S(&s) || BT != NULL)
    {
        if(BT != NULL)
        {
            Push(BT, &s);
            BT = BT->lchild;
        }
        else
        {
            BT = Top(&s);
            if(BT->rchild != NULL && BT->rchild != temp)   // 若是从右子树返回，则刚访问的节点就是右子树的根节点，于是不会再进入右子树的遍历
            {
                BT = BT->rchild;
            }
            else
            {
                Pop(&s);
                printf("%c ", BT->data);
                temp = BT;                  // 记录刚刚访问过的节点
                BT = NULL;
            }
        }
        
    }
}

// 层序遍历
void LevelOrder(BTnode *BT)
{
    queue Q;
    MakeNull_Q(&Q);
    if(BT != NULL)
    {
        EnQueue(BT, &Q);
    }
    while(!Empty_Q(&Q))
    {
        BT = Front(&Q);
        printf("%c ", BT->data);
        DeQueue(&Q);
        if(BT->lchild != NULL)
        {
            EnQueue(BT->lchild, &Q);
        }
        if(BT->rchild != NULL)
        {
            EnQueue(BT->rchild, &Q);
        }
    }
}

// 判断二叉树是否为完全二叉树
int  IsCompleteBT(BTnode *BT)
{
    queue Q;
    int ltag, rtag, flag = 0;
    MakeNull_Q(&Q);
    if(BT != NULL)
    {
        EnQueue(BT, &Q);
    }
    while(!Empty_Q(&Q))
    {
        ltag = 0;
        rtag = 0;
        BT = Front(&Q);
        DeQueue(&Q);
        if(BT->lchild != NULL)
        {
            EnQueue(BT->lchild, &Q);
            ltag = 1;
        }
        if(BT->rchild != NULL)
        {
            EnQueue(BT->rchild, &Q);
            rtag = 1;
        }
        if ((flag == 1) && (ltag == 1 || rtag == 1))
        {
            return 0;                     // 判断后续节点是不是叶节点，若不是，则不是完全二叉树，直接返回0
        }
        if (ltag == 0 && rtag == 1)       // 若左子树为空，右子树不为空，则一定不是完全二叉树
        {
            return 0;
        }
        else if((ltag == 0 && rtag == 0) || (ltag == 1 && rtag == 0))
        {
            flag = 1;                     // 若是‘叶节点’或‘左子树不为空，但右子树为空的节点’，则其后续节点都应该为叶节点
        }
    }
    return 1;
}

// 计算队列的长度
int  Length_Q(queue *Q)
{
    Node *pr = Q->front->next;
    int i = 0;
    while(pr!= NULL)
    {
        pr = pr->next;
        i++;
    }
    return i;
}

// 计算二叉树的宽度
int  MaxLevel(BTnode *BT)
{
    int len=1, max = 1;
    queue Q;
    MakeNull_Q(&Q);
    if(BT == NULL)
        return 0;
    else
        EnQueue(BT, &Q);
    while (len != 0)
    {
        while (len > 0)        // 将上一层的节点出队（长度已经知道），同时也将该层的节点入队
        {
            BT = Front(&Q);
            DeQueue(&Q);       // 将上一层的节点都出队后，剩下的就只有该层节点，于是就能进到下一次循环，从而求出该层长度
            if (BT->lchild != NULL)
                EnQueue(BT->lchild, &Q);
            if (BT->rchild != NULL)
                EnQueue(BT->rchild, &Q);
            len--;
        }
        len = Length_Q(&Q);    // 记录每一层的长度
        max = max>len ? max : len;     // 每求出一层的宽度，就与最大值作比较
    }
    return max;
}