#include <TBenchmark.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TStopwatch.h>
#include <TApplication.h>
#include <TH2F.h>
#include <TFile.h>
#include <TSpline.h>
#include <TLatex.h>
#include <TLine.h>
#include <TArrow.h>
#include <TLegend.h>

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <cmath>

using namespace std;

double* GetPulseInfo(TSpline5 *spl);

int main(){

  TFile *f1 = new TFile("WLS_3.810.root");
  if(!f1->IsOpen()) { cerr << "Can't open file WLS_3.810.root" << endl; exit(1);}

  TH1 *h1 = (TH1*)f1->Get("hSPETime");
  h1->SetStats(0);
  TSpline5 *spl1 = new TSpline5(h1);
  h1->SetLineColor(2);
  h1->GetXaxis()->SetRangeUser( 0.0,30.0);
  TH1 *h1cl = (TH1*)h1->Clone("h1cl");

  TFile *f2 = new TFile("WLS_48.895.root");
  if(!f2->IsOpen()) { cerr << "Can't open file WLS_48.895.root" << endl; exit(1);}
  TH1 *h2 = (TH1*)f2->Get("hSPETime");
  h2->SetStats(0);
  TSpline5 *spl2 = new TSpline5(h2);
  h2->SetLineColor(4);
  h2->GetXaxis()->SetRangeUser( 0.0,30.0);
  TH1 *h2cl = (TH1*)h2->Clone("h2cl");

  double *pinfo1 = GetPulseInfo(spl1);
  double *pinfo2 = GetPulseInfo(spl2);

  for(int ii = 0; ii < 6; ii++){
    cout << "D = 3.81 cm : " << pinfo1[ii] << endl;
  }
  for(int ii = 0; ii < 6; ii++){
    cout << "D = 48.8 cm : " << pinfo2[ii] << endl;
  }
  
  cout << "Pulse rise time 10-90 % = " << pinfo1[5]-pinfo1[4] << " ns" << endl;
  cout << "Pulse rise time 10-90 % = " << pinfo2[5]-pinfo2[4] << " ns" << endl;

  //-- Make some plots
  TLatex *tex;
  TCanvas *cc = new TCanvas("cc","",200,10,700,900);
  cc->SetFillColor(0);
  cc->SetBorderMode(0);
  cc->SetFrameBorderMode(0);
  cc->Divide(1,2);
  cc->GetPad(1)->SetFillColor(0);
  cc->GetPad(2)->SetFillColor(0);
  cc->GetPad(1)->SetBorderMode(0);
  cc->GetPad(1)->SetFrameBorderMode(0);
  cc->GetPad(2)->SetBorderMode(0);
  cc->GetPad(2)->SetFrameBorderMode(0);
  
  cc->cd(1);
  h1->Draw();
  h2->Draw("same");
  double ymax = pinfo1[1]*1.2;
  h1->GetYaxis()->SetRangeUser(0.0,ymax);
  h1cl->GetYaxis()->SetRangeUser(0.0,ymax);
  TLine *l1 = new TLine(pinfo1[0],0.0,pinfo1[0],ymax);
  l1->SetLineColor(2);
  l1->Draw();
  TLine *l2 = new TLine(pinfo2[0],0.0,pinfo2[0],ymax);
  l2->SetLineColor(4);
  l2->Draw();

  TArrow *ar1 = new TArrow(pinfo1[0],ymax*0.9,pinfo2[0],ymax*0.9,0.008,"<|>" );
  ar1->SetAngle(40.0);
  ar1->Draw();
  
  double dt = pinfo2[0]-pinfo1[0];
  double dx = (48.895 - 3.81)/100.0;
  double speed = dx/(dx+0.3*dt);
  tex = new TLatex(0.35 , 0.8 , Form("Time: %5.2f ns, speed = %5.3fc" , dt , speed));
  tex->SetNDC();
  tex->Draw();
  //--

  cc->cd(2);
  double scale = pinfo1[1]/pinfo2[1];

  h1cl->GetXaxis()->SetRangeUser( 0.0,20.0);
  h1cl->GetXaxis()->SetTitle("PMT time distribution (ns)");
  h1cl->Draw();
  h2cl->Scale(scale);
  h2cl->GetXaxis()->SetTitle("PMT time distribution (ns)");
  h2cl->Draw("same");
  
  tex = new TLatex(0.35 , 0.3 , Form("Scale factor: %5.2f" , scale) );
  tex->SetNDC();
  tex->SetTextColor(4);
  tex->Draw();

  dt = pinfo2[2]-pinfo1[2];
  speed = dx/(dx+0.3*dt);
  tex = new TLatex(0.35 , 0.2 , Form("Light speed: %5.3f" , speed) );
  tex->SetNDC();
  tex->SetTextColor(4);
  tex->Draw();

  TArrow *ar2 = new TArrow(pinfo1[4],pinfo1[1]*0.1,pinfo1[4],pinfo1[1]*0.9,0.01,"<|>" );
  ar2->SetAngle(40.0);
  ar2->SetLineColor(2);
  ar2->SetFillColor(2);
  ar2->Draw();

  TLine *l3 = new TLine(0.0,pinfo1[1]*0.1,pinfo1[4],pinfo1[1]*0.1);
  l3->SetLineColor(2);
  l3->Draw();
  TLine *l4 = new TLine(0.0,pinfo1[1]*0.9,pinfo1[5],pinfo1[1]*0.9);
  l4->SetLineColor(2);
  l4->Draw();


  TSpline5 *spl3 = new TSpline5(h2cl);
  double *pinfo3 = GetPulseInfo(spl3);

  TLegend *leg = new TLegend( 0.6 , 0.6 , 1.0 , 0.95 );
  leg->AddEntry( h1   , Form( "FWHM: %5.2f ns" , pinfo1[3]-pinfo1[2] ) , "L");
  leg->AddEntry( h2cl , Form( "FWHM: %5.2f ns" , pinfo3[3]-pinfo3[2] ) , "L");
  leg->AddEntry( h1   , Form( "Rise time(10-90%): %5.2f ns" , pinfo1[5]-pinfo1[4] ) , "L");
  leg->AddEntry( h2   , Form( "Rise time(10-90%): %5.2f ns" , pinfo2[5]-pinfo2[4] ) , "L");
  leg->AddEntry( h1   , Form( "Rise time(5-95%): %5.2f ns" , pinfo1[7]-pinfo1[6] ) , "L");
  leg->AddEntry( h2   , Form( "Rise time(5-95%): %5.2f ns" , pinfo2[7]-pinfo2[6] ) , "L");

  leg->Draw();

  cc->Print("pulse.ps");
  // -----------------------------------------------------------------------

  delete [] pinfo1;
  delete [] pinfo2;

  f1->Close();
  f2->Close();
}

double* GetPulseInfo(TSpline5 *spl)
{
  double *plsinfo = new double[8];
  int Np = 10000;
  double minx = spl->GetXmin();
  double maxx = spl->GetXmax();
  
  double dx = (maxx-minx)/Np;
  
  double maxval  = 0.0;
  double maxvalx = -1000.0;

  for(int ii = 0; ii < Np; ii++) {
    
    double xval = minx + dx/2.0 + ii *dx;
    double fval = spl->Eval(xval);
    if( fval > maxval ) { maxval = fval; maxvalx = xval; }
  }
  plsinfo[0]=maxvalx;
  plsinfo[1]=maxval;

  // -- Start finding pulse info after finding the pulse maximum
  //
  double fvalhalf_x = 0.0;
  double mindiff = 10000.0;

  double fvalhalf_x1 = 0.0;
  double mindiff1 = 10000.0;
  
  double fval10percent_x   = 0.0;
  double mindiff_10percent = 10000.0;

  double fval90percent_x   = 0.0;
  double mindiff_90percent = 10000.0;

  double fval5percent_x    = 0.0;
  double mindiff_5percent = 10000.0;

  double fval95percent_x    = 0.0;
  double mindiff_95percent = 10000.0;

  for(int ii = 0; ii < Np; ii++) {    
    double xval = minx + dx/2.0 + ii *dx;
    double fval = spl->Eval(xval);
    double diff = fabs(maxval/2.0-fval);
    if( diff < mindiff && xval < maxvalx) {
      mindiff = diff;
      fvalhalf_x = xval;
    }
    plsinfo[2]=fvalhalf_x;    
    if( diff < mindiff1 && xval > maxvalx) {
      mindiff1 = diff;
      fvalhalf_x1 = xval;
      //      cout << "x-> = " << xval << "" << diff << endl;
    }
    //    cout << "x = " << xval << " " << diff << endl;
    plsinfo[3]=fvalhalf_x1;

    double diff10 = fabs(maxval*0.1-fval);
    if( diff10 < mindiff_10percent && xval < maxvalx) {
      mindiff_10percent = diff10;
      fval10percent_x = xval;
    }
    plsinfo[4]=fval10percent_x;
    double diff90 = fabs(maxval*0.9-fval);
    if( diff90 < mindiff_90percent && xval < maxvalx) {
      mindiff_90percent = diff90;
      fval90percent_x = xval;
    }
    plsinfo[5]=fval90percent_x;
    //------------------------------------------
    double diff5 = fabs(maxval*0.05-fval);
    if( diff5 < mindiff_5percent && xval < maxvalx) {
      mindiff_5percent = diff5;
      fval5percent_x = xval;
    }
    plsinfo[6]=fval5percent_x;

    double diff95 = fabs(maxval*0.95-fval);
    if( diff95 < mindiff_95percent && xval < maxvalx) {
      mindiff_95percent = diff95;
      fval95percent_x = xval;
    }
    plsinfo[7]=fval95percent_x;

  }
  return plsinfo;
}
