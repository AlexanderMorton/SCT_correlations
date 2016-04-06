#include "sct/predef/plane.hh"

#define  X_DEF "x"
#define  Y_DEF "y"
#define  ID_DEF "ID"

std::vector<std::string> xy_names() {
  std::vector<std::string> ret;
  ret.push_back(X_DEF);
  ret.push_back(Y_DEF);
  ret.push_back(ID_DEF);
  return ret;
}
plane::plane(const generic_plane& pl) :m_plane(pl){

}

plane::plane()
{

}

bool plane::next() {
  return m_plane.next();
}

ProcessorCollection* plane::get_ProcessorCollection() const{
  return m_plane.get_ProcessorCollection();
}

const generic_plane* plane::get_generic_plane()const {
  return &m_plane;
}

generic_plane* plane::get_generic_plane(){
  return &m_plane;
}

xy_plane::xy_plane(const generic_plane& pl) :plane(pl) {
  m_plane.setHitAxisAdress(X_DEF, &Hit->x);
  m_plane.setHitAxisAdress(Y_DEF, &Hit->y);
}

xy_plane::xy_plane()
{

}

hit* xy_plane::get_hit() {
  return Hit.get();
}

axis xy_plane::get_x() const
{
  return m_plane.get_axis(X_DEF);
}

axis xy_plane::get_y() const
{
  return m_plane.get_axis(Y_DEF);
}

FitterPlane::FitterPlane(const generic_plane& pl) :xy_plane(pl) {
  m_plane.setHitAxisAdress(X_DEF, &F_Hit->x);
  m_plane.setHitAxisAdress(Y_DEF, &F_Hit->y);
  m_plane.setHitAxisAdress("chi2", &F_Hit->chi2);
  m_plane.setHitAxisAdress("ndf", &F_Hit->ndf);
  m_plane.setHitAxisAdress("phi", &F_Hit->phi);
  m_plane.setHitAxisAdress("theta", &F_Hit->theta);
}

FitterPlane::FitterPlane()
{

}

hit* FitterPlane::get_hit() {
  return F_Hit.get();
}

fitterHit* FitterPlane::get_fitterHit(){
  return F_Hit.get();
}