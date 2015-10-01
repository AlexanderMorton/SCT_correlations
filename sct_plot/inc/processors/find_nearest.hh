#ifndef find_nearest_h__
#define find_nearest_h__
#include "plane_def.h"
#include "s_plot_prob.h"

namespace sct_processor {

class find_nearest {
public:
  find_nearest(const sct_corr::plane_def& planeA,
               const sct_corr::plane_def& planeB,
               Double_t x_cutoff,
               Double_t y_cutoff,
               const s_plot_prob& = ""
               );
  sct_corr::plane_def getResidual() const;
  sct_corr::plane_def getHitOnPlaneA() const;
  sct_corr::plane_def getHitOnPlaneB() const;

private:
  s_plane_collection_find_closest m_planes;
};


}

#endif // find_nearest_h__