//
//	filename:readtree3check.C
// 	Author:Y.Takagi 
// 	first create:2021/06/07
//	final change:2021/06/07
//
//	no claim, no guarantee, and no responsibility
//	note:for(get tan theta) and draw histogram
//


void readtree3check(){

//load .root file-channel as ttree
TString filename = "./sci1001.root";
TString name = "tree";
TFile *fin = new TFile(filename,"read");
TTree *t = (TTree*)fin->Get(name);

//prepare to draw
TCanvas *c2  = new TCanvas("c2","c2",0,0,600,400);
//TH2F *f1 = new TH2F("f1","title; X; Y",4,0,4,8,0,8);//2d color plot
//Int_t n;
TH1D *f2 = new TH1D("f2","title",100,-10,10);

Int_t totentry = t->GetEntries();
cout << "entry number:" << totentry << endl;
for(Int_t entry_no = 0; entry_no < totentry; entry_no++){

	Int_t High[64];//variable to save VadcHigh(0~63)
	t->SetBranchAddress("VadcHigh",High);//set VadcHigh->High
	t->GetEntry(entry_no);//do
	Int_t m = 0;
		for(Int_t i = 0;i <= 31;i++){
			if(High[i] > 1000)m++;}
		if(m <= 1)continue; 
	//prepare to get tan theta
	TGraph *f1 = new TGraph();//2d color plot
	f1->SetMarkerColor(kRed);
	f1->SetMarkerStyle(21);
	TF1 *func = new TF1("","[0]+[1]*x");
	

	Int_t j = 0;
	for(Int_t i = 0;i <= 31;i++){
		if(High[i] > 1000){
			f1->SetPoint(j,i%4+0.5,7-i/4+0.5);
		//for(int j = 0; j <= High[i];j++){
			//f1->Fill(i%4,7-i/4);
		j++;
					//cout << j;
		}
	}
	f1->Fit(func,"Q");
		//cout << func->GetParameter(1) << endl;
	double_t x = func->GetParameter(1);
	if(x > 4)f1->Draw("AP");
	f2->Fill(x);
}
//f2->Draw("hist");
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
