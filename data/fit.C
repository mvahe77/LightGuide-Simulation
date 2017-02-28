{
  TVirtualFitter::SetMaxIterations( 10000 );

  TFile ff("WLS_3.81.root");
  
  TF1 *f1 = new TF1("f1","(pol9(0))*expo(10)");

  double params [] = { -2.29775e+04,5.27883e+04,-4.38974e+04,1.72979e+04,-3.22397e+03,3.43319e+02,
		       -2.16062e+01,7.91150e-01,-1.55058e-02,-1.55058e-02,1.25534e-04,-4.78412e+00		       
  };

  //  double params[] = {1.42375e+01,-7.16803e-02,1.42363e+01,-7.16687e-02,-4.78215e+03,-4.07857e+00,-4.07914e+00};

  f1->SetLineColor(2);
  f1->SetParameters(params);
  
  hSPETime->Fit("f1" , "" , "" , 1.0 , 25.0 );

  f1->SetRange( 2 , 60 );
  f1->Draw("same");

  double max   = f1->GetMaximum();
  double max_x = f1->GetX(max);

  double f1_10percent = max * 0.1;
  double f1_90percent = max * 0.9;
  
  double fval90 = f1->GetX( f1_90percent , 0.0 ,  max_x );
  double fval10 = f1->GetX( f1_10percent , 0.0 ,  max_x );
  
  cout << "Rise time = " << fval90 - fval10 << endl;

  TLine l1( 0.0 , f1_10percent , fval10 , f1_10percent );
  l1.Draw();
  TLine l2( 0.0 , f1_90percent , fval90 , f1_90percent );
  l2.Draw();

  double f1_50percent_min = f1->GetX( max/2.0 , 2.0   ,  max_x );
  double f1_50percent_max = f1->GetX( max/2.0 , max_x ,  60.00 );
  double tdiff = f1_50percent_max - f1_50percent_min;

  cout << "Half width = " << f1_50percent_max - f1_50percent_min  << endl;

  TLine l3( 0.0 , max/2.0 , 60.0 , max/2.0);
  //  l3.Draw();

  TArrow *arrow = new TArrow( f1_50percent_min , max/2.0 , f1_50percent_max , max/2.0 , 0.04 , "<|>");
  arrow->SetFillColor(1);
  arrow->SetFillStyle(1001);
  arrow->SetAngle(30);
  arrow->Draw();

  TLatex *tex = new TLatex( 7.0 , max/2*0.7 , Form( "FWHM = %4.1f ns", tdiff ) );
  tex->Draw();
  hSPETime->GetXaxis()->SetRangeUser( 0.0 , 20.0 );
  hSPETime->GetYaxis()->SetRangeUser( 0.0 , max*1.3 );

  TArrow *arrow1 = new TArrow( fval10 , f1_10percent , fval10 , f1_90percent , 0.04 , "<|>");
  arrow1->SetFillColor(1);
  arrow1->SetFillStyle(1001);
  arrow1->SetAngle(30);
  arrow1->Draw();
  
  tex = new TLatex( 0.5 , max*1.1 , Form( "Rise time = %4.1f ns", fval90 - fval10 ) );
  tex->Draw();


}
