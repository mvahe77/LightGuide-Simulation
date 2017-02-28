{
  gStyle->SetOptFit(1);
  TVirtualFitter::SetMaxIterations( 100000 ); 
  TCanvas *cc = new TCanvas("cc","",200,10,700,900);
  cc->Divide(1,2);
  cc->cd(1);
  TFile *f1 = new TFile("WLS_3.81.root");
  TFile *f2 = new TFile("WLS_48.8.root");

  TTree *T1 = f1->Get("T");
  TTree *T2 = f2->Get("T");

  TH1F *h1t = f1->Get("hSPETime");
  TH1F *h2t = f2->Get("hSPETime");

  TH1F *h1cl = (TH1F*)h1t->Clone("h1cl");
  TH1F *h2cl = (TH1F*)h2t->Clone("h2cl");

  double ymaximum = 1.3 * h1cl->GetMaximum();

  h1t->GetYaxis()->SetRangeUser(0,ymaximum);
  h1t->SetStats(0);
  h1t->GetXaxis()->SetTitle("Time (ns)");
  h1t->SetTitle("PMT time distribution");

  h1t->SetLineColor(2);
  h2t->SetLineColor(4);

  TF1 *ff  = new TF1("ff" ,"gaus(0)*pol9(3)",2.3,10.0);
  TF1 *ff1 = new TF1("ff1","gaus(0)*pol9(3)",3.2,10.0);
  double par1[] = { 1.61013e+01,-5.30767e+01,9.66258e+00,-1.45019e+08,1.80096e+08,
		    -6.20926e+07,-3.89193e+06,6.43412e+06,-9.58068e+05,5.17956e+04,
		    0.1, 0.1, 0.1 };
  
  ff->SetParameters(par1);

  //  ff->SetParLimits(0,0.0,30000.0);
  //  ff->SetParLimits(1,2.0,100.0);
  //  ff->SetParLimits(2,0.,10.0);

  double par2[] = { 1.98570e+02,-6.04156e+01,1.04059e+01,-4.66221e+08,3.41201e+08,
		    -5.09074e+07,-1.72203e+07,6.27158e+06,-6.59013e+05,2.60540e+04,
		    0.1, 0.1, 0.1 };

  ff1->SetParameters(par2);

  //  ff1->SetParLimits(0,0.0,30000.0);
  //  ff1->SetParLimits(1,2.0,109.0);
  //  ff1->SetParLimits(2,0.,200.0);

  h1t->Fit("ff" ,"F","", 2.2, 15.0);
  h2t->Fit("ff1","","" , 3.2 ,15.0);

  double half_max1 = ff ->GetMaximum()/2.0;
  double half_max2 = ff1->GetMaximum()/2.0;

  double up_lim1 = ff ->GetMaximumX();
  double up_lim2 = ff1->GetMaximumX();

  cout << half_max1 << "  " << half_max2 << " " << up_lim1 << " " << up_lim2 << endl;

  double time1 = ff ->GetX( half_max1 , 2.0 , up_lim1);
  double time2 = ff1->GetX( half_max2 , 3.0 , up_lim2);

  h1t->GetXaxis()->SetRangeUser(0.0,30.0);
  h1t->Draw();
  h2t->Draw("same");

  cout << time1 << "  " << time2 << endl;

  double dt = time2 - time1;
  double dx = (48.895 - 3.81)/100.0;

  cout << "Speed = " << dx/(dx+0.3*dt) << endl;
  double speed = dx/(dx+0.3*dt);

  TLegend *leg = new TLegend( 0.54 , 0.7 , 0.95 , 0.87 );
  leg->SetTextSize(0.035);
  leg->AddEntry( h1t , "Scin to PMT distance  4.81 cm" , "L");
  leg->AddEntry( h2t , "Scin to PMT distance 48.89 cm" , "L");
  leg->Draw();

  TLatex *tex = new TLatex( 0.5 , 0.5 , Form( "Light speed in WLS: %5.3fc" , speed) );
  tex->SetNDC();
  tex->Draw();

  TLine *l1 = new TLine(up_lim1,0.0,up_lim1,ymaximum);
  l1->Draw();

  TLine *l2 = new TLine(up_lim2,0.0,up_lim2,ymaximum);
  l2->Draw();
  TArrow *arrow = new TArrow(up_lim1,7612.732,up_lim2,7612.732,0.02,"<>");
  arrow->SetFillColor(1);
  arrow->SetFillStyle(1001);
  arrow->SetLineWidth(2);
  arrow->SetAngle(49);
  arrow->Draw();

  tex = new TLatex(5.0,8196.287,"#Delta t = 1.5 ns");
  tex->SetLineWidth(2);
  tex->Draw();


  /////////////////////////////////////////////////////////////////////////
  
  h1cl->SetLineColor(2);
  h2cl->SetLineColor(4);
  h1cl->GetXaxis()->SetRangeUser(0.0,16.0);

  TF1 *ff2  = new TF1("ff2" ,"gaus(0)+pol6(3)",2.3,3.5);
  TF1 *ff3 = new TF1("ff3","gaus(0)+pol6(3)",3.2,5.5);

  //  h1cl->Fit("pol1","","",2.1, 2.5);
  //  h2cl->Fit("pol1","","",3.3, 4.3);


  
  cc->cd(2);
  //  h1cl->SetLineColor();

  double time3 = 2.35909301685587725;
  double time4 = 3.73713695554503467;

  double scale = ff->Eval(up_lim1)/ff1->Eval(up_lim2);
  h2cl->Scale(scale);

  h1cl->GetXaxis()->SetRangeUser(1.0,30.0);
  h1cl->GetYaxis()->SetRangeUser(0,ymaximum);

  h1cl->GetXaxis()->SetTitle("Time (ns)");
  h1cl->SetTitle("Light speed in WLS using half of full pulse-height");
  
  h1cl->SetStats(0);
  h2cl->SetStats(0);
  h1cl->Draw();
  h2cl->Draw("same");

  TArrow *arrow1 = new TArrow(time3,ff->Eval(up_lim1)/2,time4,ff->Eval(up_lim1)/2,0.02,"<>");
  arrow1->SetFillColor(1);
  arrow1->SetFillStyle(1001);
  arrow1->SetLineWidth(2);
  arrow1->SetAngle(49);
  arrow1->Draw();

  TLine *l3 = new TLine(time3 , 0.0 , time3 , ymaximum);
  TLine *l4 = new TLine(time4 , 0.0 , time4 , ymaximum);
  l3->Draw();
  l4->Draw();

  tex = new TLatex( 4.3 , 4800.287 ,"#Delta t = 1.5 ns");
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex( 0.5 , 0.8 , "Light speed in WLS: 0.50c" );
  tex->SetNDC();
  tex->Draw();  
  tex = new TLatex( 0.65 , 0.45 , Form("Scale factor %4.2f" , scale) );
  tex->SetNDC();
  tex->SetTextColor(4);
  tex->Draw();  


  cc->Print("wls_light_speed.ps");
}
