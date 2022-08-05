# 参数估计统计量的性质 有效性 无偏性 一致性

**Prerequisite：**

此篇文章用于蒙特卡洛方法的方差分析，在[数值分析基础](https://zhuanlan.zhihu.com/p/545565243)的章节中已经知道：
一致性： 渐近无偏性就是一致性

**蒙特卡洛方法的方差**
蒙特卡洛方法的方差：利用无偏估计可以通过样本方差来估计 $Q_N$的误差条(error bar)
构造随机变量： $Y = \frac{f(X)}{p(X)}$
备注： 其中推导使用了Property of Variance: $\sigma^2\left[ \sum\limits_{i=1}\limits^N Y_i\right] = \sum\limits_{i=1}\limits^N \sigma^2 \left[Y_i\right] $
$$
\begin{align*}
  \sigma^2[F_N] &=\sigma^2\left[ {\frac{1}{N}\sum\limits_{i=1}\limits^N\frac{f(X_i)}{p(X_i)}} \right] \\
  &= \frac{1}{N^2} \sum\limits_{i=1}\limits^N \sigma^2  \left[  \frac{f(X_i)}{p(X_i)} \right]  \\
  &= \frac{1}{N^2}\sum\limits_{i=1}\limits^N\sigma^2\left[Y_i\right]\\
  &= \frac{1}{N^2}\left(N \sigma^2[Y] \right)\\
  &= \frac{1}{N} \sigma^2[Y]\\
  所以有：\sigma[F_N] = \frac{1}{\sqrt{N}}\sigma[Y]\\
\end{align*}\\
$$
结论： 
1. 蒙特卡洛估值不稳定来源于随机变量$Y$ 取值的不稳定，即在$Y = \frac{f(x_i)}{p_i}$中$\frac{f(x_i)}{p_i}$值越大，就会是Y的方差越大。 从而影响蒙特卡洛估值的准确度。  所以若p(x)的形状越接近f(x)，则有益于最终结果的收敛。这就是**重要性采样**的思想
2. 估计值与理论值之间的误差可以通过增加样本数来减小，但收敛速率仅为$O(\sqrt{N})$。


### 参数估计

**评价性质**