{
  TVirtualFitter::SetMaxIterations( 1000000 );

  ifstream fin("bq_waveform_test009_Ch1.txt" , ios::in);

  string line;
  getline( fin , line );
  getline( fin , line );
  getline( fin , line );
  getline( fin , line );
  getline( fin , line );
  getline( fin , line );

  double time, volt;

  TGraphErrors *gr = new TGraphErrors;
  gr->SetMarkerStyle(20);

  int ii = 0;
  int jj = 0;

  while( !fin.eof() ) {
    
    getline( fin , line );  
    
    sscanf( line.c_str() , "%lf %lf" , &time , &volt );

    //    cout << time << "  " << volt << endl;

    if( ii % 30 == 0 ) {
      gr->SetPoint( jj , time*1.0e+9 , -volt + 0.000319208 );
      gr->SetPointError( jj , 0.0 , 0.00001 );
      jj++;
    }
    ii++;
  } 
  gr->Draw("AP");
  //  gr->Fit("pol0","","",-10,-9);

  double params[] = { 
    1.61786e-02,-2.31616e+01,1.43351e+01,
    3.89007e-12,-4.71063e+00,3.00471e+00,
    -1.34416e+09,1.84992e+09,1.47916e+09,3.48123e+08,-1.04271e+08,
    -3.97528e+07,6.71953e+06,4.94831e+05,1.12576e+04,-2.62885e+03
  };
  
  TF1 *ff = new TF1( "ff" , "gaus(0)+gaus(3)*pol9(6)" );
  ff->SetParameters(params);

  ff->SetParLimits(0 , 0.0 , 100000.0 );
  //  ff->SetParLimits(1 , 0.0 , 3.0 );
  //  ff->SetParLimits(2 , 0.0 , 10.0 );
  //  ff->SetParLimits(4 , 0.0 , 100000.0 );
  //  ff->SetParLimits(5 , 0.0 , 100000.0 );

  ff->SetLineColor(2);
 
  //  gr->Fit("ff" , "" , "" , 4.0 , 34.0 );

  TSpline5 *spl = new TSpline5( "spl" , gr );
  spl->SetLineColor(2);
  //  spl->Draw("same");

}
