#ifndef Cluster_strip_h__
#define Cluster_strip_h__
#include "sct/predef/plane.hh"
#include "sct/xy_processors/find_nearest_strip.hh"
#include "sct/processor_prob.hh"
#include "TH2.h"
#include "TProfile.h"
#include "sct/platform.hh"
#ifndef __CINT__
#include <memory>
#endif


class DllExport Cluster_strip {
public:
  Cluster_strip(
    const xy_plane& trueHits_with_dut,
    const xy_plane& sz_data,
    double max_cluster_size,
    axis_def search_axis,
    double modulo_,
    processor_prob& plot_prob_ = saveWithRandomName("Cluster_strip__")
    );


  int Draw_ClusterSize();

  xy_plane get_plane();
private:
#ifndef __CINT__


  std::shared_ptr<TProfile> m_profile;
  double m_mod , m_max_cluster_size;
  std::shared_ptr<TH2D> m_cluster_size_hist;
  xy_plane m_cluster_size_vs_pos;
#endif // !__CINT__
};

#endif // Cluster_strip_h__