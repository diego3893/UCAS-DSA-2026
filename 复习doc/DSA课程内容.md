# DSA课程内容doc

- 以代码和相关操作为导向，涵盖了一些个人认为重要的知识点
- 包含某些对出题方向和考点的推测
- 对每一种结构的操作步骤：
  1. 合法性检查（越界、判空、溢出等）
  1. 申请内存，用另一个指针先申请`realloc`，确认申请成功后再重定向
  1. 执行操作
  1. 维护外围特性，比如`size`，`head/tail`
  1. 释放内存，free掉没有用的空间
  1. 返回结果（`Status`或者具体的数据）


-------------

## 0 绪论

- 逻辑结构：
  1. 集合
  2. 线性结构：一对一
  3. 树型结构：一对多
  4. 图状结构：多对多
- 两种存储结构：顺序、链式
- 算法：有穷性、确定性、可行性、输入、输出
- 算法设计思路：暴力、分治、dp、贪心
- 算法评价标准：正确性、可读性、健壮性（鲁棒性）、高效低存储量
- 大O记号算复杂度：$O(1)<O(\log n)<O(n)<O(n\log n)<O(n^2)<O(2^n)<O(n!)<O(n^n)$
  - 找循环嵌套最深的那一句，计算它的执行频次，用大O记号表示

- 主定理：对于一个规模为$n$的问题，通过分治将每个问题分解成$a$个规模为$\frac{n}{b}$的子问题，每次递归带来的额外运算为$f(n^d)$，那么可得到它的时间复杂度关系式：$T(n)=aT(\frac{n}{b})+f(n^d)$
  - 若$\log_ba<d$，$T(n)=O(n^d)$
  - 若$\log_ba>d$，$T(n)=O(n^{\log_ba})$
  - 若$\log_ba=d$，$T(n)=O(n^d\log_bn)$，也可以写成$$T(n)=O(n^d\log n)$

- 最好情况、最坏情况、平均复杂度
  - 快排：固定pivot时，最坏为$O(n^2)$，递归树退化为链；平均为$O(n\log n)$
  - 二叉搜索树BST：最坏为$O(n)$，树退化为链；平均为$O(\log n)$
    - 这就是为什么都用平衡树/红黑树

  - 哈希查找：最坏$O(n)$，极端哈希冲突导致；平均$O(1)$


## 1 线性表

- **唯一**头，**唯一**尾，**唯一**直接前驱，**唯一**直接后继

  - 顺序表就是手写数组，很简单的原理
  - 数组、链表，本章的重点是多种的链表的多种实现
  - 单链表、双向链表、循环链表、静态链表

- 重中之重：内存分配以及迭代

  - 内存分配：`Node *p = (Node*)malloc(sizeof(Node));`
  - 迭代：`p = p->next`

### 1.0 顺序表

- 建表时直接`malloc`申请一块连续内存即可

- 在位置i插入元素时，把其后的所有元素向后挪一格

```c
typedef struct{
    int *elem;
    int listsize;
    int length;
}SqList;
// 实例化L并初始化
int *p, *q;
q = &(L->elem[i-1]);
for(p = &(L->elem[L->length-1]); p>=q; --p){
	*(p+1) = *p;
}
*q = e;
L->length++;
```

- 删除元素同理，将第i个位置之后的元素全部左移一个

```c
p = &(L->elem[i-1]);
*e = *p;
q = L->elem+L->length-1;
for(++p; p<=q; ++p){
	*(p-1) = *p;
}
L->length--;
```

### 1.1 单链表

- 初始化：有无头结点

- 建表

  - 双指针法

  - ```c
    typedef struct Node{
        int data;
        struct Node *next;
    }Node;
    Node *head = (Node*)malloc(sizeof(Node));
    head->next = NULL; // 建立头结点
    Node *p, *q;
    q = head;
    while(read new data){
    	p = (Node*)malloc(sizeof(Node));
        p->data = data;
        p->next = NULL;
        q->next = p;
        q = p;
    }
    ```

- 销毁：删除整张表

  - 严格的来讲，需要从头节点开始，用双指针法删除整张表

- 插入

  - 修改插入位置直接前驱的指针为p，p的指针为**直接前驱的直接后继**

  - ```c
    // q为插入位置的直接前驱
    p->next = q->next;
    q->next = p;
    ```

  - 注意顺序，原因很显然

- 遍历表

  - ```c
    p = head->next; // 指向第一个存数据的节点
    while(p){
    	// do something here
        
        p = p->next;
    }
    ```

- 查找、取值

  - 遍历表，加一个data判断

- 删除特定节点

  - 查找+`free()`

  - ```c
    // code here
    // 已经找到目标节点p，p的前驱存在q
    q->next = p->next;
    free(p);
    ```

- 求表长

  - 遍历表，`data_cnt++`

- 修改节点值

  - 查找节点，直接改
  
- 原地置逆

  - 原地：不创建新的链表
  - 三指针法
    - 为什么要三个指针？A：单链表只维护后继关系，需要`*pre`存前驱；要修改当前节点，需要`*cur`存当前节点；要修改后继关系，避免断链，`*next`存后继


  ```c
  Node *pre, *cur, *next;
  pre = NULL;
  cur = head->next;
  while(cur){
  	next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
  }
  head->next = pre;
  ```
- 如何改进？
  - 加入表长`length`，$O(1)$进行插入位置合法性检查
  - 加表尾指针，$O(1)$进行表尾插入，不用遍历
  - 维护一个`curpos`指针，将绝对位置`i`变为相对位置，不用重复多次遍历
  - 典型的时间换空间
### 1.2 双向链表

- 顾名思义，直接前驱和直接后继都要存

  - ```c
    typedef struct Node{
        int data;
        struct Node *prior; // 前驱
        struct Node *next; // 后继
    }Node;
    ```

- 需要的操作和单链表差不多，只是需要注意每次要修改两个指针

  - 建表：

    - ```c
      Node *head = (Node*)malloc(sizeof(Node));
      head->next = NULL;
      Node *p, *q;
      q = head;
      while(read new data){
      	p = (Node*)malloc(sizeof(Node));
          p->data = data;
          p->next = NULL;
          p->prior = q;
          q->next = p;
          q = p;
      }
      ```

  - 插入：

    - ```c
      // 遍历操作完全一致，用不上前驱
      // 现在已经找到要插入的位置，q为插入位置的前驱，p指向待插入的节点
      p->next = q->next;
      p->prior = q;
      q->next = p;
      p->next->prior = p;
      ```

  - 删除：

    - ```c
      // p为删除节点，q为p的前驱
      q->next = p->next;
      p->next->prior = q;
      free(p);
      ```

### 1.3 循环链表

- 首尾相接就是循环链表

  - ```c
    // p 为尾节点
    p->next = head;
    ```

### 1.4 静态链表

- 因为不用动态申请内存，所以是静态的（废话）
- 从头部插入数据！不是尾部
- 看起来很麻烦，实际也不简单
  - 模拟邻接表（前向星）会用静态链表
- 用数组模拟链表的操作
  - 下面这段代码只是一个示例，用来理解next数组的作用
  - next[0]不存数据，用来维护一个“空闲节点”的链表
- 建表

```c
int data[105];
int next[105]; // next[i]为data[i]的后继下标
int head[105]; // head[i]存第i张表的表头下标
int head_idx = 1;
// 初始化，next[0]用来维护空闲节点
for(int i=0; i<100; ++i){
    next[i] = i+1;
}
next[100] = 0;
// 建立新表
// 对于第k张表
if(next[0]){
    head[head_idx] = next[0];
    next[0] = next[next[0]];
    next[head[head_idx]] = 0;
    head_idx++;
}
while(read new_data){
    int av_idx = -1;
	if(next[0]){
        av_idx = next[0];
        next[0] = next[next[0]];
	}
    if(av_idx != -1){
        data[av_idx] = new_data;
        next[av_idx] = next[head[k]];
		next[head[k]] = av_idx;
    }
}
```
- 删除节点
```c
int idx = next[head[k]];
int pre = head[k];
while(data[idx]!=target_data && idx!=0){
    pre = idx;
	idx = next[idx];
}
if(idx){
    next[pre] = next[idx];
	next[idx] = next[0]; // 回收
	next[0] = idx;
}
```
- 其他操作和单链表同理
------------

## 2 栈和队列

### 2.0 栈

- FILO，先进后出
- 操作受限的线性表

#### 2.0.0 动态栈 && 静态栈

- 本质是一个动态一维数组，维护一个不动的栈底指针`*base`和一个随时被修改的栈顶指针`top`

```c
typedef struct{
    int top;
    int *base;
    int stack_size;
}Stack;
Stack s;
s->base = (int*)malloc(StackSize*sizeof(int));
s->top = 0;
s->stack_size = StackSize; // Init
// push，需要判定栈是否满，即比较top和size
s->base[s->top++] = data;
// top
int e = s->base[s->top];
// pop，需要判栈是否空
s->top--;
```

- 静态栈就是直接申请一个数组来维护栈，即栈大小不可变

#### 2.0.1 链式栈

- 单链表+一个栈顶指针，链表的头结点就是栈底

#### 2.0.2 栈的应用

- DFS、递归

![](C:\Users\30130\Desktop\workstation\DSA\复习doc\运算符优先级表.jpg)

- 表达式求值、转换：前缀表达式、中缀表达式、后缀表达式
  - 后缀求值
    - 一个栈，装操作数
    - 每次读到符号，弹两个操作数（op2，op1），求值再压栈，最后栈中的唯一一个数就是值
  - 前缀求值
    - 一个栈，装操作数
    - 逆向读入，每次读到符号，弹两个操作数（op1，op2），求值再压栈，最后栈中的唯一一个数就是值
  - 中缀求值
    - 两个栈，符号栈`optr`，操作数栈`opnd`；维护一个表示运算符优先级的表
    - 读到符号，和`optr`栈顶符号比较优先级，当前优先级低或者相等，计算并压操作数栈，直到当前符号可以压栈
  - 三者转换
    - 通法：转成中缀表达式建一颗表达式树，然后三种遍历出三种表达式
  - 中缀->后缀
    - 维护一个表示运算符优先级的表，包括`+-*/()#`
    - 遇到数直接输出
    - 遇到符号，和符号栈顶的比较优先级，当前优先级低或者相等则已知弹栈，直到当前符号可以压栈
  - 中缀->前缀
    - 维护一个表示运算符优先级的表，包括`+-*/()#`
    - 遇到数直接输出
    - 反转中缀表达式$A-B*(C-D) \to (D-C)*B-A$，按照中缀转后缀的办法处理，但是在**优先级严格小于**的时候才弹栈
      - 因为反转，让结合律反转了，所以相等时不用弹出，而是压栈，这才符合新的结合律
    - 最终输出表达式再次反转，就是前缀表达式
  - 前后缀->中缀
    - 后缀从左向右扫描，前缀从右向左扫描
    - 后缀每次弹操作数是op2，op1；前缀是op1，op2
    - 每次读到操作符，弹出两个操作数，合并为一个`op1 sym op2`，压栈
    - 括号处理
      - 维护一个上一步处理的符号`pre_sym`，即每个操作数变为`{string exp; char pre_sym;}`
      - 比较操作数符号和当前符号的优先级
        - 当前优先级更高：操作数中优先级低的部分加括号，再拼接
          - $AB-CD-*\to (A-B)*(C-D)$
        - 当前优先级低：直接拼接
        - 优先级相等：如果当前符号是`-`或者`/`，则`op2`加括号，拼接
- 递归中汉诺塔时间复杂度：
  - Z柱过渡，X上的(n-1)个盘子移到Y；X的最后一个盘子挪到Z；X过渡，Y的(n-1)个盘子挪到Z
  - $f(n)=2*f(n-1)+1$，$f(1)=1$，$f(n)=2^{n-1}+const$
  - $T(n)=O(2^n)$
- 递归与非递归写法的转换
  - 手动用栈模拟函数的调用过程，可以将任何递归改写成非递归
  - 对于尾递归和单向递归，可以用循环结构替代
  - 用栈、数组等存储中间数据，从而用非递归结构代替递归
    - 斐波拉契、阶乘、树的三种遍历的栈写法等等

### 2.1 队列

- FIFO，先进先出，维护队首和队尾
- 操作受限的线性表

#### 2.1.0 链式队列

- 单链表+队首队尾双指针，队首就是链表的头结点，每次出队即删除`head->next`
- 如何判空？队首队尾都指向`head`

#### 2.1.1 顺序队列和循环队列

- 静态队列：数组+head+tail，简单地实现
- 假溢出：因为出队后无法释放空间，整个队列相对数组一直在向后偏移，会浪费很多`head`之前的空间
- 循环队列：将head和tail都对`QUEUESIZE`取模，将整个数组看成一个圆环
  - 如何判空判满？
    - `(head%QUEUESIZE)==(tail%QUEUESIZE)`在空和满是都成立
  - 维护一个`cnt`，辅助判断
  - 增加一个标志位，区分空和满
  - 少用一个元素，即`(head%QUEUESIZE)==(tail%QUEUESIZE)`为空，而`(head%QUEUESIZE)==(tail%QUEUESIZE)+1`为满，则队首的前一个空间不会被使用

#### 2.1.2 队列的应用

- 杨辉三角

  - 队列存上一行的值，末尾手动加0表示结束
  - 维护两个`cur_i`和`cur_i_1`，分别存当前出现的相邻两个数，相加获得下一行的数
  - 需要计算第k行的杨辉三角，队列要多长？
    - 第k行有k+1个数，加上手动添加的0，总共`k+2`长度

  ```c
  // 初始入队1,1
  int cur_i = 0, cur_i_1 = 0;
  for(int r=1; r<total_r; ++r){
  	q.push(0);
      for(int c=1; c<=r+2; ++c){ // 输出当前行，计算下一行
          int e = q.front();
          cur_i = e;
          q.pop();
          if(e){
              printf("%d", cur_i);
  		}
          next_row_i = cur_i+cur_i_1;
          q.push(next_row_i);
          cur_i_1 = cur_row_i; // 迭代
      }
      printf("\n");
  }
  // 单独输出队列中存的最后一行值
  ```

- BFS

- 集合划分（这部分示例代码是自己写的，不保证没有错误）

  - 保证队列内部有序（升序），便于判断是否遍历完成一轮
  - `confict[n][n]`维护冲突关系，`res[n]`存分组编号
  - 引入`clash[n]`维护当前组别的冲突关系，减少对`conflict`的重复查看

  ```c++
  int k = 1;
  int conflict[n][n]; // 冲突关系
  int clash[n];
  memset(clash, 0, sizeof(clash));
  int res[n];
  queue<int> q;
  for(int i=0; i<n; ++i){
      q.push(i);
  }
  while(!q.empty()){
      int cur = q.front();
      q.pop();
  	if(!clash[cur]){
          res[cur] = k;
          for(int i=0; i<n; ++i){
              clash[i] += conflict[cur][i];
  		}
  	}else{
          q.push(cur);
  	}
      if(!q.empty() && cur>=q.front()){ // 新的一轮
          k++;
          memset(clash, 0, sizeof(clash));
  	}
  }
  ```

-----------

## 3 串

- 数据全是字符的线性表，隐含结束符`\0`
- 串、子串、平凡子串vs真子串

### 3.0 串的存储

#### 3.0.0 顺序串、定长顺序存储

- `typedef unsigned char SString[MAXLEN+1]`，`MAXLEN`一般取255，因为`s[0]`存串长，而无符号字符只能表示`0~255`
- 串匹配的暴力算法：每次失配时，都把模式串的指针回退到初始位置
  - 最坏复杂度：$m*(n-m+1)=O(nm)$

#### 3.0.1 顺序串、堆分配存储

```c
typedef struct{
	char *ch;
    int strsize;
    int length;
}HString;
HString s;
s->ch = (char*)malloc(STRLEN*sizeof(char)); // malloc分配的内存在堆区
s->ch[0] = '\0';
s->length = 0;
s->strsize = STRLEN;
```

- 显然可以类似地进行复制、比较、拼接等操作
- 堆区串长超出限制时，使用`(char*)realloc(s->ch, (size+1)*sizeof(char))`重新分配，注意重新设置`s->strsize`
- 注意显式地、手动在串的末尾加上`\0`
- e.g. 子串替换

```c
void StrRepSubstr(HString *s,HString *t,HString *v){
    int n,m,pos,i;
    HString newStr,sub;
    StrInit(&newStr);
    StrInit(&sub);
    n=StrLen(s);
    m=StrLen(t);
    pos=1; 
    i=1;
    while(pos<=n-m+1 && i){
        i=StrIndex(s,t,pos); // 匹配
        if(i != 0){
            StrSubstr(&sub,s,pos,i-pos); //sub存匹配串之前的那一段不用修改的子串
            StrConcat(&newStr,&newStr,&sub);
            StrConcat(&newStr,&newStr,v); // 拼接上 置换串
            pos=i+m; // 这m个字符被替换，跳过
        }
    }
    if(StrSubstr(&sub,s,pos,n-pos+1)){
        StrConcat(s,&newStr,&sub); // 处理尾巴上的子串
    }else{
        StrCopy(s,&newStr);
    }
    return; 
}
```

#### 3.0.2 块链存储

```c
typedef struct Chunk{
	char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;
typedef struct{
    Chunk *head;
    Chunk *tail;
    int curlen;
}LString;
```

- 本质就是一个分块存储的单链表

### 3.1 模式串匹配

- 暴力匹配

  - 每次失配都把模式串指针回退到开头，并且把主串指针回退到**本次匹配开头的下一个位置**

- KMP

  - 维护一个`next`数组，存储当前最长公共前后缀的长度
  - 由于是最长公共前后缀
    - 失配时模式串指针回退至`next[i]`即可
    - 主串指针不需要回退，持续向右滑动
  - $next[j] = 
    \begin{cases} 
    -1, & j=0 \\ 
    k,0<k<j, & 使得p_0p_1...p_{k-1}=p_{j-k}p_{j-k+1}...p_{j-1}的最大整数\\ 0, & Others 
    \end{cases}$

  - 人话：`next[0]=-1`表示串到头了，没法往前移了，是放弃**向前挪指针**的标志，意味着无论如何都需要继续在主串向后匹配；`next[j]=k`表示在$0\sim j-1$区间中的最长公共前后缀长度

  - KMP主体的思路显而易见了：如果模式串和主串匹配，二者指针同时向前；失配时，按照`next`不停回退模式串指针，直到可以匹配或者`next=-1`；如果模式串完成匹配，返回匹配位置
    - 复杂度$O(n)$
    - $k=2i-j$严格递增，最多为$k=2n$，所以是$O(n)$

  ```c
  int KMP(HString *s, HString *t, int pos){
      int next[STRLEN];
      get_next(t, next);
      i = pos-1;
      j = 0;
      while(i<s->length && j<t->length){
          if(j==-1 || s->ch[i]==t->ch[j]){
              i++;
              j++;
          }else{
              j = next[j]; // 失配，回退
          }
  	}
      if(j >= t->length){
          return i-t->length+1;
  	}else{
          return 0;
      }
  }
  ```

  - 如何获得`next`？模式串**自匹配**的过程

  ```c
  void get_next(HString *pattern, int next[]){
      int j = 0, k = -1; // j是子串指针（等效于kmp的i），k是自匹配指针（kmp的j）
      next[0] = -1;
      while(j < pattern->length){
          if(k==-1 || pattern->ch[j]==pattern->ch[k]){
              j++, k++;
              next[j] = k;
          }else{
              k = next[k];
          }
      }
  }
  ```

  - `next`优化为`nextval`，*路径压缩*的写法
    - 答题时不要写**路径压缩**四个字！这是并查集里面的术语，用在这里只是因为二者思路相近
    - 为什么类似于**路径压缩**？
    - 当失配时，我们要回退到`next[j]`，而如果此时的`next[j]`位置的字符和回退前一样，意味着我们还需要再次回退
    - `nextval[j]=nextval[k]`将这若干步无效的回退压缩到一步中
    
  
  ```c
  void get_next(HString *pattern, int nextval[]){
      int j = 0, k = -1;
      nextval[0] = -1;
      while(j < pattern->length){
          if(k==-1 || pattern->ch[j]==pattern->ch[k]){
              j++, k++;
              if(pattern->ch[j] == pattern->ch[k]){
                  nextval[j] = nextval[k];
              }else{
                  nextval[j] = k;
              }
          }else{
              k = nextval[k];
          }
      }
  }
  ```

------------------

## 4 数组和广义表

### 4.0 数组

- 顺序存储，随机访问，**不是线性表**，因为可以有未赋值的元素
- 二维以上数组不是线性结构，因为有多个直接前驱和后继

#### 4.0.0 多维数组

- 从下标到存储位置映射：

  - 一维数组：`arr[k]`的存储位置为$arr[0]+k*L$，L为每个元素的长度
  - 二维数组：一般取**行主序**，定义`arr[n][n]`，`arr[i][j]`存在$arr[0][0]+(i*n+j)*L$
  - 三维：`arr[i][j][k]`在$arr[0][0][0]+(i*n*n+j*n+k)*L$
  - n维：$LOC(j_1,j_2,...,j_n)\\=LOC(0,0,0)+(b_2\times ...\times b_n\times j_1+b_3\times ...b_n\times j_2+...b_n\times j_{n-1}+j_n)L\\=LOC(0,0,0)+(\Sigma_{i=1}^{n-1}j_i\prod_{k=i+1}^nb_k+j_n)L\\=LOC(0,0,0)+\Sigma_{i=1}^nc_ij_i$
    - 其中第i维的长度为$b_i$，化简后$c_n=L,c_{i-1}=b_i*c_i$

  ```c
  #include  <stdarg.h> //提供va_start, va_arg, va_end，用于存取变长参数表
  Status InitArray(Array *A, int dim, …) {
      va_list ap; //ap 存放变长参数表信息的数组
      //若维数dim 和各维长度合法，则构造数组 A, 并返回 OK
      if  ( dim <1 || dim > Max_ARRAY_DIM){
          return ERROR;
      }
      A->dim = dim;
      A->bounds = (int *) malloc ( dim* sizeof (int)); if (!A->bounds) return OVERFLOW;
      //若各维长度合法(>0)，则存入 A->bounds, 并求出 A 的元素总数 elemtotal
      elemtotal = 1;
      va_start(ap, dim);  // 第二个参数指明变长部分的前一个参数 
      for ( i=0; i< dim; ++i) {
          A->bounds[i]= va_arg(ap, int) ; // 存每一维度的长度
          if (A->bounds[i] <= 0){
              return UNDERFLOW;
          }
          elemtotal *= A->bounds[i]; 
      }
      va_end(ap);
      A->base = (ElemType *) malloc(elemtotal * sizeof(ElemType)); 
      if  (!A->base) {
          return OVERFLOW;
      }
      A->constants=(int *)malloc(dim*sizeof(int));
      if (!A->constants){
          return OVERFLOW;
      }
      // 求映象函数的常数𝑐_𝑖, 并存入 A->constants[i-1], i = 1,…,dim
      A->constants[dim -1]= 1; 
      for ( i=dim -2; i>= 0; - - i){
          A->constants[i] = A->bounds[i+1] * A->constants[i+1] ; // 递推式
      }
      return OK; 
  }
  ```

  - 计算$offset=\Sigma_{i=0}^{n-1}idx[i]\times constants[i]$

#### 4.0.1 特殊矩阵存储

- 下三角：只用存一半
  - 对于元素$a_{ij}$，存储位置$k=\begin{cases}\frac{i\times (i+1)}{2}+j,&i\ge j\\ \frac{j\times (j+1)}{2}+i,&i< j\end{cases}$
  - 第$i-1$行有$i$个元素，求和即得上式
  
- 三对角矩阵：共$3n-2$个元素
  - $a_{ij}$存在$k=2\times i+j$
  - 反推有$i=\lfloor (k+1)/3 \rfloor , j=k-2\times i$

- 稀疏矩阵：$\delta=\frac{t}{m\times n}$，$\delta \le 0.05$可以认为是稀疏矩阵

  - 三元组存：$\{i,j,a_{ij}\}$表示一个元素

    - 便于求转置，$\{i,j,a_{ij}\}\to \{j,i,a_{ij}\}$

    - 朴素转置法的复杂度为$O(M.nu*M.tu)$，当$M.tu \approx M.mu*M.nu$，时间复杂度相当高
  
      ```c
      q =0;
      for (col = 0; col < M.nu; col++){ // 按列处理，确保转置后行序单调
          for (p = 0; p < M.tu; p++){
              if (M.data[p].j== col) {		
                  T->data[q].i = M.data[p].j; T->data[q].j = M.data[p].i;
                  T->data[q].e = M.data[p].e;
                  q++;
              }
          }
      }
      ```

    - 快速转置：计算`num[col]`，表示转置前各列非零元个数；因此可以确定`cpot[col]`，表示每一列的非零元在转置数组中的存储位置

      - 转置的时候，顺序扫一遍矩阵，直接转置，存到`cpot[col]`指定的下标，然后`cpot[col]++`即可
      - 省去了很多无用的扫描
  
    ```c
    for(col=0; col<M.nu; ++col){
    	num[col] = 0;
    }
    for(t=0; t<M.tu; ++t){
        ++num[M.data[t].j];
    }
    cpot[0] = 0;
    for(col=1; col<M.nu; ++col){
        cpot[col] = cpot[col-1]+num[col-1]; // 预处理每一列的起始位置
    }
    for(p=0; p<M.tu; ++p){
        col = M.data[p].j;
        q = cpot[col];
        T->data[q].i = M.data[p].j;
        T->data[q].j = M.data[p].i;
        T->data[q].e = M.data[q].e;
        ++cpot[col]; // 为存该列的下一个元素做准备
    }
    ```
  
  - 行逻辑连接的顺序表：在三元组的基础上维护一个`rpos`数组，表示每个行起始的下标
    - 处理矩阵乘法
    - 将`arow`从0循环到`M.mu`对于M的每一行做如下处理：
    
    ```c
    for (i = 0; i < N.nu; i++){
    	ctemp[i] = 0; // 当前行各元素累加器清零
    }
    Q->rpos[arow] = Q->tu; // Q是乘法结果存储矩阵，当前行的起始下标就是现在存的元素个数
    if (arow < M.mu - 1){ // 生成对于当前行的遍历结束下标
    	s = M.rpos[arow + 1];
    }else{
    	s = M.tu + 1;
    }
    
    for (p = M.rpos[arow]; p < s; ++p){
    	// 对M矩阵当前行中每一个非零元
    	brow = M.data[p].j; // 根据当前元素的列号来取N中的元素
    	if (brow < N.mu){ // 生成对于当前列的遍历的结束下标
    		t = N.rpos[brow + 1];
    	}else{
    		t = N.tu + 1;
    	}
    	for (q = N.rpos[brow]; q < t; ++q){
    		ccol = N.data[q].j; // 乘积元素在Q中列号
    		ctemp[ccol] += M.data[p].e * N.data[q].e;
    	} // for q, 计算Q中第arow行的积并存入ctemp[]
    } // 求得Q中第crow( =arow)行的非零元
    for (ccol = 0; ccol < Q->nu; ++ccol){// 将ctemp[]中非零元素压缩存储到Qdata
    	if (ctemp[ccol]){
    		if (Q.tu > MAXSIZE){
    			return ERROR;
    		}
    		Q->data[Q->tu].i = arow;
    		Q->data[Q->tu].j = ccol;
    		Q->data[Q->tu].e = ctemp[ccol];
    		Q->tu++;
    	} // if
    } 
    // 总体看来，是M每一行都按规律和整个N相乘，一次性生成Q的一整行
    ```
    
  - 十字链表：非零元位置和个数变化较大时使用，贴合链表适合加工型操作的特性
  
    - 处理矩阵加法
  
    ```c
    typedef struct OLNode{
    	int i, j;
    	ElemType e;
    	struct OLNode *right, *down;
    } OLNode, *Olink;
    typedef struct{
    	// 行和列链表 头指针向量的基址
    	Olink *rhead, *chead;
    	int mu, nu, tu;
    } CrossList;
    ```
    
    - 两个表头向量构成矩形的两条边，每个节点在内部，向右和向下分别构成单链表
    - 建表、添加节点等和单链表完全一致！在横向和纵向分别做一次操作即可
    - 矩阵加法时，每次扫一行：
      - `pa、pb`只有一个有数据，则在存结果的链表中新建节点，直接存数据
      - `pa、pb`在该位置都有数据，相加，非0则存，0则忽略

### 4.1 广义表

- 广义表LS是n个表元素$\alpha_1,\alpha_2,...,\alpha_n$组成的有限序列$LS(\alpha_1,\alpha_2,...,\alpha_n)$
  - $\alpha_i$可以是广义表，也可以是数据元素（原子）
  - 最外层的元素个数为LS的长度，即n
  - 原子的深度为0，空表的深度为1
  - $广义表的深度 = \max\{子表的深度\}+1$，即所含括弧的重数
  - 当表非空，表的第一个元素为表头，其余为表尾
    - `LS(x)`，表头为x，表尾为空表
- 性质
  - 数据有相对次序，类似线性结构
  - 递归定义的线性结构
    - $F(4,F)$，显然这个递归定义的表$depth(F)=\infty$
    - 多层次的
    - 递归的表->有向图
  - 广义表可以共享，即A表可以作为B表的子表出现

#### 4.1.0 表头表尾分析法

- 广义非空的时候一定可以拆解为表头和表尾

```c
typedef enum{
	ATOM,
	LIST
} ElemTag;
typedef struct GLNode{
	ElemTag tag;
	union{
		AtomType atom;
		struct{
			struct GLNode *hp, *tp;// ptr.hp, ptr.tp指向表结点的表头、表尾
		} ptr;
	}
} Glist;
```

![](C:\Users\30130\Desktop\workstation\DSA\复习doc\表头表尾示意图.jpg)

- 上图的广义表可以如下表示：
  - B=(e)
  - C=(a,(b,c,d))
  - D=((),B,C)
- 显然的，这种表示方法要求每个原子节点都作为一个广义表的表尾，因为单独的原子无法向后链接其他节点，所以原子只能作为“叶子”出现

#### 4.1.1 子表分析法

- 将每个节点都当多留一个向后的指针域，即原子正常存，广义表在上层存一个不挂载数据的表头，向下延伸数据节点

```c
typedef enum { 
	ATOM, 
	LIST 
} ElemTag;
typedef struct GLNode {
  ElemTag tag; // ATOM or LIST
  union {      // 原子结点和表结点的联合部分
    AtomType atom;
    struct GLNode *hp; // 指向子表的指针
  };
  struct GLNode *tp;
  // 指向同一层下一个表元素结点的指针，类似单链表的*next
} Glist;
```

![](C:\Users\30130\Desktop\workstation\DSA\复习doc\子表分析法.jpg)

- 更符合直觉性思维的一种写法

#### 4.1.2 广义表的操作

- 递归定义的数据结构，当然要递归处理
- 每次剥离一个表头元素，即**在括号匹配的情况下**，遇到的第一个`,`作为分界，分别递归前半段，存在`hp`，递归后半段存在`tp`
- 一般来说，递归函数返回的是指针

```c++
GLNode* createGList(string s, int &pos){
    GLNode *node = NULL;
    char c = s[pos];
    pos++;

    if(c == '('){
        node = new GLNode();
        node->type = List;
        node->hp = createGList(s, pos);
        if(s[pos] == ')'){
            pos++;
        }
        if(s[pos] == ','){
            pos++;
            node->tp = createGList(s, pos);
        }else{
            node->tp = NULL;
        }
    }else if(isalpha(c)){
        node = new GLNode();
        node->type = Atom;
        node->data = c;
        if(s[pos] == ','){
            pos++;
            node->tp = createGList(s, pos);
        }else{
            node->tp = NULL;
        }
    }else if(c == ')'){
        pos--;
        return NULL;
    }
    return node;
}
```

- 删除节点，就是递归查找，比对所有Atom节点的值，匹配的话就删

------------

## 5 树

- 树可以分为根和子树，每棵子树的根有一个直接前驱和0或多个直接后继
  - 各个子树之间没有交集
- 概念
  - 节点的度：节点的子树数量
  - 叶子：度为0的节点
  - 路径
  - 树的度：节点度的最大值，最大度为m则为m叉树
  - 树的宽度：每层节点的最大数量为树的宽度
  - 祖先、子孙
  - 满m叉树：除了根和叶子，其余节点度数都是m
  - 完全m叉树：除了最后一层，其余为满m叉树，且最后一层的节点全部连续在左侧
  - 森林

### 5.0 二叉树

- 性质
  - 第i层最多$2^{i-1}$个节点
  - 深度为k，最少k个节点（退化为链），最多$2^k-1$个节点（满二叉）
  - 叶子节点有$n_0$，度为2的节点有$n_2$，则$n_0=n_2+1$
    - 考虑树的性质：边+1=点
  - 完全二叉树有n个节点，所以深度$k=\lfloor \log_2n\rfloor+1=\lceil \log_2(n+1)\rceil$
  - 显然的，对于编号的完全二叉树，编号i的节点，父亲为$\lfloor i/2\rfloor$，左右孩子分别为$2i,2i+1$
- 几乎所有的二叉树操作都可以递归进行

#### 5.0.0 存储方式

- 顺序存储

  - 按照编号i的节点，父亲为$\lfloor i/2\rfloor$，左右孩子分别为$2i,2i+1$来进行存储
  - 对于非完全二叉树，空间利用效率比较低

- 二叉链表

  - 节点两个指针域`*lc,*rc`，分别指向两个孩子

- 三叉链表

  - 三个指针域，分别指向两个孩子和父亲

- 双亲链表

  - ```c
    Typedef struct BPTNode{
    	TElemType data;
    	int parent;
    	Char LRTag;
    }BPTNode;
    ```

  - `parent`为父亲的下标，`LRTag`表示自身相对于父亲的左右孩子关系

#### 5.0.1 遍历

- 先序、中序、后序

  - 这个要会手算
  - 这个用递归或者栈模拟

- 层序遍历

  - 这个用队列，显然的

- 先中后序的递归处理或者栈模拟

  - 栈模拟的具体实现和后面的线索化一起给出

  - 递归写法很简单，仅给出先序的写法

  - ```c
    void preorder(Tree *t){
    	if(t){
    		vst(t->data);
            if(t->lc){
                preorder(t->lc);
            }
            if(t->rc){
                preorder(t->rc);
            }
        }
        return;
    }
    ```

  - 先序

    - 根节点压栈
    - 栈空之前，重复：弹栈，输出，压入右孩子，压入左孩子

  - 中序

    - 维护一个游标`cur_idx`，从根节点开始，一直向`lc`方向扫描，扫到一个节点就压栈
    - 当`cur_idx==0`即到底时，弹栈，输出
      - 如果弹栈元素有右孩子，将游标切换到右孩子，继续向`lc`扫描
      - 否则保持游标不动

  - 后序用先序改一下就行

    - $root\to rc\to lc$，再逆向输出，就是$lc\to rc\to root$
  
- ==HIGHLIGHT==：通过先序/中序，后序/中序，层次/中序可以**唯一**地确定一棵二叉树；而没有中序遍历的任意两种遍历都无法确定唯一的二叉树

  - 为什么可以？

    - 层序、先后序都可以一眼丁真看出根节点，利用中序可以将序列进行分割，分离为左子树-根-右子树的形式，再对两棵子树进行类似操作，直到序列被完全分隔
  - 没有中序为什么不行？
  
    - 而没有中序的情况就会产生如下歧义：对于只有单个孩子的情况，e.g. `preorder=1,2; postorder=2,1`，显然可得1为根节点，但是无法确定2是1的左孩子还是右孩子
    - 特殊的！！！当说明该二叉树是一棵**正则二叉树**时，即**任何非叶子节点都有两个孩子（完全二叉树的情况）**，任意两种遍历都可以确定树的结构
      - e.g. 已知一棵满二叉树，`preorder=1,2,4,5,3,6,7; postorder=4,5,2,6,7,3,1`
      - 先序的第一个和后序的末尾都是1，则1是树根
      - 先序1后面是2，2是1的左子树的树根
      - 在后序中找2，2之前的序列为左子树序列
      - 所以4是2的左孩子，5是2的右孩子
        - 左子树处理完成
      - 先序5后是3，3是1的右子树的树根
      - 在后序中找3，3之前、2之后的序列为右子树
      - 6为3的左孩子，7为3的右孩子


### 5.1 哈夫曼树

- 一棵编码树，一棵最优判定树

  - 判定树：叶子节点是比较结果，内节点是比较过程，叶子的权是概率
  - 编码树：叶子是需要编码的字符，从根到叶子的路径所代表的串是该字符的编码

- 保证带权路径和是最小的

  - 树的带权路径长度：树的所有叶子结点的带权路径长度之和
  - $l_k$是根节点到叶子k的路径长度，则$WPL(T)=\Sigma_{k=1}^nw_kl_k$，$w_k$为叶子k的权值

- 贪心就完事了

  - 初始每个节点为一棵只有根节点的二叉树
  - 在只剩一棵树之前，重复下列步骤：
    - 每次选择两棵根节点值最小的二叉树，分别作为左右子树，构建一棵新树，新树根节点的值为两棵子树根节点权值的和
  - 得到的最终树应该有下列性质：
    - 根节点的值是所有能生成的树中最小的
    - 值越大的节点，深度越小（贪心造成的）

- 我们用哈夫曼树构造变长编码

  - 前缀编码：任何一个字符的编码都不是同一字符集中另一个字符的编码的前缀
  - 哈夫曼树可以构造一个字符集的二进制前缀编码
  - 是一种最优前缀编码，可以使得该字符集所组成的串长度最短
  - 前提是知道每种字符使用的频度（作为叶子的权值）

- 显然哈夫曼树是一棵正则二叉树

- 考虑使用静态三叉链表来存，同时父亲和两个孩子的关系

- 对于初始n个叶子节点，则最终的哈夫曼树有$m=2n-1$节点

  - 不妨将数组`1~n`下标初始化为叶子，即`w=weight,lc=rc=parent=0`
  - `i=n+1~m`，在`1~i-1`中找`parent=0且权最小的两个节点s1,s2`，i作为二者的父亲，s1,s2为儿子，合并为一棵新树
  - 显然小根堆可以有很好的优化效果，但是好像我们不用掌握

- 如何获得哈夫曼树的编码？

  - 找每个叶子到根的路径，逆向输出就是该叶子的编码

  - ```c
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    // 分配存放n个字符编码的头指针向量
    cd = (char *)malloc(n * sizeof(char)); // 存放 编码
    cd[n - 1] = '\0';
    for (i = 1; i <= n; ++i) { // 逐个字符求Huffman编码
      	start = n - 1;           // 编码结束位置
      	for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
        // 从叶子到根逆向求编码
        	if (HT[f].lchild == c) {
          		cd[--start] = '0';
        	} else {
          		cd[--start] = '1';
        	}
      	}
      // 为第i个字符的编码分配空间
      	HC[i] = (char *)malloc((n - start) * sizeof(char));
      	strcpy(HC[i], &cd[start]); // 从cd复制编码到HC
    }
    free(cd);
    return HC;
    ```

  - 无栈非递归遍历

    - 树已经完成构建，`weight`失去作用，因此可以作为访问的标记

  - ```c
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    cd = (char *)malloc(n * sizeof(char));
    q = m;
    cdlen = 0;
    for (i = 1; i <= m; ++i){
        (HT + i)->weight = 0; // 用作结点状态标志
    }
    while (q) {             // 从根出发，遍历Huffman树
        if ((HT + q)->weight == 0) {
            (HT + q)->weight = 1; // 向左，访问左结点
            if ((HT + q)->lchild != 0) {
                q = (HT + q)->lchild;
                cd[cdlen++] = '0';
            } else if ((HT + q)->rchild == 0) { // 到达叶结点，登记该结点的编码
                HC[q] = (char *)malloc((cdlen + 1) * sizeof(char));
                cd[cdlen] = '\0';
                strcpy(HC[q], cd);
            }
        } else if ((HT + q)->weight == 1) {
            (HT + q)->weight = 2; // 向右访问右结点
            if ((HT + q)->rchild != 0) {
                q = (HT + q)->rchild;
                cd[cdlen++] = '1';
            }
        } else { // (HT+q)->weight == 2，该结点的左右孩子都访问过了
            (HT + q)->weight = 0;
            q = (HT + q)->parent;
            --cdlen; // 退回父节点
        } // else
    } // while
    return HC;
    ```

### 5.2 线索化二叉树

- 二叉树的叶子节点的`lc,rc`域不存数据，空间利用较低
  - 将数据域改造为`ltag,lc,rtag,rc`
  - `ltag=Link`，则`lc`存左孩子
  - `ltag=Thread`，则`lc`存线索化的前驱（某种线索化下）
  - 同理`rc`可以用来存后继
- 原理很简单，直接贴出三种线索化的代码，来源：[oj | 6.20-二叉树的线索化](http://152.136.172.65/problem/1038)

```c++
vector<Node> preorder_treading(vector<Node> t){ // 先序前驱线索化
    vector<Node> preorder_t = t;
    stack<Node> s;
    s.push(preorder_t[val2idx[preorder_t[0].id]]);
    Node pre = s.top();
    while(1){
        pre = s.top();
        s.pop();
        if(pre.rc!=0 && pre.rtag==Link){
            s.push(preorder_t[val2idx[pre.rc]]);
        }
        if(pre.lc!=0 && pre.ltag==Link){
            s.push(preorder_t[val2idx[pre.lc]]);
        }
        if(s.empty()){
            break;
        }
        Node cur = s.top();
        if(cur.lc==0 && cur.ltag==Link){
            cur.ltag = Tread;
            cur.lc = pre.id;
            int cur_idx = val2idx[cur.id];
            preorder_t[cur_idx] = cur;
        }
    }
    return preorder_t;
}

vector<Node> postorder_treading(vector<Node> t){ // 后序后继线索化，使用反转变形先序（root-rc-lc反转）
    vector<Node> postorder_t = t;
    stack<Node> s;
    s.push(postorder_t[val2idx[postorder_t[0].id]]);
    Node pre = s.top();
    while(1){
        pre = s.top();
        s.pop();
        if(pre.lc!=0 && pre.ltag==Link){
            s.push(postorder_t[val2idx[pre.lc]]);
        }
        if(pre.rc!=0 && pre.rtag==Link){
            s.push(postorder_t[val2idx[pre.rc]]);
        }
        if(s.empty()){
            break;
        }
        Node cur = s.top();
        if(cur.rc==0 && cur.rtag==Link){ // 变形先序中的前驱就是后序中的后继
            cur.rtag = Tread;
            cur.rc = pre.id;
            int cur_idx = val2idx[cur.id];
            postorder_t[cur_idx] = cur;
        }
    }
    return postorder_t;
}

vector<Node> inorder_treading(vector<Node> t){ // 中序全线索化
    vector<Node> inorder_t = t;
    stack<Node> s;
    int cur_id = inorder_t[0].id;
    Node pre(-1, -1, -1);
    while(!s.empty() || cur_id!=0){
        while(cur_id != 0){
            s.push(inorder_t[val2idx[cur_id]]);
            if(inorder_t[val2idx[cur_id]].ltag == Link){
                cur_id = inorder_t[val2idx[cur_id]].lc;
            }else{
                cur_id = 0;
            }
        }
        Node cur = s.top();
        s.pop();
        if(pre.id != -1){
            if(pre.rc==0 && pre.rtag==Link){
                int pre_idx = val2idx[pre.id];
                inorder_t[pre_idx].rtag = Tread;
                inorder_t[pre_idx].rc = cur.id;
            }
            if(cur.lc==0 && cur.ltag==Link){
                int cur_idx = val2idx[cur.id];
                inorder_t[cur_idx].ltag = Tread;
                inorder_t[cur_idx].lc = pre.id;
                cur.ltag = Tread;
                cur.lc = pre.id;
            }
        }
        pre = cur;
        if(cur.rc!=0 && cur.rtag==Link){
            cur_id = cur.rc;
        }else{
            cur_id = 0;
        }
    }
    return inorder_t;
}
```

### 5.3 树

#### 5.3.0 树的表示与存储

- 双亲表示法

  - 因为父亲是唯一的，所以可以只存父亲的信息

- 孩子表示法

  - 类似于邻接表的结构
  - 表尾存的是当前节点的所有孩子

- 孩子-兄弟表示法

  - ```c
    typedef struct Node{
        int data;
        struct Node *parent;
        struct Node *firstchild, *nextsibling;
    }Node;
    ```

  - `*firstchild`指向第一个孩子，`*nextsibling`指向下一个兄弟

    - 先找`*firstchild`，然后沿着`*nextsibling`扫描，可以遍历所有孩子
    - 解决了孩子数不确定难以存储的问题

  - 显然的，这种方式可以把任何一棵树转化为一棵唯一对应的二叉树

    - 需要掌握二者之间互相转换的方法，看图说话即可

#### 5.3.1 树的性质

- 树的节点数等于所有节点的度数+1
- 度为m的树，其第i层至多$m^{i-1}$节点（参考二叉树）
- 高度为h的m叉树至多$(m^h-1)/(m-1)$节点
- 具有n个节点的m叉树的最小高度h为$\lceil log_m(n(m-1)+1)\rceil$
- 一棵树可以转换为一棵唯一的没有右子树的二叉树（孩子-兄弟表示）
- n个节点的不同形态的树的数目记为$t_n$，具有n-1个节点互不相似的二叉树的数目相同，$t_n=b(n-1)$
  - $b(0)=b(1)=1$
  - $b(n)=h(n)=\Sigma^{n-1}_{i=0}h_ih_{n-i-1}$
  - $h_n=\frac{1}{n+1}C^n_{2n}=\frac{1}{n+1}\frac{(2n)!}{n!n!}$

#### 5.3.2 树的遍历

- 先根遍历，后根遍历
  - 先根遍历对应**孩子-兄弟表示**转换二叉树的先序遍历
  - 后根遍历对应二叉树的中序遍历
- 广度优先遍历，层序遍历

#### 5.3.3 树的应用

- 并查集（这个很重要，Kruskal要用）

  - 本质是维护等价类的关系

  - ```c
    int f[n+5]; // f[i]表示i所在等价类的代表元，可以是i所在树的树根
    int get_father(int i){ // 查询所在的等价类
        if(f[i] == i){
            return i;
        }
        return f[i] = get_father(f[i]); // 路径压缩写法
    }
    ```

  - ```c
    void merge(int i, int j){
    	f[get_father(j)] = get_father(j); // 将i和j的等价类合并
        return;
    }
    ```

  - ppt是直接维护的多棵树结构来表示并查集，树根即为代表元

    - `parent`一直上跳找树根

    - 合并就是把i所在树的树根的`parent`设置为j所在树的树根

    - 路径压缩变得更复杂，必须把路径上所有的点再次遍历

    - ```c
      int FixMFSet(MFSet *S, int i) {
        int j, k, t; // 确定i所在子集，
        // 将从i至根路径上所有结点变为根的孩子结点
        if (i < 0 || i = > S->n)
          return ERROR;
        // 寻找i所在树的根，记录在j
        for (j = i; S->nodes[j].parent >= 0; j = S->nodes[j].parent)
          ;
        for (k = i; k != j; k = t) {
          // 将从i到根沿路结点的双亲都指向根
          t = S->nodes[k].parent;
          S->nodes[k].parent = j;
        }
        return j;
      }
      ```

- 幂集生成，四皇后
  - 一棵dfs搜索树
  - 幂集选择取与不取，树深度等于元素个数
  - 四皇后就是八皇后简化版，直接搜

### 5.4 森林

- 多棵树成为森林
- 森林转二叉树
  - 首先，每棵树都用**孩子-兄弟表示**转成一棵没有右子树的二叉树
  - 第k棵树的根作为第k-1棵树的右子树
  - 最后成为一棵二叉树
- 二叉树转森林
  - 分离右子树，递归处理右子树
  - 将当前二叉树转化为树
- Q：设F是一个森林，B是由F转换得到的二叉树，F中有n个非叶结点，那么B中右指针为空的结点有多少个？
  - A：$n+1$
  - 每一个非叶子节点都有若干孩子，而这些孩子中一定仅存在一个*最右侧*的孩子没有下一个兄弟，即在二叉树中没有右子树
  - 最后一棵树的根节点也没有右子树
  - 总共$n+1$
- 森林的遍历
  - 先序：对应二叉树的先序
  - 中序：对应二叉树的中序
