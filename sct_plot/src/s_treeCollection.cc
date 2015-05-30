#include "sct_plots.h"
#include "treeCollection.h"
#include <iostream>
#include "TCanvas.h"









void S_plot_collection::push2Local(const char * name, treeCollection* tree)
{
  local_events[name].m_ID = tree->ID;
  local_events[name].m_x = tree->x;
  local_events[name].m_y = tree->y;
  local_events[name].m_event_nr = &tree->event_nr;
}
bool S_plot_collection::getFromLocal(const char* name, treeCollection* tree)
{
  if (!IsLocalCollection(name))
  {
    return false;
  }

  tree->ID = local_events[name].m_ID;
  tree->x = local_events[name].m_x;
  tree->y = local_events[name].m_y;
  tree->event_nr_pointer = local_events[name].m_event_nr;

  return true;
}
bool S_plot_collection::IsLocalCollection(const char* name)
{
  auto it = local_events.find(name);
  if (it == local_events.end())
  {
    return false;
  }
  return true;
}


void S_plot_collection::resetLocal()
{
  local_events.clear();
}

S_plot_collection::S_plot_collection(TFile* file)
{

  addFile(file);

}


void S_plot_collection::addFile(TFile* file)
{
  m_file.push_back(file);
}

void S_plot_collection::reset()
{
  resetLocal();
  m_planes.clear();
  m_plots.clear();
  m_drawOption.clear();
  m_trees.clear();
}

void S_plot_collection::addPlot(const char* PlotType, const char* name, S_Axis x_axis, S_Axis y_axis)
{
  addPlot(PlotType, name, x_axis, y_axis, S_DrawOption());
}

void S_plot_collection::addPlot(const char* PlotType, const char* name, S_Axis x_axis, S_Axis y_axis, S_DrawOption option)
{
  m_plots.push_back(std::make_pair(name, S_plot(PlotType, name, getAxis_ref(x_axis), getAxis_ref(y_axis))));
  //m_plots[name] std::move(S_plot(PlotType, name, getAxis_ref(x_axis), getAxis_ref(y_axis)));
  m_drawOption[name] = option;
}

void S_plot_collection::addPlot(const char* name, S_plot pl)
{
  m_plots.push_back(std::make_pair(name, std::move(pl)));
  m_drawOption[name] = S_DrawOption();
}

void S_plot_collection::addPlot(const char* PlotType, const char* name, S_plane p1, S_plane p2)
{
  auto p1_pointer = pushPlane(std::move(p1));
  auto p2_pointer = pushPlane(std::move(p2));
  if (p1_pointer && p2_pointer)
  {
    addPlot(name, S_plot(PlotType, name, p1_pointer, p2_pointer));
  }
  else{
    std::cout << "planes not set correctly!! \n";
  }

}

void S_plot_collection::addPlot(S_plot_def plot_def, S_plane p1, S_plane p2)
{
  auto p1_pointer = pushPlane(std::move(p1));
  auto p2_pointer = pushPlane(std::move(p2));

  if (p1_pointer && p2_pointer)
  {
    addPlot(plot_def.m_name.c_str(), S_plot(plot_def, p1_pointer, p2_pointer));
  }
  else{
    std::cout << "planes not set correctly!! \n";
  }
}

void S_plot_collection::addPlot(S_plot_def plot_def, S_Axis x_axis, S_Axis y_axis)
{
  m_plots.push_back(std::make_pair(plot_def.m_name, S_plot(plot_def, getAxis_ref(x_axis), getAxis_ref(y_axis))));
}

void S_plot_collection::Draw()
{
  auto c = new TCanvas();

  c->Divide(m_plots.size(), 1);
  int i = 0;
  for (auto& e : m_plots){
    c->cd(i++);
    Draw(e.first.c_str());
  }
}

Long64_t S_plot_collection::Draw(const char* name)
{
  return Draw(name, m_drawOption[name]);
}

Long64_t S_plot_collection::Draw(const char* name, const S_DrawOption& option)
{
  for (auto &e : m_plots)
  {
    if (e.first == name)
    {
      return  e.second.Draw(option.m_options, option.m_cuts, option.m_axis);
    }
  }
  return 0;
}

void S_plot_collection::loop(Int_t last /*= -1*/, Int_t start /*= 0*/)
{
  if (last == -1)
  {
    last = kMaxInt;
    for (auto & e : m_trees)
    {
      auto l = e.second->GetEntries();
      if (last < kMaxInt && l != last)
      {
        std::cout << "trees must have the same length" << std::endl;


      }
      if (l < last)
      {
        last = l;
      }
    }
  }

  for (Int_t i = start; i < last; ++i)
  {
    for (auto& e : m_trees)
    {
      e.second->GetEntry(i);
    }

    for (auto& current_plot : m_plots){
      current_plot.second.fill();

    }
  }
}

axis_ref* S_plot_collection::getAxis_ref(const S_Axis & axis)
{
  if (axis.m_axis == x_axis_def)
  {
    return getPlane(axis.m_planeID, getCollection(axis.m_collectionName.Data()))->getX();
  }

  if (axis.m_axis == y_axis_def)
  {
    return getPlane(axis.m_planeID, getCollection(axis.m_collectionName.Data()))->getY();
  }

  return nullptr;
}

treeCollection* S_plot_collection::getCollection(const char* name)
{
  for (auto&e : m_trees)
  {
    if (e.first == name)
    {
      return e.second;
    }
  }

  if (IsLocalCollection(name))
  {
    treeCollection* tree_pointer = new treeCollection(name);
    push2Local(name, tree_pointer);
    m_trees.push_back(std::make_pair(std::string(name), tree_pointer));
    return tree_pointer;
  }

  if (m_file.empty())
  {
    std::cout << "file empty" << std::endl;
    return nullptr;
  }
  TTree *collection = NULL;

  for (auto& e : m_file)
  {
    e->GetObject(name, collection);
    if (collection)
    {
      break;
    }
  }



  if (!collection)
  {
    std::cout << "collection not found! Collection name: \"" << name << "\"" << std::endl;
    return nullptr;
  }


  treeCollection* tree_pointer = new treeCollection(collection);
  push2Local(name, tree_pointer);
  m_trees.push_back(std::make_pair(std::string(name), tree_pointer));
  return tree_pointer;

}

S_plane* S_plot_collection::getPlane(double ID, treeCollection* coll)
{
  if (!coll)
  {
    return nullptr;
  }

  m_planes.push_back(std::make_shared<S_plane>(ID, coll));
  return m_planes.back().get();
}

S_plane* S_plot_collection::pushPlane(S_plane pl)
{
  if (!pl.isSetTreeCollectionSet())
  {
    auto pl_pointer = getCollection(pl.getName());
    if (!pl_pointer)
    {
      return nullptr;
    }
    pl.setTreeCollection(pl_pointer);

  }
  m_planes.push_back(std::make_shared<S_plane>(pl));

  return m_planes.back().get();
}


S_treeCollection::S_treeCollection(TTree *tree) :m_tree(new treeCollection(tree))
{

}


Int_t S_treeCollection::GetEntry(Long64_t entry)
{
  if (!m_tree)
  {
    std::cout << "[S_treeCollection] tree not set " << std::endl;
    return -1;
  }
  return m_tree->GetEntry(entry);
}

Int_t S_treeCollection::GetEntries() const
{
  if (!m_tree)
  {
    std::cout << "[S_treeCollection] tree not set " << std::endl;
    return -1;
  }
  return m_tree->GetEntries();
}