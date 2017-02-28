{
  
  TFile *ff = new TFile("WLS.root");
  
  TCanvas *cc = new TCanvas("cc","",200,10,700,900);
  
  cc->Divide( 1 , 2 );

  cc->Print("wls.ps[");
  
  cc->cd(1);
  
  T->Draw("et>>hEt(100,0,4.0)","","goff");
  
  hEt->SetTitle("Energy deposited in EJ-232 scintilator");
  hEt->GetXaxis()->SetTitle("Deposited energy (MeV)");
  hEt->Draw();

  cc->cd(2);
  T->Draw("npt>>hNp(500,6000,20000)","","goff");  
  hNp->SetTitle("Total number of photons produced in EJ-232");  
  hNp->GetXaxis()->SetTitle("Number of photons");  
  hNp->Draw();

  cc->Print("wls.ps");

  cc->cd(1);
  hEscin->SetTitle("Spectrum of photons produced in EJ-232");
  hEscin->GetXaxis()->SetTitle("Photon wavelength (nm)");  
  hEscin->Draw();

  cc->cd(2);
  hEWLS->SetTitle("Spectrum of wavelength shifted photons");
  hEWLS->GetXaxis()->SetTitle("Photon wavelength (nm)");
  hEWLS->Draw();

  cc->Print("wls.ps");

  cc->cd(1);
  T->Draw("npr>>hNpr(40,0.0,100)","","goff");
  hNpr->SetTitle("Number of photons that reached the PMT");
  hNpr->GetXaxis()->SetTitle("Number of photons");
  hNpr->Draw();

  cc->cd(2);
  T->Draw("td>>hTd(40,0.0,40)","","goff");
  hTd->SetTitle("Photon collection time distribution");
  hTd->GetXaxis()->SetTitle("Time (ns)");
  hTd->Draw();

  cc->Print("wls.ps");

  cc->Print("wls.ps]");
}
