# Light Transport: Surface Reflection

### Overview 
散射方程 ；它的值可以用蒙特卡洛估计：
$$
\begin{aligned}
L_{\mathrm{o}}\left(\mathrm{p}, \omega_{\mathrm{o}}\right) &=\int_{\mathrm{S}^{2}} f\left(\mathrm{p}, \omega_{\mathrm{o}}, \omega_{\mathrm{i}}\right) L_{\mathrm{i}}\left(\mathrm{p}, \omega_{\mathrm{i}}\right)\left|\cos \theta_{\mathrm{i}}\right| \mathrm{d} \omega_{\mathrm{i}} \\
& \approx \frac{1}{N} \sum_{j=1}^{N} \frac{f\left(\mathrm{p}, \omega_{\mathrm{o}}, \omega_{j}\right) L_{\mathrm{i}}\left(\mathrm{p}, \omega_{j}\right)\left|\cos \theta_{j}\right|}{p\left(\omega_{j}\right)}
\end{aligned}
$$

从具有 PDF分布的立体角$p(\omega_j)$中采样的$\omega_j$方向。在实践中，我们希望从近似于 BSDF 的分布中抽取一些样本，从近似于光源入射辐射的分布中抽取一些样本，然后使用多重重要性采样对样本进行加权。 


