# leiden-openmp-CPM
[leiden-communities-openmp]的一个 fork 库,目的是实现 Constant Potts Model (CPM) ，使其适应于[Leiden]的生物学建模、聚类与解释。具体而言，重写了[GVE-Leiden]的底层质量函数，使其支持 Constant Potts Model (CPM) 而非原始设置的 Modularity。由于 leiden-open-CPM 是基于多核心的类贪婪算法，因此在2模块的 Intel Xeon Gold 6430 机器上运行时，其速度较`Leidenalg`的 CPM 方式快 ~20 倍，尚未实施标准化 benchmarking。

A fork of [leiden-communities-openmp] meant to implement the Constant Potts Model (CPM) for applications in biological modeling, clustering, and interpretation of [Leiden]. Rewrote the underlying quality function of [GVE-Leiden] to support the Constant Potts Model (CPM) instead of the original Modularity setting. Since leiden-open-CPM is based on a multi-core quasi-greedy algorithm, it runs ~20 times faster than the CPM implementation in Leidenalg when executed on a dual-socket Intel Xeon Gold 6430 machine. Standardized benchmarking has not yet been performed.

Usage:
``` bash
g++ -std=c++17 -O3 -fopenmp -Iinc main.cxx -o leiden-omp
./leiden-omp ~/edges.mtx 0 1 1.3 1

```

[leiden-communities-openmp]:https://github.com/puzzlef/leiden-communities-openmp
[Leiden]:https://www.nature.com/articles/s41598-019-41695-z
[GVE-Leiden]:https://doi.org/10.1145/3673038.3673146
