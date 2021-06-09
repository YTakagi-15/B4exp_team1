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
TString filename = "./data/sci1001.root";
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

