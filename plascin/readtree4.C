//
//	filename:readtree3
// 	Author:Y.Takagi 
// 	first create:2021/06/07
//	final change:2021/06/07
//
//	no claim, no guarantee, and no responsibility
//	note:for(get tan theta) and draw histogram on pi
//


void readtree4(){

const Int_t bin_num_x = 4;
const Int_t bin_num_y = 8;
const Int_t threshold = 1100;
const Int_t on_num = 1;

//load .root file-channel as ttree
TString filename = "./data/sci1003.root";
TString name = "tree";
TFile *fin = new TFile(filename,"read");
TTree *t = (TTree*)fin->Get(name);

//prepare to draw
TCanvas *c2  = new TCanvas("c2","c2",0,0,600,400);
TH1D *f2 = new TH1D("f2","title",100,-2,2);

Int_t totentry = t->GetEntries();
cout << "entry number:" << totentry << endl;
for(Int_t entry_no = 0; entry_no < totentry; entry_no++){

	Int_t High[64];//variable to save VadcHigh(0~63)
	t->SetBranchAddress("VadcHigh",High);//set VadcHigh->High
	t->GetEntry(entry_no);//do
	Int_t m = 0;
		for(Int_t i = 0;i <= bin_num_x * bin_num_y;i++){
			if(High[i] > 1000)m++;}
		if(m <= on_num)continue; 
	//prepare to get tan theta
	TGraph *f1 = new TGraph();//2d color plot
	f1->SetMarkerColor(kRed);
	f1->SetMarkerStyle(21);
	TF1 *func = new TF1("","[0]+[1]*x");
	

	Int_t j = 0;
	for(Int_t i = 0;i <= 31;i++){
		if(High[i] > 1000){
			f1->SetPoint(j,i % bin_num_x + 0.5,bin_num_y - 1 - i/bin_num_x + 0.5);
		j++;
		}
	}
	f1->Fit(func,"Q");
	double_t x = func->GetParameter(1);
	f2->Fill(atan(x));
}
f2->Draw("hist");
}

