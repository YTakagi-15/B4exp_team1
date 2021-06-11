//
//	filename:readtree
// 	Author:Y.Takagi 
// 	first create:2021/06/04
//	final change:2021/06/04
//
//	no claim, no guarantee, and no responsibility
//	
//

void readtree(int ent){
//load .root file-channel as ttree
TString filename = "./data/sci1001.root";
TString name = "tree";
TFile *fin = new TFile(filename,"read");
TTree *t = (TTree*)fin->Get(name);

TCanvas *c2  = new TCanvas("c2","c2",0,0,600,400);
TH2F *f1 = new TH2F("f1","title; X; Y",4,0,4,8,0,8);


Int_t High[64];
t->SetBranchAddress("VadcHigh",High);

	t->GetEntry(ent);

//printf("High:%i\n"/*,inst*/,High[i]);
for(Int_t i = 0;i <= 31;i++){
	for(int j = 0; j <= High[i];j++){
		f1->Fill(3-i%4,i/4);
	}
}

f1->Draw("colz");
}
/*
TString ifn = "./sci1001.root";
TFile *fin = new TFile(ifn,"read");
TTree *tin = (TTree*)fin->Get("tree");

Int_t mode;
Int_t ADC_HIGH_1;
Double_t val[100];
vector<TString> chname;
//for(Int_t i = 0;i < 60;i++){
//chname.push_back(Form("ADC_HIGH_%s",i));
//}
//tin->SetBranchAddress(chname[0], &chname[0]);
tin->SetBranchAddress("ADC_HIGH_1", &ADC_HIGH_1);

 const Int_t N = tin->GetEntries();
 for(Int_t ientry = 0; ientry < N; ientry++){
  tin->GetEntry(ientry);
  printf("ADC_HIGH_1:%f\n",ADC_HIGH_1);
 }
}






