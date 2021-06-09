//
//	filename:readtree1
// 	Author:Y.Takagi 
// 	first create:2021/06/07
//	final change:2021/06/07
//
//	no claim, no guarantee, and no responsibility
//	
//


void readtree1(Int_t entry_no){

const Int_t bin_num_x = 4;
const Int_t bin_num_y = 8;

//load .root file-channel as ttree
TString filename = "./sci1001.root";
TString name = "tree";
TFile *fin = new TFile(filename,"read");
TTree *t = (TTree*)fin->Get(name);

//prepare to draw
TCanvas *c2  = new TCanvas("c2","c2",0,0,600,400);
TH2F *f1 = new TH2F("f1","title; X; Y",bin_num_x,0,bin_num_x,bin_num_y,0,bin_num_y);//2d color plot



Int_t High[64];//variable to save VadcHigh(0~63)
t->SetBranchAddress("VadcHigh",High);//set VadcHigh->High

	t->GetEntry(entry_no);//do

for(Int_t i = 0;i <= bin_num_y * bin_num_x - 1;i++){

	for(int j = 0; j <= High[i];j++){
		f1->Fill(i%bin_num_x, bin_num_y - 1 - i/bin_num_x);
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
}*/
