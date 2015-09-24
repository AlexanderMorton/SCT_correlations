#include "TError.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "s_plot_collection.h"
#include "TFile.h"
#include "s_file_base.h"
#include "sct_processors.h"
#include "TBrowser.h"
#include <iostream>
#include <thread>




#include "s_cuts.h"
#include "TH2.h"
#include "SCT_helpers.h"

#include "TProfile.h"




std::vector<TCanvas*> gCanvas;
TBrowser* gBrowser = NULL;


using namespace std;


void remove_root_printouts() {
  gErrorIgnoreLevel = kError;  // ignoring root printouts (replace of histograms) 
}

struct  inParam {
  int argc;
  char **argv;
};



int asyncMain(void *arg) {
  inParam* para = static_cast<inParam *>(arg);
  int argc = para->argc;
  char **argv = para->argv;
  TApplication theApp("App", &argc, argv);
  TFile * file_ = new TFile("D:/alibava/dutTree_350V_sct.root");
  TFile * out_file = new TFile("output.root", "recreate");

  r_plot_collection pl(file_);
  pl.setOutputFile(out_file);
  s_alibava_file file___(pl.get_plot_collection_ptr());

  TH2D h2("h2", "h2", 100, 0, 0, 100, 0, 0);
  auto local_ = sct_processor::coordinate_transform(file___.DUT_fitted_local_GBL(), 1 / 0.0763636, +60.6567 + 3.73549, 1, 0);
  auto corr = sct_processor::correlation(file___.Alibava_sz_data().getX_def(), local_.getX_def());
  auto res = sct_processor::residual(file___.Alibava_sz_data().getX_def(), local_.getX_def());

  auto res1 = sct_processor::residual_with_charge(file___.Alibava_sz_data(), local_,true,"entire_cluster");

  auto res2 = sct_processor::hitmap(res1.getX_def(), res1.getCharge_def());
  auto res_missing = sct_processor::hitmap(res1.getX_def(), res1.getY_def());


  auto max_strip = sct_processor::residual_with_charge(file___.Alibava_sz_data(), local_,false,"Leading_strip");

  auto max_strip_ = sct_processor::hitmap(max_strip.getX_def(), max_strip.getCharge_def());

  auto clusterVSMaxStrip = sct_processor::correlation(res1.getCharge_def(), max_strip.getCharge_def());

  pl.loop();




  new TCanvas();
  pl.Draw(clusterVSMaxStrip, S_DrawOption().draw_y_VS_x());

  new TCanvas();

  TH1D h1("h1", "h1", 100, 0, 500);
  //TH2D h3("h3", "h3", 100, -4,4 ,100,0,1.5);
  pl.Draw(res2, S_DrawOption().draw_y());
  pl.Draw(max_strip_, S_DrawOption().draw_y().opt_same());

  //SCT_helpers::saveTH1_as_txt(h1, "all_cluster.txt");


  new TCanvas();
  pl.Draw(max_strip_, S_DrawOption().draw_x());
  pl.Draw(res, S_DrawOption().draw_x().opt_same());

  new TCanvas();

  pl.Draw(corr, S_DrawOption().draw_y_VS_x().opt_colz().output_object(&h2));

  auto p=SCT_helpers::LinearFit_Of_Profile(&h2,0.5);
  h2.Draw("samecolz");
  p.Draw("same");
  std::cout << p.GetParameter("p1") << std::endl;
  std::cout << p.GetParameter("p0") << std::endl;
  new TCanvas();
  pl.Draw(res, S_DrawOption().draw_x());

  gBrowser = new TBrowser();
  theApp.Run();

  exit(0);
  return 0;
}
int main(int argc, char **argv) {

  remove_root_printouts();






  inParam para;
  para.argc = argc;
  para.argv = argv;

  std::cout << "press q to quit the program" << std::endl;
  std::thread thr(asyncMain, &para);
  thr.detach();
  std::string i;

  while (i != "q") {
    std::cin >> i;

  }


  return 0;

}
