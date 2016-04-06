#include "sct/predef/truehitExtractor.hh"
#include "sct/xy_processors/converters.hh"
#include "sct/lagacy/setup_description.hh"
#include "sct/predef/fitterFile.hh"
#include "sct/xy_processors/find_nearest.hh"
#include "sct/processor_prob.hh"

class truehitExtractorMAY15 :public truehitExtractor {
public:
  truehitExtractorMAY15(truehitExtractor::Parameter_ref param_);
  virtual xy_plane get_true_DUT_Hits() ;
  xy_plane m_plane;
};

registerTruehitExtractor(truehitExtractorMAY15, "MAY15");

xy_plane make_connections(truehitExtractor::Parameter_ref param_) {
  auto apix_local = convert_zs_data_to_hits_GBL(
    param_.get_fitterFile()->apix_zs_data(),
    *param_.get_gear()->detector.layer_by_ID(20),
    DontsaveWithRandomName()
    );

  auto apix_global = convert_local_to_global(
    apix_local,
    *param_.get_gear()->detector.layer_by_ID(20),
    DontsaveWithRandomName()
    );


  auto apix_on_DUT = convert_global_to_local(
    apix_global,
    *param_.get_gear()->detector.layer_by_ID(8),
    DontsaveWithRandomName()
    );


  return find_nearest(
    apix_on_DUT,
    param_.get_fitterFile()->DUT_fitted_local_GBL(),
    1, // residual cut x
    1,  // residual cut y
    param_.get_processor_pro()
    ).getHitOnPlaneB();
}

truehitExtractorMAY15::truehitExtractorMAY15(truehitExtractor::Parameter_ref param_) :truehitExtractor(param_),m_plane(make_connections(param_))
{
  
}

xy_plane truehitExtractorMAY15::get_true_DUT_Hits( )
{
  return m_plane;

}