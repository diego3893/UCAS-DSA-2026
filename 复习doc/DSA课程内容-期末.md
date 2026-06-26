# DSA课程内容doc-期末

## 6 图论

- 树plus（？），树可以看做是没有环路的图

### 6.0 概念

- $G=(V, E)$，V为顶点集，E为边集
- 子图
- 生成子图：由$G'=(V, E'\subseteq E), E'$为生成子图
- 简单图：无自环，无重边
- 完全图
- 多重图：有多重边
- 有向图/无向图
- 对于有向边：$i\to j$中，i是弧尾，j是弧头
- 稀疏图：$e<n\log_2n$
- 简单路径：没有重复顶点
- 无向图的连通性：
  - 连通分量：极大连通子图
  - 极小连通子图：最小生成树
- 有向图的连通性：
  - 强连通性：任意两点存在双向路径
  - 强连通分量：极大连通子图
  - 生成森林
- 割边（桥）/割点（关节点）

- 度
  - 无向图
    - 顶点的度之和为边的两倍
  - 有向图
    - 分出度和入度，且出度之和=入度之和，其余和无向图一致
- 路径/回路
- 哈密顿路径/回路：每个点经过一次
- 欧拉路径/回路：每条边经过一次
  - 定理：含有至少2个顶点的多重连通图具有欧拉回路，当且仅当，它的每个顶点的度都为偶数
  - 定理：一个多重连通图具有欧拉路径但没有欧拉回路，当且仅当，它恰好有2个度为奇数的顶点
  - 定理：一个有向图存在欧拉回路的充要条件是该图必须是强连通的且每一个顶点有相同的入度和出度


### 6.1 存储

#### 6.1.0 邻接矩阵

- `a[i][j] = w`表示 $i\to j 有一条边，且权重为w$

#### 6.1.1 邻接表

- 维护一个头指针数组`headvex`，`headvex[i]`表示第i个节点
- 每个头指针节点维护一个单链表，表示邻接点信息
- 分正邻接表（维护出度），逆邻接表（维护入度）

#### 6.1.2 十字链表

```c++
struct node{
    int tailvex;
    int headvex;
    node *tlink; // 弧尾方向
    node *hlink; // 弧头方向
    int info; // 存权重等
};
struct headNode{
    int data;
    node *firstin, *firstout;
};
```

![](./图的十字链表.jpg)

- 同时维护**有向图**的入度和出度，可以看做被融合的正邻接表和逆邻接表

- 由上述定义可知：


  - 每个边节点（node），存储边的所有信息，维护出、入信息


  - 每个点节点（headNode），存储编号，以及第一条出边、入边的指针


  - 沿着$firstin\to hlink$维护逆邻接表，读边的`tailvex`
  - 沿着$firstout\to tlink$维护正邻接表，读`headvex`

  - **画图方法**：
    - 先画一张正邻接表，补全`firstout、tlink`
    - 在该表中按照逆邻接表的画法连接`firstin、hlink`
  - 代码实现为头插法，参考邻接多重表的示例代码

#### 6.1.3 邻接多重表

![](./邻接多重表.jpg)
```c++
struct node{
	int info;
    int mark; // 标记该边是否被遍历
    node *ilink, *jlink;
    int ivex, jvex;
};
struct headNode{
    int data;
    node *firstedge;
};
```


  - 维护无向图的边关系
  - 在普通邻接表中，无向图的每条边需要两个节点表示，冗余！邻接多重表只需要一个节点
  - 由结构体定义可知节点的构造，可以类比十字链表，只是对于无向边不对两个顶点加以区分，用i/j代指
- 同一张图的邻接多重表有**多种画法**！

- **如何画图**？（见下图，这是例题的另一种画法）
  1. 将无向边`(ivex, jvex)`列出，不妨取$ivex<jvex$
  2. 将ivex视作“弧头”，画正邻接表，此时0号节点的每条边都被正确相连
  3. 对后续的每一个顶点：遍历所有边，顺次相连（可以是图中最好连线的方式来画），注意ilink和jlink即可
  4. 高度建议画完之后检查一遍所有顶点是不是都可以遍历关联边
- 头插法维护

```c++
// 邻接多重表建表代码
for(int k=1; k<=n; ++k){
	scanf("%d%d", &i, &j); // 假设i<j
  	p = new node;
  	p->ivex = i, p->jvex = j;
  	p->ilink = head[ivex].firstedge, p->jlink = head[jvex].firstedge;
  	head[ivex].firstedge = p, head[jvex].firstedge = p;
}
// 遍历某个顶点的邻接点
p = head[vex].firstedge;
while(p){
    if(p->ivex == vex){
        printf("%d ", p->jvex);
        p = p->ilink;
    }else if(p->jvex == vex){
        printf("%d ", p->ivex);
        p = p->jlink;
    }
}
```

![](./邻接多重表2.jpg)

### 6.2 遍历

- DFS
  - 数据结构为栈或者队列
  - 前序：调用DFS之前压入队列
    - 求顶点路径
  - 后序：调用DFS之后压入队列
  - 逆前序：调用DFS之前压入栈
  - 逆后序：调用DFS之后压入栈
    - 拓扑排序
  
  ```c++
  void dfs(int cur){
      for(int i=1; i<=next_state[cur]; ++i){
          vis[cur] = 1;
          nxt = state[cur][i];
          if(!vis[nxt]){
              dfs(nxt);
          }
          vst[cur] = 0; // 回溯
      }
  }
  ```
  
- BFS

  - 使用队列
  - 类似树的层次遍历
  - 对于每条边平权的情况下，找出来的第一条一定是最优路径

  ```c++
  // q为队列
  while(!q.empty()){
      vis[cur] = 1;
  	int cur = q.head();
      q.pop();
      for(int i=1; i<=nxt_state[cur]; ++i){
          int nxt = state[cur][i];
          if(!vis[nxt]){
              q.push(nxt);
          }
      }
  }
  ```

- 拓扑排序

  - 由一个偏序关系得到集合上的全序的操作
  - **无环图**才可以拓扑！拓扑排序本身就可以判断是否存在环
  - 手算拓扑序列，Kahn更简单

  ```c++
  // Kahn的拓扑，如果ans!=n，则有环；需要输出拓扑序列，每找到一个入度为0的点存一下就行
  int topo(vector<vector<int> > g, int indeg[], int n){
      int ans = 0;
      int u;
      int is_indeg_zero;
      do{
          u = -1;
          is_indeg_zero = 0;
          for(int i=1; i<=n; ++i){
              if(indeg[i] == 0){
                  indeg[i] = -1;
                  u = i;
                  is_indeg_zero = 1;
                  ans++;
                  break;
              }
          }
          if(u != -1){
              for(int i=0; i<g[u].size(); ++i){
                  indeg[g[u][i]]--;
              }
          }
      }while(is_indeg_zero);
      return ans;
  }
  ```

  ```c++
  // DFS逆后序求拓扑
  bool dfs(int u, const vector<vector<int>>& g, vector<int>& color, stack<int>& st) {
      color[u] = 1; // 标记为 1 (正在访问，处于递归调用栈中)
      // 遍历当前节点的所有出边 (邻接点)
      for (int i = 0; i < g[u].size(); ++i) {
          int v = g[u][i];
          if (color[v] == 1) {
              // 发现指向“正在访问”节点的边，说明存在回边 (环)！
              return false; 
          } else if (color[v] == 0) {
              // 遇到未访问的节点，继续深入 DFS
              if (!dfs(v, g, color, st)) {
                  return false; // 如果子树中发现环，层层向上报错
              }
          }
          // 如果 color[v] == 2 (已访问)，说明那是另一个已经处理完的分支，直接跳过即可
      }
      color[u] = 2; // 当前节点的所有邻接点都处理完毕，标记为 2 (已访问)
      // 【核心操作】：在节点彻底访问完毕之时，将其压入栈中 (这就是后序压栈)
      st.push(u); 
      return true;
  }
  
  // 外部调用的主控函数
  vector<int> topoDFS(const vector<vector<int>>& g, int n) {
      vector<int> color(n + 1, 0); // 状态数组：初始化为 0 (未访问)。假设节点编号 1~n
      stack<int> st;               // 用于存放后序序列的栈
      vector<int> result;          // 最终的拓扑排序结果
      // 图可能不是强连通的，存在多个独立的连通块，因此需要遍历所有节点作为起点尝试
      for (int i = 1; i <= n; ++i) {
          if (color[i] == 0) {
              if (!dfs(i, g, color, st)) {
                  return {}; // 返回空数组，表示检测到环，无法进行拓扑排序
              }
          }
      }
      // 逆后序输出：将后序压入的节点依次出栈，即为正向的拓扑排序
      while (!st.empty()) {
          result.push_back(st.top());
          st.pop();
      }
      return result;
  }
  ```

### 6.3 连通性

#### 6.3.0 无向图的连通性

- DFS生成树/生成森林
  - 树上的边是被dfs访问的边，即：点被标记后无法访问的边为回边，不在生成树中
- BFS生成树：类比DFS生成树
- 一般的，图用邻接表存，树/森林用孩子-兄弟链表

#### 6.3.1 有向图的强连通性

##### 6.3.1.0 Kosaraju

- 正图dfs一次，逆图dfs一次，两个图的强连通分量相同
- 逆图：将$G$的所有边反向得到$G'$
- 算法步骤：
  - 对$G$进行DFS，求所有顶点的逆后序编号（退出dfs的顺序，即拓扑排序）
  - 根据上一步中得到的编号，**从大到小**，对$G'$的点dfs，每一轮dfs得到的所有点归为一个集合，为一个强连通分量
  - $G'$每结束一轮dfs，保存一个强连通分量，寻找编号最大且未被访问的点开始新一轮dfs
  - 直到所有点均被访问
- 考虑使用**十字链表**存图，同时维护原图和逆图的正邻接关系（原图的逆邻接就是逆图的正邻接）；dfs维护一个**栈**来存逆后序点序列，即最后退出的点在栈顶
- ==证明==：若逆图有$s\to v$，则原图上s、v强连通
  - 逆图dfs到$s\to v$的路径，则s的编号大于v，s比v后退出原图dfs
  - 有两种情况：
    1. $dfs(s)_{st}\to dfs(v)_{st} \to dfs(v)_{ed}\to dfs(s)_{ed}$
    2. $dfs(v)_{st}\to dfs(v)_{ed}\to dfs(s)_{st}\to dfs(s)_{ed}$
  - 因为逆图有$s\to v$，所以原图一定有$v\to s$的路径，第二种情况不成立
  - 第一种情况意味着原图有$s\to v$的边
  - 所以s、v强连通

##### 6.3.1.1 tarjan

- 只用掌握求割点（关节点）的办法

- 已知dfs生成树，如何判别关节点？
  - 如果整棵树的根节点有多个分支，则为关节点
  - 对于非根节点的任意节点v：如果它的子树没有指向v的祖先的回边，则v为关节点
    - 如果存在连接到祖先的回边，则删除v，子孙仍和祖先通过回边连接，即v不是关节点

- 对于每个节点，维护两个变量`visited[v]`和`low[v]`
  - `visited[v]`表示节点i进入dfs的时间戳，即逆前序？
  - `low[v]`表示节点i能通过边回溯到的、时间戳最小的节点
    - 影响`low[v]`有三种：
      1. 子孙通过回边连接到了祖先
      2. 节点i自身通过回边连接到了祖先
      3. 节点i自身的时间戳
    - 因为我们需要能连接到的最早的那个祖先，则`low[v]=min(visited[v], low[w], visited[k])`
      - 其中，w为i的子孙，k为与w通过回边连接的祖先
    - 为什么只考虑回边，不考虑非回边？
      - 计算`visited`数组时的dfs生成了dfs生成树，将所有非回边的计算纳入`visited`内了

- 当`low[w]>=visited[v]`说明什么？

  - 子孙w能回溯到的最近节点也在v以下，则v被删除必然导致w和v的祖先断开，连通分量+1，v为关节点

- 特判！根节点直接判断孩子数量即可

- 代码实现思路：

  - 全局维护`low`，`visited`，`timer`，每个节点维护一个`child_cnt`
  - dfs每访问一个新节点：

  ```c++
  timer = 1;
  void tarjan(int v, int parent){
      int child_cnt = 0;
      visited[v] = timer++, low[v] = visited[v];
      for(遍历v的所有邻接点u){
          if(visited[u] == 0){ // 孩子
              child_cnt++;
              tarjan(u, v); // dfs会算完该孩子的整个子树之后才进入下一步，此时的low[u]已经确定
              low[v] = min(low[v], low[u]);
              if(parent == -1 && child_cnt>=2){
                  is_cut_node[v] = 1;
              }else if(parent!=-1 && low[u]>=visited[v]){
                  is_cut_node[v] = 1;
  			}
          }else if(u == parent){
              continue;
  		}else if(visited[u] != 0){ // 找到一个回边连接的祖先
              low[v] = min(visited[u], low[v]); 
          }
      }
  }
  ```

  - 在整个图上跑这个dfs即可

### 6.4 最小生成树

#### 6.4.0 Prim

- 贪心选择节点，用于**稠密图**，复杂度$O(n^2)$
- 选择**与当前树邻接的、权重最小的边**，整棵树一直保持连通
- 每次添加节点w，贪心策略如下：
  - w和树上已经有的节点v是邻接的
  - $(v,w)$的边权是所有$(v,w')$中最小的
  - 将w添加进最小生成树，cost累加

#### 6.4.1 Kruskal

- 贪心选择边，用于**稀疏图**，复杂度$O(e\log e+n^2)$，可优化至$O(e\log e)$
- 贪心选择**全局最小边权、且还没有连通**的边，是多棵树逐步连通的过程
- 贪心策略：
  - 将边权排序
  - 每次取当前的最小边
  - 维护并查集，判断：$(u,v)$是否在一个等价类中（等价类中元素表示相互连通）
  - 如果不连通，添加该边，cost累计

### 6.5 求关键路径/AOE

- 图中的顶点代表“事件”，边代表“依赖关系”或者“活动”，边权代表“耗时”

- 求从起点到汇点的最长路径

- 求整个工程完成的最短时间（工程中耗时最长的阶段制约了完成速度）

- 假设起点为A，汇点为W

- 定义四个变量：（手算AOE就是依次计算这四个，然后出结果）

  - 对于顶点$U$，定义`ve(U)`为*最早发生时间*，是从**起点**到该顶点的**最长路径长度**

    - `ve(U) = A到U的最长路径长度`

  - 对于顶点$U$，定义`vl(U)`为(不影响工程进度的)最迟发生时间，是从汇点最早发生时间减去该顶点到汇点的最长路径长度

    - `vl(U) = vl(W) - U到W的最长路径长度`
    - `vl(A)=ve(A)=0, vl(W)=ve(W)`

  - 对于边$i=(j, k)$，定义`e(i)`为活动最早开始时间

    - `e(i) = ve(j)`

  - 对于边$i=(j, k)$，定义`l(i)`为活动最迟开始时间
    - `l(i) = vl(k)-w(i)`，w(i)为i的边权
- 所有`e(i)==l(i)`的都是关键路径
- 由上述定义，ve和vl的计算显然对之前的点有依赖性，代码实现时先做拓扑排序，按拓扑正序计算ve，按拓扑逆序计算vl

### 6.6 最短路径

#### 6.6.0 Dijkstra 单源最短路

- 这玩意必须会手算，巨喜欢考，就模拟算法跑n遍结束
  - 如果想考难一点，可以加堆优化（这样很不道德我希望不要这样）
- 核心思想是“松弛”
  - 每次选择已经算出的、还未确定的所有单源路径中，选择最小的那一条，确定之
  - 因为新确定了一条最短路，将这条路径终点作为中转，修改其他未确定路径的代价

```c++
// 邻接矩阵存图
memset(vst, 0, sizeof(vst)); // 初始化vst为0，表示没有确定任何路径
memset(dis, 0x3f, sizeof(dis)); // 初始化路径代价为INF，表示未被计算
dis[st] = 0; // 起始点到自己的距离已知，为0
for(int i=1; i<=n; ++i){
	int min_idx = -1;
    int minn = INF;
    for(int j=1; j<=n; ++j){ // 找未被访问的、路径开销最小的点
        if(!vst[j]){
            if(minn > dis[j]){
                minn = dis[j];
                min_idx = j;
            }
		}
	}
    if(min_idx == -1){ // 不连通
        break;
	}
    vst[min_idx] = 1; // 确定该点的最短路径长度
    for(int j=1; j<=n; ++j){
        if(!vst[j] && dis[j]>dis[min_idx]+g[min_idx][j]){
            dis[j] = dis[min_idx]+g[min_idx][j]; // 松弛！
		}
    }
}
```

#### 6.6.1 Floyd 全源最短路

- 无脑三重循环秒了
- 本质动态规划，看不懂可以死背
  - 最外层k枚举所有中转点
  - 后两层枚举路径的起点和终点
  - 状态转移：如果存在中转点k，使得原本的路径变短，则选择更短的路径

```c++
memset(f, 0x3f, sizeof(f)); // 初始化为INF
for(int i=1; i<=n; ++i){
    f[i][i] = 0;
}
// 输入边权，存入f中
for(int k=1; k<=n; ++k){
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            if(f[i][k]+f[k][j] < f[i][j]){
                f[i][j] = f[i][k]+f[k][j];
            }
        }
    }
}
```

