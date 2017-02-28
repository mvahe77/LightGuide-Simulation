{
  TFile *f1  = new TFile("WLS_3.810.root");
  TFile *f2  = new TFile("WLS_6.816.root");
  TFile *f3  = new TFile("WLS_9.821.root");
  TFile *f4  = new TFile("WLS_12.827.root");
  TFile *f5  = new TFile("WLS_15.833.root");
  TFile *f6  = new TFile("WLS_18.838.root");
  TFile *f7  = new TFile("WLS_21.844.root");
  TFile *f8  = new TFile("WLS_24.850.root");
  TFile *f9  = new TFile("WLS_27.855.root");
  TFile *f10 = new TFile("WLS_30.861.root");
  TFile *f11 = new TFile("WLS_33.867.root");
  TFile *f12 = new TFile("WLS_36.872.root");
  TFile *f13 = new TFile("WLS_39.878.root");
  TFile *f14 = new TFile("WLS_42.884.root");
  TFile *f15 = new TFile("WLS_45.889.root");
  TFile *f16 = new TFile("WLS_48.895.root");

  TH1F *h1t  = f1 ->Get("hWLSTIME");
  TH1F *h2t  = f2 ->Get("hWLSTIME");
  TH1F *h3t  = f3 ->Get("hWLSTIME");
  TH1F *h4t  = f4 ->Get("hWLSTIME");
  TH1F *h5t  = f5 ->Get("hWLSTIME");
  TH1F *h6t  = f6 ->Get("hWLSTIME");
  TH1F *h7t  = f7 ->Get("hWLSTIME");
  TH1F *h8t  = f8 ->Get("hWLSTIME");
  TH1F *h9t  = f9 ->Get("hWLSTIME");
  TH1F *h10t = f10->Get("hWLSTIME");
  TH1F *h11t = f11->Get("hWLSTIME");
  TH1F *h12t = f12->Get("hWLSTIME");
  TH1F *h13t = f13->Get("hWLSTIME");
  TH1F *h14t = f14->Get("hWLSTIME");
  TH1F *h15t = f15->Get("hWLSTIME");
  TH1F *h16t = f16->Get("hWLSTIME");

  h1t ->Draw();
  h1t->SetLineColor(2);
  //  h2t ->Draw("same");
  //  h3t ->Draw("same");
  h4t ->Draw("same");
  //  h5t ->Draw("same");
  //  h6t ->Draw("same");
  h7t ->Draw("same");
  //  h8t ->Draw("same");
  //  h9t ->Draw("same");
  h10t->Draw("same");
  //  h11t->Draw("same");
  //  h12t->Draw("same");
  h13t->Draw("same");
  //  h14t->Draw("same");
  //  h15t->Draw("same");
  h16t->SetLineColor(4);
  h16t->Draw("same");


}
