#ifndef processor_transform_h__
#define processor_transform_h__
#include "sct/xy_processors/processor_hit2d.hh"
#include "sct/platform.hh"

class processor_transform:public processor_hit2d {
public:
  processor_transform(double x_slope, double x_offset, double y_slope, double y_offset, const axis& x_, const axis& y_, processor_prob& pprob);
  double m_x_slope = 0;
  double m_y_slope = 0;
  double m_x_offset = 0;
  double m_y_offset = 0;
  virtual void processHit(double x, double y) ;
};



#endif // processor_transform_h__