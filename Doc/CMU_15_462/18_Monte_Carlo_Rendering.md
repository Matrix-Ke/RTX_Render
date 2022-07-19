# Monte Carlo Rendering
### Photorealistic Rendering
渲染一张真实感图片需要： 
1. camera
2. geometry
3. material
4. lights
![](./Image/Photorealistic_Scene_Combine.png)

### Monte Carlo Ray Tracing
* 在渲染方程中使用蒙特卡洛积分：To develop a full-blown photorealistic ray tracer, will need to apply Monte Carlo integration to the rendering equation 
* 对输入光线进行积分决定每一个像素的着色：To determine color of each pixel, integrate incoming light 
* 对什么函数进行积分：What function are we integrating? 
   - illumination along different paths of light 
* What does a “sample” mean in this context? 
   - ==每条光线路径就是一个采样==  each path we trace is a sample

**思考**
1. 利用均匀分布随机变量去采样
2. 预期得到什么数值： EXPECTED VALUE — what value do we get on average?
3. 如何减少方差： VARIANCE —what’s the expected deviation from the average?
4. 如何让每次采样更有效： IMPORTANCE SAMPLING — how do we (correctly) take more samples in more important regions?

**Expected Value**