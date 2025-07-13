
 # leiden-openmp-CPM
[leiden-communities-openmp]的一个 fork 库，仅提供支持 Constant Potts Model (CPM) 的 Leiden 算法实现。我们重写了 [GVE-Leiden] 的质量函数，使其采用 CPM 而非最初的 Modularity。在双插槽 Intel Xeon Gold 6430 服务器上，本实现比 `Leidenalg` 的 CPM 方式约快 20 倍，但尚未进行标准化基准测试。
 
推荐的γ值=1.3，此时可获得中粒度的聚类结果。若要获取更细粒度的聚类结果，建议使用1.8~2.0之间的γ值。

A fork of [leiden-communities-openmp] only contains an OpenMP implementation of the Leiden community detection algorithm with Constant Potts Model (CPM) support. Consequently, this fits for biological modeling, clustering, and interpretation of [Leiden]. Rewrote the underlying quality function of [GVE-Leiden] to support the Constant Potts Model (CPM) instead of the original Modularity setting. Since leiden-openmp-CPM is based on a multi-core quasi-greedy algorithm, it runs ~20 times faster than the CPM implementation in `Leidenalg` when executed on a dual-socket Intel Xeon Gold 6430 machine. Standardized benchmarking has not yet been performed.
 
The recommended γ value is 1.3, which yields medium-grained clustering results. For finer-grained clustering, a γ value between 1.8 and 2.0 is suggested.
 
 Usage:
 ``` bash
 g++ -std=c++17 -O3 -fopenmp -Iinc main.cxx -o leiden-omp
 ./leiden-omp ~/edges.mtx 0 1 1.3 1
 
 ```
 
 [leiden-communities-openmp]:https://github.com/puzzlef/leiden-communities-openmp
 [Leiden]:https://www.nature.com/articles/s41598-019-41695-z
 [GVE-Leiden]:https://doi.org/10.1145/3673038.3673146
        
        
        
        
         
         
         
         
         
         
         
         

        
        
        
        
        
        
        
        
