#include "sct/generic_plane.hh"
#include "sct/axis.hh"
#include "TTree.h"
double zero = 0;


std::vector<double> *getAxisByName(const std::string& name,const std::vector<storage>& data) {
  for (auto&e : data) {
    if (e.axisName == name) {
      return e.vec;
    }
  }
  return nullptr;
}

generic_plane::generic_plane(double planeID, std::vector<double> *ID, ProcessorCollection*pc, TTree* tree):plane_id(planeID),m_id(ID),m_pc(pc),m_tree(tree){
 
}

generic_plane::generic_plane(const generic_plane& pl): m_pc(pl.m_pc), m_id(pl.m_id), m_storage(pl.m_storage), plane_id(pl.plane_id),m_tree(pl.m_tree){
  for (auto&e:m_storage){
    e.value = &zero;
  }
 
}

generic_plane& generic_plane::operator=(const generic_plane& pl)  {
  m_pc = pl.m_pc;
  m_id = pl.m_id;
  m_storage = pl.m_storage;
  plane_id = pl.plane_id;
  m_tree = pl.m_tree;
  for (auto&e : m_storage) {
    e.value = &zero;
  }

  return *this;
}

void generic_plane::add_axis(const std::string& axisName, std::vector<double> *axis_) {

  m_storage.push_back(storage( axis_, axisName));
}

bool generic_plane::setHitAxisAdress(const std::string& name, double* outVar) {


  for (auto&e : m_storage) {
    if (e.axisName == name) {
      e.value = outVar;
      m_usedstorage.push_back(e);
      return true;
    }
  }

  return false;
}

bool generic_plane::next() {
  while (++curr < m_id->size()) {
    if (m_id->at(curr) == plane_id){
      for (auto& e : m_usedstorage) {
        *(e.value) = e.vec->at(curr);
      }
      return true;
    }

  }
  curr = -1;
  return false;
}

void generic_plane::push() {
  push(plane_id);
}

void generic_plane::push(double planeID){
  m_id->push_back(planeID);
  for (auto& e : m_storage) {
    e.vec->push_back(*e.value);
  }
}

axis generic_plane::get_axis(const std::string& axisName)const {
  auto axis_ = getAxisByName(axisName, m_storage);
  
 return axis(plane_id,m_id, axisName, axis_, get_ProcessorCollection(),m_tree);

}

ProcessorCollection* generic_plane::get_ProcessorCollection() const{
  return m_pc;
}

TTree* generic_plane::get_tree(){
  return m_tree;
}

double generic_plane::get_ID() const
{
  return plane_id;
}



storage::storage(std::vector<double>* vec_, const std::string& axisName_) :vec(vec_), axisName(axisName_), value(&zero)
{

}
