#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include "inc/main.hxx"
#include "inc/leiden.hxx"

using namespace std;




#pragma region CONFIGURATION
#ifndef TYPE
/** Type of edge weights. */
#define TYPE float
#endif
#ifndef MAX_THREADS
/** Maximum number of threads to use. */
#define MAX_THREADS 128
#endif
#ifndef REPEAT_METHOD
/** Number of times to repeat each method. */
#define REPEAT_METHOD 5
#endif
#pragma endregion




// HELPERS
// -------

template <class G, class R>
inline double getModularity(const G& x, const R& a, double M) {
  auto fc = [&](auto u) { return a.membership[u]; };
  return modularityByOmp(x, fc, M, 1.0);
}


template <class K, class W>
inline float refinementTime(const LeidenResult<K, W>& a) {
  return a.refinementTime;
}




// PERFORM EXPERIMENT (Removed)


int main(int argc, char **argv) {
  using K = uint32_t;
  using V = TYPE;
  install_sigsegv();
  if (argc < 2) {
    cerr << "usage: leiden-omp <matrix.mtx> [sym=0] [weighted=0] "
            "[gamma=0.7] [quality=1 (0=MODULARITY,1=CPM)]\n";
    return 1;
  }
  char *file     = argv[1];
  bool symmetric = argc > 2 ? std::stoi(argv[2]) : 0;
  bool weighted  = argc > 3 ? std::stoi(argv[3]) : 0;
  double gamma   = argc > 4 ? std::stod(argv[4]) : 1.3;
  int    quality = argc > 5 ? std::stoi(argv[5]) : 1;
  omp_set_num_threads(MAX_THREADS);
  LOG("OMP_NUM_THREADS=%d\n", MAX_THREADS);
  LOG("Loading graph %s ...\n", file);
  DiGraph<K, None, V> x;
  readMtxOmpW(x, file, weighted); double m = edgeWeightOmp(x) / 2.0; LOG(""); println(x);

  LeidenOptions opts{};
  opts.repeat               = REPEAT_METHOD;
  opts.useCPM               = (quality == 1);
  opts.resolution           = gamma;
  opts.tolerance            = 1.3;
  opts.aggregationTolerance = 0.8;
  opts.toleranceDrop        = 1;
  opts.maxIterations        = 10;
  opts.maxPasses            = 20;

  if (!symmetric) {x = symmetricizeOmp(x); LOG(""); println(x); printf(" (symmetricize)\n");}

  auto res = leidenStaticOmp(x, opts);

  auto printStats = [&](const auto& r) {
    printf("=== Leiden-%s(γ=%.2f) time（ms） ===\n",
           opts.useCPM ? "CPM" : "Modularity", opts.resolution);
    printf("totaltime: %.1f\n", r.time);
    printf("marking: %.1f\n", r.markingTime);
    printf("init: %.1f\n", r.initializationTime);
    printf("firstpass: %.1f\n", r.firstPassTime);
    printf("local: %.1f\n", r.localMoveTime);
    printf("refine: %.1f\n", r.refinementTime);
    printf("aggregation: %.1f\n", r.aggregationTime);
    printf("===========================================\n");
  };
  printStats(res);

  auto comm = communities(x, res.membership);
  printf("communitynumber = %zu\n", comm.size());
  return 0;
}
