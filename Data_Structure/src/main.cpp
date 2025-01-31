
#include <iostream>
#include <cstring>
#include <List>

#include "../include/main.h"
// #include "../include/list.h"
using namespace std;

// 链表
namespace _List_test

{
    // 例如 存储 学生姓名,学号,成绩 单链表结构如下
    typedef struct student
    {
        string name;
        long num;
        int score;
    } ElemType;

    // 单链表的指针
    typedef struct Lnode
    {
        ElemType data;
        struct Lnode *next;
    } Lnode, *LinkList_ptr;
    // 双向链表的指针
    typedef struct DuLnode
    {
        ElemType data;
        struct DuLnode *next, *prior;
    } DuLnode, *DuLinkList_ptr;

    namespace _LindList_ // 单链表
    {

        // 运算符重载
        bool operator!=(const ElemType &th, const ElemType &data_b)
        {
            return th.name != data_b.name || th.num != data_b.num || th.score != data_b.score;
        }

        bool operator==(const ElemType &th, const ElemType &data_b)
        {
            return th.name == data_b.name && th.num == data_b.num && th.score == data_b.score;
        }
        istream &operator>>(istream &in, ElemType &data)
        {
            cin >> data.name >> data.num >> data.score; // 读取数据
            return in;
        }

        // 单链表的初始化 （带头节点的单链表）
        Status LinkList_L(LinkList_ptr &L)
        {
            // 1.生成新的结点作为头节点，用头指针L 指向头节点
            // 2. 将头节点的指针域置为空
            L = new Lnode; // 使用动态分配了一块Lnode大小的空内存
            L->next = nullptr;
            return OK;
        }

        // 判断连链表是否为空
        Status ListEmpty(LinkList_ptr L)
        {

            if (L->next)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }

        // 单链表的销毁，
        Status DestroyLIst(LinkList_ptr &L)
        {
            LinkList_ptr p;
            while (L)
            {
                p = L;       // 先记录 L头节点的位置
                L = L->next; // 获取下一个的指针域
                delete p;    // 然后释放原来位置
            }
            return OK;
        }

        // 清空单链表
        // 思路：依次释放所有节点，将头节点指针域设置为空
        Status ReviseList(LinkList_ptr &L)
        {
            LinkList_ptr P, Q;
            P = L->next;
            while (P) // 结束条件 P==null
            {

                Q = P->next;
                delete P;
                P = Q;
                Q = P->next;
            }
            L->next = nullptr;
            return OK;
        }

        // 求单链表的表长
        Status SizeList(LinkList_ptr L)
        {
            // 先有一个指针，当指针下移 则++ （同时进行判断是否为空）
            LinkList_ptr p;
            int index = 0; // 设置一个计数器
            p = L->next;   // 先获取首个节点 （因为这是一个带有头节点的单链表（不计入链表的长度））

            while (p)
            {
                /*
                进行判断p！=null  不是null 时进入循环,计数器加一，p指向下一个节点依次循环
            */
                index++;
                p = p->next;
            }
            return index;
        }
        /********************************************************************************************************* */
        // 查找元素(索引查找)
        Status FindList(LinkList_ptr L, int index, ElemType &e)
        {
            LinkList_ptr p;
            int j = 1;
            p = L->next;           // 首元节点
            while (p && j < index) // 先判断 p 是否为空 并且 满足 j< index
            {                      // 下移计数
                p = p->next;
                ++j;
            }
            if (!p || j > index) // p不为空但是 index的索引大于链表的长度
                return ERROR;
            e = p->data; // 找到了返回数据
            return OK;
        }

        // 按值查找（返回的是p指向linklist节点数据域)
        LinkList_ptr Find_data_List(LinkList_ptr L, ElemType datp)
        {
            LinkList_ptr p;
            p = L->next;
            while (p && p->data != datp) // p->data 相当于 this，而 datp 是作为参数传入的对象
                p = p->next;
            return p;
        }

        // 按值查找（返回的位置的下标)
        Status Find_index_List(LinkList_ptr L, ElemType datp)
        {
            LinkList_ptr p;
            p = L->next;
            int j = 1;
            while (p && p->data != datp)
            { // 存在两种情况  1 或 0
                p = p->next;
                j++;
            }
            if (p)
                return j;
            else
                return ERROR;
        }

        // 插入
        Status Insert_List(LinkList_ptr &L, ElemType datp, int index)
        {
            LinkList_ptr p;
            int j = 0;
            while (p && j < index - 1)
            {
                p = p->next;
                ++j;
            }
            if (!p || j > index - 1) // 判断位置非法
                return ERROR;

            // null-------》1（指针p）------(插入datp （指针S）)------》2----------》3
            LinkList_ptr s = new Lnode; // new 一块新的地址
            s->data = datp;             // 将新的数据域赋给 s->data
            s->next = p->next;          // 将现在   s.next=p.next 原来指向2的指针赋值给datp（的指针s）
            p->next = s;                // 在将s的地址赋值给1.next （p.next）
            return OK;
        }

        // 删除
        Status Delete_List(LinkList_ptr &L, int index) // 1  2  3  4   5
        {
            LinkList_ptr p, q; // 创建变量，存储前驱和后继
            int j = 0;
            p = L;
            while (p->next && j < index - 1) // 删除节点的前驱
            {                                // 判断p->next && j < index - 1  两个条件必须都要为真
                p = p->next;
                ++j;
            }
            if (!(p->next) || j > index - 1) // 判断 下一节点或者 j的下边是大于index的下标 则抛出异常
                return ERROR;
            q = p->next;             // 删除节点
            p->next = q->next->next; // 将上一节点的指针 指向  下一节点的下一个节点
            delete q;
            return OK;
        }

        // 头插法
        Status Head_Insert_List(LinkList_ptr &L, int index)
        {
            LinkList_ptr Q;    // 建立链表
            Q->next = nullptr; // 头节点的next为空
            for (int i = index; i > 0; --i)
            {
                LinkList_ptr p = new Lnode;
                cin >> p->data; // 当在这里在data中输入信息的时候，用到的（>> 运算符重载 ）
                p->next = Q->next;
                Q->next = p;
            }
            L = Q; // 将头节点返回给Q
            return OK;
        }

        // 尾差法     1    2       3      4         5   --->null
        Status Tail_Insert_List(LinkList_ptr &L, int index)
        {
            // 检查索引是否有效
            if (index < 0)
                return ERROR;

            LinkList_ptr K = L; // 尾指针，初始化为链表的头节点

            // 如果链表为空，初始化链表并输入第一个节点的数据
            if (!L)
            {
                L = new Lnode;     // 创建新节点
                cin >> L->data;    // 输入节点数据
                L->next = nullptr; // 新节点的下一个指针设为 nullptr
                return OK;         // 返回成功状态
            }

            // 找到链表的尾节点
            while (K->next)
            {
                K = K->next; // 移动指针到下一个节点
            }

            // 插入新节点
            for (int i = 0; i < index; i++)
            {
                LinkList_ptr Q = new Lnode; // 创建新节点
                cin >> Q->data;             // 输入新节点的数据
                Q->next = nullptr;          // 新节点的下一个指针设为 nullptr
                K->next = Q;                // 将尾节点的下一个指针指向新节点
                K = Q;                      // 更新尾指针 K 为新节点
            }

            return OK; // 返回成功状态
        }

    } // namespace 单链表

    namespace _CirculateList_ //  循环链表
    {
        // 带有尾指针的循环链表的合并
        LinkList_ptr &Connect(LinkList_ptr &Ta, LinkList_ptr &Tb) // 两个尾节点
        {
            LinkList_ptr p;            // 存放 Ta的头节点
            p = Ta->next;              // 获取Ta的头节点
            Ta->next = Tb->next->next; // 将Tb的头节点的地址赋值为Ta尾节点的下一个节点
            delete Tb->next;           // 释放Tb的空头结点（带有空头节点的链表）
            Tb->next = p;              // 将合并的尾节点 下一个节点赋为头节点 （尾头相连）
            return Tb;                 // 返回合并链表的尾节点
        }

    }

    namespace _DulindList_ // 双向链表
    {
        // 查找索引元素
        DuLinkList_ptr FindList(DuLinkList_ptr L, int index)
        {
            DuLinkList_ptr p;

            p = L->next;
            int j = 1;             // 首元节点
            while (p && j < index) // 先判断 p 是否为空 并且 满足 j< index
            {                      // 下移计数
                p = p->next;
                ++j;
            }
            if (!p || j > index) // p不为空但是 index的索引大于链表的长度
                return ERROR;

            return p;
        }
        // 插入元素

        Status Insert_List(DuLinkList_ptr &L, int index, ElemType e)
        {
            DuLinkList_ptr p;              // 定义当前节点
            if (!(p = FindList(L, index))) // 查找到当前索引链表的位置
                return ERROR;

            DuLinkList_ptr s;    // 插入的新元素节点
            s->data = e;         // 将数据传入 双链表节点 s中
            s->prior = p->prior; // 当前节点的上一个节点
            s = p->prior->next;  // 将上一个节点的下一个节点设置为 当前节点 S
            s->next = p;         // 将p 设置为 s的next
            p->prior = s;        // 将s设置为p的prior
            return OK;
        }
        // 根索引删除元素
        Status Delete_List(DuLinkList_ptr &L, int index, ElemType &e)
        {
            DuLinkList_ptr p;              // 查找到index节点
            if (!(p = FindList(L, index))) // 查找到当前索引链表的位置
                return ERROR;
            e = p->data;
            // 假设现在有链表  a<====>b<====>c  删除b
            //   b             c
            //   |            |
            p->prior->next = p->next;  // 将c的地址 给到a的next
            p->next->prior = p->prior; // 将a的节点给到c的piror
            delete p;
            return OK;
        }
    }
}
namespace _stack_test //!! 栈
{

    //!!  表尾是栈顶Top, 表头是栈底 Base
    //  插入元素到栈顶(表尾 ) 的操作 称为 入栈
    // 从 栈顶 （表尾） 删除最后一个元素的操作 称为 入栈
    typedef struct Stack_data
    {
    } SElemType;

    typedef struct _Stack
    {
        SElemType *Base;
        SElemType *Top;
        Status StackSize;

    } SqStack;

    typedef struct StackNode // 链栈
    {

        SElemType data;
        struct StackNode *next;
    } StackNode, *LinkdStack;

    Status
    InitStack(SqStack &S) // 初始化栈
    {

        S.Base = new SElemType[MAXSSIZE]; // 开辟内存
        if (!S.Base)
            exit(OVERFLOW);     // 判断  内存是否成功
        S.Top = S.Base;         // 栈顶 ==栈底  相当于 空栈
        S.StackSize = MAXSSIZE; // 长度
        return OK;
    }
    Status IfStack(SqStack S)
    { // 判断栈是否为空
        if (S.Top == S.Base)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    Status SizeStack(SqStack S)
    { // 求栈的长度
        return S.Top - S.Base;
    }
    Status EmptyStack(SqStack &S)
    { // 清空栈
        if (S.Base)
            S.Top = S.Base;
        return OK;
    }
    Status DelStack(SqStack &S) // 销毁栈
    {
        if (S.Base)
        {
            //!! 由于将栈回归内存中，栈存在栈底和栈顶   将栈底的base释放
            //!!  然后将其他的设置为 nullptr  和 0
            delete S.Base;
            S.StackSize = 0;
            S.Base = S.Top = nullptr;
        }
        return OK;
    }

    //!+++++++++++++++     重点         ++++++++++++++++
    Status Push(SqStack &S, SElemType e)
    {
        // 1.判断栈是否填满   2.元素e 入栈   3.栈顶指针加 1
        if ((S.Top - S.Base) == S.StackSize)
            return ERROR; // 栈满
        //!!  相当于*S.Top= e; S.top++;  因为 s.top 所指的是一片空间的地址，
        *S.Top++ = e;
        return OK;
    }

    Status Pop(SqStack &S, SElemType &e) // 出栈
    {
        if (IfStack(S))
            return ERROR;

        e = *--S.Top; // 先--  在给 *s.top 的值赋给 e
        return OK;
    }

    namespace _LinkdStack_ // 链栈
    {
        Status InitLinkdStack(LinkdStack &S) // 初始化
        {
            S = nullptr;
            return OK;
        }

        Status IfLinkdStack(LinkdStack S) // 判断是否为空
        {
            if (S == nullptr)
                return TRUE;
            else
                return FALSE;
        }
        Status PushLinkdStack(LinkdStack &S, SElemType e) // 入栈
        {
            LinkdStack p;
            p->data = e;
            p->next = S;
            S = p;
            return OK;
        }

        Status PopLinkdstack(LinkdStack &S) // 出栈
        {
            if (S == nullptr)
                return ERROR;
            LinkdStack P;
            P = S;
            S = S->next;
            delete P;
            return OK;
        }

        SElemType GetTop(LinkdStack S) // 获取栈顶元素
        {
            if (S != nullptr)
                return S->data; //  这里警告的原因是  在SElemType 中什么也为定义
        }

    } // namespace LinkdStack

}

namespace _queue_test //!! 队列
{
    typedef struct Queue_data
    {
    } Queue_data;

    typedef struct
    {
        Queue_data *base; // 初始化动态分配空间
        int front;        // 头
        int rear;         //! 尾  指向数据的下一个内存
    } SqQueue;

    // typedef struct // 定义链队
    // {
    // } LinkdQueue;
    // typedef struct Qnode // 链队的结构定义
    // {
    //     LinkdQueue data;
    //     Qnode *next;
    // } Qnode, *Queue_ptr;
    // typedef struct
    //{
    //     LinkdQueue front;
    //     LinkdQueue rear;
    // } LinkQueue_ptr;

    Status initQueue(SqQueue &Q) // 初始化 队列
    {
        Q.base = new Queue_data[MAXQSIZE];
        if (!Q.base)
            exit(OVERFLOW);
        Q.front = Q.rear = 0;
        return OK;
    }
    Status QueueLength(SqQueue Q) // 求长度 （包含循环队列）
    {
        /*
         !! 需要判断循环链表 rear 和feont 存在负数问题
         !! 现在假设循环链表 头为  0  尾为 5   maxqsize 为 10

         Q.rear - Q.front  为 -5       加上maxQsize  最后的值为  5 最后在对  MAXQSZIE 取余 为 5
         相当于先计算了头和为的差值 加上了总长度， 总长度 - 空元素 = 存志的长度（肯定是不为零 ）
         最后在取于 避免了 头比尾大 最后最后相加 大于总长度
        */

        return ((Q.rear - Q.front + MAXQSIZE) % MAXQSIZE);
    }

    Status PushQueue(SqQueue &Q, Queue_data &e) // 入队
    {
        // 判断队列是否队满
        if ((Q.rear + 1) % MAXQSIZE == Q.front) //!! 因为在队列中有一个 空值 作为缓冲以防溢出越界
            return ERROR;
        Q.base[Q.rear] = e;               //!! 在以开辟内存的数据中 找到下标为Q.rear的内存空间 存放 e这个值
        Q.rear = (Q.rear + 1) % MAXQSIZE; //  最后更新 rear（尾指针的）的指向
        return OK;
    }
    Status delQueue(SqQueue &Q, Queue_data &e)
    {
        if (Q.front == Q.rear) // 头和尾不能相等
            return ERROR;
        e = Q.base[Q.front];                // 通过数组去访问到队列的头
        Q.front = (Q.front + 1) % MAXQSIZE; // 在将头指针+1
        return OK;
    }
    Status GetQueue(SqQueue Q, Queue_data &e) // 获取头
    {
        if (Q.front != Q.rear) // 头和尾不能相等
            return ERROR;
        e = Q.base[Q.front];
        return OK;
    }

    // namespace _LinkdQueue // 链队
    // {

    //     Status InitLinkdQueue(LinkQueue_ptr &QL)
    //     {
    //         QL.front = new Qnode;
    //     }

    // }
}

int main()
{
    
    cin.get();
    return 0;
}
namespace demo
{ // 递归调用
    int _fact(int n)
    {
        if (n == 0)
            return 0;
        else
            return n * _fact(n - 1);
    }

} // namespace demo
