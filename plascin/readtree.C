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
TString filename = "./sci1001.root";
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





//
//	file name:totalfit.C
//	author:Y.Takagi 
//	first create:2021/06/03	 
//	final change:2021/06/04
//	
//	usage notion:plz use in the directory has led[datano].root files

#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include<vector>
//plz give me fileno, datachannel
vector<double> totalfit(int nn,int nono){

vector<double> result;
result.push_back(nn);
result.push_back(nono);

int gaus_peak_num = 5;

//load .root file-channel as hist
TString filename = Form("./led%i.root",nn);
TString name = Form("ADC_HIGH_%i",nono);
TFile *fin = new TFile(filename,"read");
TH1D *h = (TH1D*)fin->Get(name);

//search status
//maximum(now,0photon) peak
int max_bin = h->GetMaximumBin();//maximum x
int max_event = h->GetMaximum();//maximum y
int nowcount = max_event;
int nowbin;
	for(int j = max_bin; nowcount >= max_event / 5 ;j++){
	nowcount = h->GetBinContent(j);
	nowbin = j;
	//delete bins with many events
	h->SetBinContent(j,0);
	h->SetBinContent(2 * max_bin - j,0);
	}
			//cout << max_bin << "\t" << max_event << "\t" << nowbin << endl;

//second peak
int second_bin = h->GetMaximumBin();
int second_event = h->GetMaximum();

//bins between 0peakto1peak
int peak_to_peak = second_bin - max_bin;
			//cout << second_bin << "\t" << peak_to_peak << endl;
*/
