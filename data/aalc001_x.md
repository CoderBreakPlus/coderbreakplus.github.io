题意经过一些转化，发现等价于可以用 $g_i$ 的代价将 $A_i$ 增加 $1$ 或减少 $1$，或者 $d_{i-1}$ 的代价将 $A_i \sum A_n$ 都增加 $1$ 或者减少 $1$。

将以上四种增加或减少操作的量分别定义为 $p_i,q_i,r_i,s_i$。

写出如下线性规划问题：

$$
\begin{aligned}
\min\quad&
\sum_{j=1}^N g_j(p_j+q_j)
+\sum_{i=1}^{N-1}d_i(r_i+s_i)\\
\text{s.t.}\quad&
A_j+p_j-q_j+\sum_{i<j}(r_i-s_i)-t=0
\qquad(1\le j\le N).
\end{aligned}
$$

线性规划对偶。我们来回忆一下对偶中等于号的规则：

$$
\boxed{
\begin{array}{c|c}
\text{原问题}&\text{对偶问题}\\ \hline
\min c^\mathsf Tx&\max b^\mathsf Ty\\
Mx=b&M^\mathsf Ty\le c\\
x\ge0&y\text{ 不限制正负}
\end{array}}
$$

令每条等式分配的对偶变量为 $w_i$，对他不限制正负。

先写出关于 $p_j$ 和 $q_j$ 的约束条件：

+ $w_j \le g_j$
+ $-w_j \le g_j$

再写出关于 $r_j$ 和 $s_j$ 的约束条件：

+ $\sum \limits_{i=j+1}^n w_i \le d_j$
+ $-\sum \limits_{i=j+1}^n w_i \le d_j$

再来看 $t$，可以把它拆成两个非负量 $u,v$ 来看，令 $t=u-v$，得到：

+ $\sum w_i \le 0$
+ $-\sum w_i \le 0$

最后最大化的东西就是 $-\sum \limits A_jw_j$。整理以上所有东西得到等价的问题：

$$
\boxed{
\begin{aligned}
\max\quad&\sum_{j=1}^NA_jw_j\\
\text{s.t.}\quad&
|w_j|\le g_j,\\
&\left|\sum_{j=i+1}^Nw_j\right|\le d_i,\\
&\sum_{j=1}^Nw_j=0.
\end{aligned}}
$$

这个显然可以转化成费用流。那么我们直接流就有了一个对的做法。

每次修改相当于关于这个点重新增广。

由于这是线段树场，考虑用线段树来模拟费用流。复杂度 $\mathcal{O}((n+q)\log n)$，常数较大。
