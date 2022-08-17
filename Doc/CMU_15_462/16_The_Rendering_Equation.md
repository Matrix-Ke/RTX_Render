#! https://zhuanlan.zhihu.com/p/545564030
# 从BSDF散射模型建立渲染方程 The Rendering Equation
### prerequisite 
理解radiance和irradiance
什么是irradiance ？
总结：
  - radiance 可以理解为一条光线所携带的能量
  - irradiance 为一个极小面上所有入射光线能量的集合
![](./Image/Radiance_VS_Irradiance.png)
什么是radiance ？ 
* Radiance at point p in direction N is radiant energy (“#hits”) per unit time, per solid angle, per unit area perpendicular to N.
![](./Image/Sphere_Intgration.png)
* **Confusing** : this $\cos\theta$  has to do with parameterization of sphere, not Lambert’s law
* 理解兰伯特$\cos{\theta}$ 与 球面积分$\cos{\theta}$的不同tale of two consines
* 参考[PBRT Working_with_Radiometric_Integrals](https://www.pbr-book.org/3ed-2018/Color_and_Radiometry/Working_with_Radiometric_Integrals)
![](./Image/Lambertlaw_VS_SphereInteration.png)
![](./Image/Irradiance_from_quadrilateral.png)


### 如何使用radince生成图像
**The rendering Equation**
* Core functionality of photorealistic renderer is to estimate radiance at a given point p, in a given direction ωo
* 对渲染方程求和：Summed up by the rendering equation (Kajiya)
![](./Image/Kajiya_rendering_equation.png)
  1. outgoing/observation
  2. incoming radiance 未知 
* 深入理解Rendering Equation： 
> $$
> Lo(\mathbf{p}, \omega_o) = L_e(\mathbf{p}, \omega_o) + \int_{\mathcal{h^2}}f_r(\mathbf{p, \omega_i}\to\omega_o )L_i(\mathbf{p}, \omega_i)(\omega_i\cdot\mathbf{N}(\mathbf{p}))\text{d}\omega_i \\
> $$
* 由于一条光线的radiance输入来自另外一条光线的输出所以需要通过递归方法求解方程 
* Recursive Raytracing
![](./Image/recursively_evaluate_rendering_equation.png)
  - 这就是为什么使用路径追踪而不是光栅化的原因： 光栅化无法递归的得到incoming radiance。
  - 光线来源于光源，其他gometry的reflection
  - 输出结果： **观察方向**的radiance 
* 渲染器用光线路径来计算radiance  Renderer measures radiance along a ray
![](./Image/radiance_traveling_in_Ray.png)

### 光的反射如何影响出射的辐射度 How does refection of light affect the outgoing radiance?

Refection models
![](./Image/Reflection_models.png)
* 反射定义： 光线进入物体表面在相同一侧离开，且频率不改变。 Refection is the process by which light incident on a surface interacts with the surface such that it leaves on the incident (same) side without change in frequency
* 选择什么样的反射方程决定了物理表面什么颜色
$$f_r(\mathbf{p}, \omega_i\to\omega_o)$$

基础的反射函数 Some basic refection functions
**`需要找到一个合适的光线传输模型来表现这些反射现象。`**
![](./Image/Basic_reflection_models.png)

### 根据这些反射函数建立反射模型来

**对物体反射现象建立反射模型：**

* 测量数据：许多真实世界表面的反射分布特性已在实验室进行测量。此类数据可以直接以表格形式使用或用于计算一组基函数的系数。
* 现象学模型：试图描述真实世界表面的定性属性的方程可以非常有效地模仿它们。这些类型的 BSDF 可以特别容易使用，因为它们往往具有修改其行为的直观参数（例如，“粗糙度”）。
* 模拟：有时，关于表面成分的低级信息是已知的。例如，可能知道油漆由悬浮在介质中的某种平均尺寸的有色颗粒组成，或者特定织物由两种类型的线组成，每种线都具有已知的反射特性。在这些情况下，可以模拟来自微观几何形状的光散射以生成反射数据。这种模拟可以在渲染期间完成，也可以作为预处理完成，之后它可以适合一组基函数以在渲染期间使用。
* 物理（波）光学：一些反射模型是使用光的详细模型得出的，将其视为波并计算麦克斯韦方程组的解，以找出它如何从具有已知特性的表面散射。然而，这些模型的计算成本往往很高，并且通常并不比基于几何光学的模型用于渲染应用更准确。
* 几何光学：与模拟方法一样，如果表面的低水平散射和几何特性已知，则有时可以直接从这些描述中推导出封闭形式的反射模型。几何光学使模拟光与表面的相互作用更容易处理，因为可以忽略偏振等复杂的波效应。

BSDF: 向反射分布函数（BRDF）抽象来描述表面的光反射，BTDF 描述表面的透射,BSDF 包含这两种效果。

Models of Scattering
1. 微表面：  Photon_on_surface
   ![](./Image/Photon_on_surface.png)
2. 能量守恒： What goes in must come out! (Total energy must be conserved)
3. 采用BRDF模型： In general, can talk about “probability*” a particle arriving from a given direction is scattered in another direction

Scattering off a surface: 
![](./Image/Torrance_Sparrow_BRDF.png)
* the BRDF(Bidirectional refectance distribution function)
* Encodes behavior of light that “bounces off” surface
* Given incoming direction ωi, how much light gets scattered in any given outgoing direction ωo.
* 表面散射分布描述： $f_r( \omega_i\to\omega_o)$
由以上前提引出brdf概念

**BRDF有如下的两个重要性质**
* Helmholtz互易性： 就是交互入射方向和反射方向，BRDF计算出来的结果是一致的 $f(p, w_i) = f(p, w_o)$
* 能量守恒
* **可以理解brdf为一束入射光的投射到表面$\Delta\mathbf{p}$点光通量与该点某一个观察方向的出射光光通量的比值，BRDF同时满足Helmholtz互异性，对一束入射光的所有反射光比值加总（积分），由能量守恒可知必然$\le1$**
$$
f_r(\omega_i\to\omega_o)\ge0\\
f_r(\omega_i\to\omega_o)=f_r(\omega_o\to\omega_i)\\
\int_{\mathcal{H}^2}f_r(\omega_i\to\omega_o)\cos\theta\ \text{d}\omega_i\le1 \\
$$


BRDF的辐射度描述  Radiometric description of BRDF
![](./Image/Radiometric_description_BRDF.png)
$$
f_r(\omega_i\to\omega_o) = \frac{\text{d}L_o(\omega_o)}{\text{d}E_i(\omega_i)}
=\frac{\text{d}L_o(\omega_o)}{\text{d}L_i(\omega_i)\cos\theta}\left[\frac{1}{sr}\right]\\
$$

**Lambertian Reflection**
* Assume light is equally likely to be refected in each output direction
![](./Image/Lambertian_refection.png)
* 由于各个出射光一样：$ f_r=f_r(\mathbf{p}, \omega_i\to\omega_o)$
> diffuse derivative:
$$
\begin{align*}
f_r(\mathbf{p})&=\frac{\rho(\mathbf{p})}{\pi}\\
L_o(\mathbf{p},\omega_o) &=\int_{\mathcal{H}^2}{f_r(\mathbf{p})L_i(\mathbf{p},\omega_i)\cos\theta}\ \text{d}\omega_i\\
&=f_r(\mathbf{p})\int_{\mathcal{H}^2}{L_i(\mathbf{p},\omega_i)\cos\theta}\ \text{d}\omega_i\\
&=f_r(\mathbf{p})E(\mathbf{p})\\
&=\frac{\rho(\mathbf{p})}{\pi}E(\mathbf{p})\\
\end{align*}\\
$$
> $\rho(\mathbf{p})​$ is albedo, between 0 and 1, because:
$$
0 \le\int_{\mathcal{H}^2}{f_r(\mathbf{p})\cos\theta}\ \text{d}\omega_i\le 1\\
0 \le\frac{\rho(\mathbf{p})}{\pi}\int_0^{2\pi}\int_0^\frac{\pi}{2}          cos\theta\sin\theta\ \text{d}\phi\text{d}\theta\le 1\\
0\le\rho(\mathbf{p})\le 1\\
$$

**perfect specular refection**

![](./image/specular_reflection.png)
* Specular refection BRDF
$$L_o(\theta_o,\phi_o)=L_i(\theta_i,\phi_i)\\$$

菲涅耳方程给出了反射光的比例$F_r(\omega_r)$, 使用Dirac delta 函数`将入射方向限制为镜面反射方向`: 
$$f_{\mathrm{r}}(\mathrm{p},\omega_{0},\omega_{\mathrm{i}})=F_{\mathrm{r}}(\omega_{\mathrm{r}}){\frac{\delta(\omega_{\mathrm{i}}-\omega_{\mathrm{r}})}{|\cos\theta_{\mathrm{r}}|}}  \tag{1} \\$$
也可以写成这样：
$$
f_r(\theta_i,\phi_i;\theta_o,\phi_o)=
\begin{cases} 
F_r(\omega_r)\frac{1}{\cos\theta_i}       &      & {\theta_o=\theta_i \text{ and }\phi_i=\phi_o\pm\pi}\\
0     &      & \text{otherwise} \\
\end{cases} \\ 
$$

**TransmissionLight**

* 光穿过介质 refracts:Transmitted angle depends on relative index of refraction of material ray is leaving/entering
* 折射 Snell`s  Law ： 折射率随光的波长而变化。因此，入射光通常在两种不同介质之间的边界沿多个方向散射，这种效应称为色散。
* eg: 人眼视角 Optical manhole
![](./Image/optical_manhole.png)
![](./Image/snells_law.png)
公式具体推导见[SpecularTransmission](https://www.pbr-book.org/3ed-2018/Reflection_Models/Specular_Reflection_and_Transmission#SpecularTransmission)
$$
\begin{align*}
\eta_i\sin\theta_i
&=\eta_t\sin\theta_t\\
\cos\theta_t
&=\sqrt{1-\sin^2\theta_t}\\
&=\sqrt{1-(\frac{n_i}{n_t})^2\sin^2\theta_i}\\
&=\sqrt{1-(\frac{n_i}{n_t})^2(1-\cos^2\theta_i)}  &\left(1-(\frac{n_i}{n_t})^2(1-\cos^2\theta_i)<0)\right)
\end{align*}\\
$$


### 菲涅尔反射 Fresnel reflection

除了反射和透射方向之外，还需要计算反射或透射的入射光的比例。对于物理上准确的反射或折射，这些项与方向有关，不能通过恒定的每表面缩放量来捕获。`菲涅耳方程描述了从表面反射的光量；它们是麦克斯韦方程在光滑表面上的解。`

**菲涅耳方程**： 给定折射率和入射光线与表面法线的夹角，菲涅耳方程指定了材料对入射照明的两种不同偏振态的相应反射率。因为偏振的视觉效果在大多数环境中是有限的，所以在 pbrt中会做出一个常见的假设，即光是非偏振的；也就是说，它相对于光波是随机定向的。有了这个简化的假设，菲涅耳反射率是平行和垂直偏振项的平方的平均值。（关于光的偏振可以观看[光的偏振：圆偏振，线偏振，非偏振光](https://www.bilibili.com/video/BV1Lt411t7Lh?share_source=copy_web&vd_source=e84f3d79efba7dc72e6306f35613222e)）

为了`计算两种(two dielectric media)电介质界面处的菲涅耳反射率，需要知道两种介质的折射率`
$$
r_{\parallel}=\frac{\eta_{\mathrm{t}}\cos\theta_{\mathrm{i}}-\eta_{\mathrm{i}}\cos\theta_{\mathrm{t}}}{\eta_{\mathrm{t}}\cos\theta_{\mathrm{i}}+\eta_{\mathrm{i}}\cos\theta_{\mathrm{t}}}\\
\\[10pt]
r_{\perp}=\frac{\eta_{\mathrm{i}}\cos\theta_{\mathrm{i}}-\eta_{\mathrm{t}}\cos\theta_{\mathrm{t}}}{\eta_{\mathrm{i}}\cos\theta_{\mathrm{i}}+\eta_{\mathrm{t}}\cos\theta_{\mathrm{t}}}\\
$$
其中$r_{\parallel}$是平行偏振光的菲涅耳反射率，$r_{\perp}$是垂直偏振光的反射率， $\eta_i$是入射和$\eta_t$透射介质的折射率，$\omega_i$和$\omega_t$是入射和透射方向.
**对于非偏振光，菲涅耳反射率**为:
$$F_{\mathrm{r}}=\frac{1}{2}(r_{\parallel}^{2}+r_{\perp}^{2})\\$$


导体和电介质之间的折射率（a conductor and a dielectric medium）：
$$
\begin{align*}
r_{\perp}&={\frac{a^{2}+b^{2}-2a\cos\theta+\cos^{2}\theta}{a^{2}+b^{2}+2a\cos\theta+\cos^{2}\theta}}\\
r_{\parallel}&=r_{\perp}\frac{\cos^{2}\theta(a^{2}+b^{2})-2a\cos\theta\sin^{2}\theta+\sin^{4}\theta}{\cos^{2}\theta(a^{2}+b^{2})+2a\cos\theta\sin^{2}\theta+\sin^{4}\theta}\\
a^{2}\,+\,b^{2} & =\,\sqrt{\left(\eta^{2}\,-\,k^{2}\,-\,\mathrm{sin}^{2}\,\theta\right)^{2}\,+\,4\eta^{2}\,k^{2}}\\
\end{align*}\\
$$
是使用复数除法运算计算$\eta+\mathrm{i}k=\bar{\eta}_{\mathrm{t}}/\bar{\eta}_{\mathrm{i}}$相对折射率。但是，通常$\eta_i$是电介质，因此可以使用正常的实数分割.

**Schlick’s approximation**: 真实世界的菲涅尔公式非常复杂，采用简化方法：($R_0 = F_0$)
$$
\begin{align*} R(\theta) &=R_{0}+\left(1-R_{0}\right)(1-\cos \theta)^{5} \\ R_{0} &=\left(\frac{n_{1}-n_{2}}{n_{1}+n_{2}}\right)^{2} \end{align*}\\
$$

利用菲涅尔方程，我们就可以根据不同的反射率画出$F_{\mathrm{r}}$与$\theta_i$的对应关系图,可以看到：
* 大部分电介质（Dielectric）都随着视角增加而反射增加 Many real materials: refectance increases with viewing angle
* conductor导体（比如铜镜），可以发现即使光线垂直于导体表面，但是依旧有90%的光被反射。
![](./Image/Fresnel_reflection.png)
![常见材质F0](./Image/Material_Fresnel_F0_Value.png)
Example : Snell + Fresnel
![](./Image/Snell_and_Fresnel.png)


### 透射分布函数 BTDF 
现在将推导出镜面传输的BTDF。Snell`s Law斯涅尔定律是推导的基础。斯涅尔定律不仅给出了透射光线的方向，而且还可以用来表明当光线在具有不同折射率的介质之间传播时，沿光线的辐射度会发生变化。

![具有不同折射率的介质之间边界处的透射辐射量由两个折射率的平方比缩放。直观地说，这可以理解为辐射的差分立体角由于传输而被压缩或扩大的结果](./Image/Radiance_change_at_refraction.png)

用$\tau$来表示由菲涅耳方程给出的传输到出射方向的入射能量分数，所以$\tau = 1 - F_r(\omega_i)$。那么传输的微分光通量为
$$\mathrm{d}\Phi_{\mathrm{o}}=\tau\mathrm{d}\Phi_{\mathrm{i}}\\$$


如果使用radiance的定义$L=\frac{\mathrm{d}\Phi}{\mathrm{d}\omega\,\mathrm{d}A^{\perp}}$，有:
$$
L_o\cos \theta_o \text{d}A\text{d}\omega_o = \tau(L_i\cos \theta_i \text{d}A\text{d}\omega_i)
$$

将立体角展开为球面角$\text{d}\omega =\sin \theta\ \text{d}\theta \text{d}\phi$，(具体公式推导见[从辐射度量学理解BRDF: Differential solid angle](https://zhuanlan.zhihu.com/p/549572824))有:
$$
L_{\mathrm{o}}\cos\theta_{\mathrm{o}}\,\mathrm{d}A\sin\theta_{\mathrm{o}}\,\mathrm{d}\theta_{\mathrm{o}}\,\mathrm{d}\phi_{\mathrm{o}}=\tau L_{\mathrm{i}}\cos\theta_{\mathrm{i}}\,\mathrm{d}A\sin\theta_{\mathrm{i}}\,\mathrm{d}\theta_{\mathrm{i}}\,\mathrm{d}\phi_{\mathrm{i}} \tag{2}\\
$$

现在可以根据Snell Law 给出关于$\theta$的关系：
$$\eta_{o}\;\mathrm{cos}\,\theta_{o}\;\mathrm{d}\theta_{o}\,=\,\eta_{\mathrm{i}}\;\mathrm{cos}\,\theta_{\mathrm{i}}\,\mathrm{d}\theta_{\mathrm{i}}\\$$

重新排列术语，有:
$$\frac{\cos\theta_{\mathrm{o}}\,\mathrm{d}\theta_{\mathrm{o}}}{\cos\theta_{\mathrm{i}}\,\mathrm{d}\theta_{\mathrm{i}}}\,=\,\frac{\eta_{\mathrm{i}}}{\eta_{\mathrm{o}}}\\$$

将这个关系和斯涅尔定律代入方程（2），然后化简，有
$$L_{\circ}\,\eta_{\mathrm{i}}^{2}\,\mathrm{d}\phi_{\circ}=\tau L_{\mathrm{i}}\,\eta_{\circ}^{2}\,\mathrm{d}\phi_{\mathrm{i}}\\$$

因为$\phi_{\mathrm{i}}=\phi_{\mathrm{o}}+\pi$因此$\mathrm{d}\phi_{\mathrm{i}}=\mathrm{d}\phi_{\mathrm{o}}$ ，有最终的关系： 
$$L_{\mathrm{o}}=\tau L_{\mathrm{i}}\frac{\eta_{\mathrm{o}}^{2}}{\eta_{\mathrm{i}}^{2}}\\$$

与镜面反射的BRDF（1）公式一样，需要分出$\theta_i$项来获得正确的BTDF镜面透射 ： 
$$f_{\mathrm{r}}(\omega_{0},\omega_{\mathrm{i}})=\frac{\eta_{0}^{2}}{\eta_{\mathrm{i}}^{2}}(1-F_{\mathrm{r}}(\omega_{\mathrm{i}}))\frac{\delta(\omega_{\mathrm{i}}-\mathrm{T}(\omega_{0},{\bf n}))}{|\mathrm{cos}\,\theta_{\mathrm{i}}|}\\$$

> $T(\omega_o, n)$是镜面透射方向$\omega_o$穿过与表面法线n的界面产生的镜面透射矢量

### 其他光学现象
**各项异性 Anisotropic refection**
Refection depends on azimuthal angle$\phi$
![](./Image/anisotropic_reflection.png)

**次表面散射 Subsurface scattering**
  Translucent materials: eg: jade skin
![](./Image/Jade_Material.png)
原因：光线出射点与入射点不一致 Visual characteristics of many surfaces caused by light entering at different points than it exits
  - Violates a fundamental assumption of the BRDF
  - Need to generalize scattering model (BSSRDF)： $S(\mathbf{p}_i,\omega_i,\mathbf{p}_o,\omega_o)$

BSSRDF:"Bidirectional Scattering Surface Reflectance Distributed Function
  - Generalization of BRDF; describes exitant radiance at one point due to incident differential irradiance at another point:
$$
L_o(\mathbf{p}_o,\omega_o)=
\int_\mathcal{A}
\int_{\mathcal{H}^2}
{S(\mathbf{p}_i,\omega_i,\mathbf{p}_o,\omega_o)L_i(\mathbf{p_i},\omega_i)\cos\theta}
\ \text{d}\omega_i\text{d}A \\
$$

> compare BRDF: 
$$
L_o(\mathbf{p},\omega_o)=L_e(\mathbf{p},\omega_o) + \int_{\mathcal{H}^2}f_r(\mathbf{p},\omega_i\to\omega_o)L_i(\mathbf{p},\omega_i)\cos\theta \ \text{d}\omega_i \\
$$


### 有什么相对简单的算法能够捕获所有的行为？ 

**The refection equation** 
* Approximate integral via Monte Carlo integration：
* Generate directions $\omega_j$ sampled from some distribution $p(\omega)$ 
* Compute the estimator 
$$
\frac{1}{N}\sum_{j=1}^N\frac{f_r(\mathbf{p},\omega_j\to\omega_r)L_i(\mathbf{p},\omega_j)\cos\theta_j}{p(\omega_j)} \\
$$
* *为了降低方差$p(\omega_j)​$ 应该尽量符合BRDF入射光线分布。 To reduce variance $p(\omega_j)​$ should match BRDF or incident radiance function*

```c++
// Assume:
// Ray ray hits surface at point hit_p
// Normal of surface at hit point is hit_n

Vector3D wr = -ray.d; // outgoing direction
Spectrum Lr = 0.;
for (int i = 0; i < N; ++i) {
    Vector3D wi; // sample incident light from this direction
    float pdf; // p(wi)
    
    generate_sample(brdf, &wi, &pdf); // generate sample according to brdf
    
    Spectrum f = brdf->f(wr, wi);
    Spectrum Li = trace_ray(Ray(hit_p, wi)); // compute incoming Li
    Lr += f * Li * fabs(dot(wi, hit_n)) / pdf;
}
return Lr / N;
```

### 如何确定入射的radiance，how do we solve the full rendering equation? Have to determine incident radiance…
选择合适的入射光线
![](./Image/Render_Equation_Ray.png)
Path tracing : 拆解递归无限光线为逐束递归光线求解，take advantage of special knowledge to break up integration into “easier” components：
* 将渲染方程拆解为直接光照部分和间接光照部分： Partition the rendering equation into direct and indirect illumination ： 
* 采用蒙特卡洛积分去单独计算每部分（束光），Use Monte Carlo to estimate each partition separately 
  - One sample for each 
  - Assumption: 100s of samples per pixel 
* 采用俄罗斯轮盘赌算法：决定要不要继续，避免无线递归下去。Terminate paths with Russian roulette
![](./Image/recursively_evaluate_rendering_equation.png)



**参考资料**

1. [PBRT Reflection_Models](https://www.pbr-book.org/3ed-2018/Reflection_Models)





