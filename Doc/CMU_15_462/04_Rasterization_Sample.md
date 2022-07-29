#! https://zhuanlan.zhihu.com/p/547513128
# 光栅化和采样

**Prerequisite**

全文的相关的数学知识可以参考[《凡人渲染传—数学篇》](https://www.zhihu.com/column/c_1534298442822557696)
### Fourier Transform


**Fourier Series**

* ![](./Image/Fourier_series.png)
$$
f(x) = \frac{A}{2} + \frac{2A\cos(tw)}{\pi} + \frac{2A\cos(3tw)}{3\pi} + \frac{2A\cos(5tw)}{5\pi} +\frac{2A\cos(7tw)}{7\pi} +\frac{2A\cos(7tw)}{7\pi}+ \dots
$$

**Fourier Transform**
作用： [图像傅里叶变换](https://zhuanlan.zhihu.com/p/99605178) 将信号从时域便换到频域
Decomposes A Signal Into Frequencies
![](./Image/Fourier_Transform.png)
输入一个时间t(有的也表示为x)的函数,输出一个频率函数
$$
F(w) = \int_{-\infty}^{\infty}f(t)e^{-2\pi(iwt) \text{d}t}
$$
输入频率w的函数，输出一个关于x的正弦（余弦）函数。 
$$
f(x) =  \int_{-\infty}^{\infty}F(w)e^{2\pi(iwx) \text{d}w}
$$

Higher Frequencies Need Faster Sampling
![](./Image/Periodic_Sample.png)
* 低频信号：充分采样以进行合理重建
* 高频信号采样不足：重建错误地似乎来自低频信号

走样的分析： 在给定采样率下无法区分的两个频率
![](./Image/Frequency_Aliases.png)

**傅里叶图像时域到频域的转换**

使用傅里叶变换对图像进行分析的时候需要将图像从时域信号转化到频域，如下图所示：
![](./Image/SpatialDomian2Spectrum.png)
具体转换规则：
1. 左图人像转化成灰度图，灰度值的大小对应z轴高度。这样就形成了凹凸不平的曲面
  ![](./Image/domianSurface.png)
2. 右图为频域图，频域信息对应到图中的每一个点：
    频率f： 点到图片中点的距离。
    振幅A： 点的灰度值。
    (波形面的)方向n： 中心点到该点的方向。
    相位$\phi$: 被舍弃掉了。



### Rasterizing triangles

**采样**
![](./Image/Convolution_Theorem.png)
光栅化: 一个像素点对应一个坐标点，对这个坐标点采样，判断它在不在三角形里面，
采样： 本质是重复频域（频率）上的内容。 Repeating Frequency Contents
![](./Image/Repeating_Frequency_Contents.png)
为什么图像频域长这样？  
理解二维图像傅里叶变换， 

采样的问题：
- Aliasing：（原始频域经过重复后出现重叠） 走样，表现为锯齿
  ![](./Image/Mixed_Frequency_Contents.png)


**反走样Anti-Aliasing:**
- Option 1: 增加采样率 Increase sampling rate
  - increasing the distance between replicas in the Fourier domain
  - Higher resolution displays, sensors, framebuffers
  -  `采样频率越大体现在在时域上就是T越小， 因此频域的f = 1 /T 就会大， 原始信号频率f进行卷积操作（也就是复制粘贴信号）越不容易发生混叠。 这样就能避免走样了`
- Option 2: Filtering
  - `去掉一些频率的信号Getting rid of certain frequency contents` 
  - 采样之前去掉图片中高频，可以参考之前写的[《Games101 采样理论知识补充》](https://zhuanlan.zhihu.com/p/547407165)， 于是就不会有重叠了：
  - 这里抗锯齿可以看作 = filtering = averaging （可以看作一种低通滤波器）
  

抗锯齿方法: 
先模糊再采样  Pre-Filter → Sample
![](./Image/PreFilter.png)

最理想的状态：像素的颜色值为负责的区域内的平均值。
![](./Image/Antialiasing_vs_Blurred_Aliasing.png)



**Sampling Artifacts** (Errors / Mistakes / Inaccuracies) in Computer Graphics
- Jaggies (Staircase Pattern)：an example of “aliasing” – a sampling error
  ![](./Image/Rasterization_Jaggies.png)
  - 空间上Signals are changing too frequent (high frequency), but sampled too slowly
- Moiré Patterns in Imaging 摩尔纹
  ![](./Image/Rasterization_MoirePattern.png)
- Wagon Wheel Illusion (False Motion)：倒着转的轮子
  - `采样速度跟不上样本变化速度`
  - 时间上Signals are changing too fast (high frequency), but sampled too slowly
- ……


**Antialiasing Today**
- No free lunch!
  - MSAA：每个像素多次采样，求平均。太浪费性能
  - 优化：不使用均匀分布，采样复用
  - 怎样分布样本才能达到最好的覆盖效果：Blue Noise?
- Milestones：目前得到广泛应用
  - FXAA (Fast Approximate AA)：先获得有锯齿的图，再后处理去除锯齿（很快）
    - 找到边界，换成没有锯齿的边界，（图像匹配）非常快
    - 方法和采样无关，采样虽然有误，但是这种方法可以弥补
  - TAA (Tem‘poral AA) ：时序信息，借助前面帧的信息
    - 最近刚刚兴起
    - 静态场景，相邻两帧同一像素用不同的位置来sample
    - 把MSAA的Sampling分布在时间上
    - 运动情况下怎么办？
- Super resolution / super sampling 超分辨率
  - From low resolution to high resolution
  - Essentially still “not enough samples” problem 类似抗锯齿
  - DLSS (Deep Learning Super Sampling) 猜

Visibility / Occlusion

## 深度缓存 Z-buffer

Painter's Algorithm：由远及近画画，覆盖

- 深度计算与排序：O(nlogn)
- 可能有无法排序的情况：例如三个三角形互相重叠

Z-buffer：对每个像素多存一个深度

- 实际coding中，(smaller z -> further, larger z -> closer)

![Z-buffer_Algorithem](./Image/Z-buffer_Algorithem.png)

复杂度：O(n) for n triangles 并不是排序，而是只要最值

需要保证三角形进入顺序和结果无关

无法处理透明物体





参考资料：

[形象展示傅里叶变换]: 可以参考我渲染数学篇的傅里叶变换内容。

[games101_06_Reasterization](https://www.bilibili.com/video/BV1X7411F744?p=6&share_source=copy_web&vd_source=e84f3d79efba7dc72e6306f35613222e)
