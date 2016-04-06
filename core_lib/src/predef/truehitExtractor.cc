#include "sct/predef/truehitExtractor.hh"
#include "sct/internal/factoryDef.hh"
registerBaseClassDef(truehitExtractor);

truehitExtractor::truehitExtractor(truehitExtractor::Parameter_ref param_) :m_param(param_)
{

}





std::unique_ptr<truehitExtractor> create_truehitExtractor(truehitExtractor::Parameter_ref param_, const truehitExtractor::MainType& type /*= ""*/)
{
  return Class_factory_Utilities::Factory<truehitExtractor>::Create(type, param_);
}



void register_truehitExtractor(const truehitExtractor::MainType& name, truehitExtractor* (fun)(truehitExtractor::Parameter_ref param_))
{
  Class_factory_Utilities::Factory<truehitExtractor>::do_register(name, fun);
}

TH_param::TH_param():m_pprob(saveWithRandomName("truehits_"))
{

}

TH_param& TH_param::set_fitterFile(fitterFile* file_)
{
  m_file = file_;
  return *this;
}

TH_param& TH_param::set_gear(Xgear* gear_)
{
  m_gear = gear_;
  return *this;
}

TH_param& TH_param::set_processor_pro(processor_prob& pprob)
{
  m_pprob = pprob;
  return *this;
}

fitterFile* TH_param::get_fitterFile()
{
  return m_file;
}

Xgear* TH_param::get_gear()
{
  return m_gear;
}

processor_prob& TH_param::get_processor_pro()
{
  return m_pprob;
}