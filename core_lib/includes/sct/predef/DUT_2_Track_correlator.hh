#ifndef DUT_2_Track_correlator_h__
#define DUT_2_Track_correlator_h__


#include "sct/predef/plane.hh"
#include "sct/lagacy/xml_input_file.hh"
#include "sct/processor_prob.hh"
#include <string>
#include "sct/internal/factory.hh"
#include "sct/lagacy/setup_description.hh"

#define registerDUT_2_Track_correlator(ClassTypeName, name) registerClass(DUT_2_Track_correlator,ClassTypeName,name)

class DllExport D2T_prob {
public:
  D2T_prob();
  D2T_prob& set_trueHits(const xy_plane& trueHits_);
  D2T_prob& set_DUTHits(const xy_plane& DUT_hits);
  D2T_prob& set_xmlFile( XML_imput_file* xml_file_);
  D2T_prob& set_processor_pro(const processor_prob& pprob);
  D2T_prob& set_gear(Xgear* gear_);
  Xgear*    get_gear() const;
  processor_prob get_processor_pro() const;
  xy_plane get_trueHits() const;
  xy_plane get_DUT_Hits() const;
  XML_imput_file* get_xmlFile() const;

private:
  Xgear* m_gear;
  xy_plane m_DUT_hits, m_trueHits;
  XML_imput_file* m_xml_file_;
  processor_prob m_prob;
};

class DllExport DUT_2_Track_correlator {
public:
  using MainType = std::string;
  using Parameter_t = D2T_prob;
  using Parameter_ref = D2T_prob&;
  DUT_2_Track_correlator(Parameter_ref param_);
  virtual xy_plane getResidual() = 0;
  virtual xy_plane getResidualVsMissing() = 0;
  virtual xy_plane getTotalTrueHits() = 0;
  virtual xy_plane getTrueHitsWithDUT() = 0;
  virtual xy_plane getDUT_Hits() = 0;
protected:
  Parameter_t m_param;
};


DllExport void register_DUT_2_Track_correlator(const DUT_2_Track_correlator::MainType& name, DUT_2_Track_correlator* (fun)(DUT_2_Track_correlator::Parameter_ref param_));
DllExport std::unique_ptr<DUT_2_Track_correlator> create_DUT_2_Track_correlator(DUT_2_Track_correlator::Parameter_ref param_, const DUT_2_Track_correlator::MainType& type);
#endif // DUT_2_Track_correlator_h__