//
//	filename:readtree4check.C
// 	Author:Y.Takagi
// 	first create:2021/06/07
//	final change:2021/06/07
//
//	no claim, no guarantee, and no responsibility
//	note:for(get tan theta) and draw histogram on pi
//	CAUTIOON!!!!! this is not proper on plotting!!!!!!!
//

void readtree4check()
{

	const Int_t bin_num_x = 4;
	const Int_t bin_num_y = 8;
	const double_t bin_reg = 0.001; //to fit solid unti
	const Int_t threshold = 1100;
	const Int_t half_pi = 3.1415 / 2;
	double_t x;
	double_t y;

	//load .root file-channel as ttree
	TString filename = "./data/sci1003.root";
	TString name = "tree";
	TFile *fin = new TFile(filename, "read");
	TTree *tree = (TTree *)fin->Get(name);

	//prepare to draw
	TCanvas *c2 = new TCanvas("c2", "c2", 0, 0, 600, 400);
	TH1D *hist = new TH1D("", "", 100, -2, 2);
	

	Int_t totentry = tree->GetEntries();
	cout << "total entry:" << totentry << endl;
	for (Int_t entry_no = 0; entry_no < totentry; entry_no++)
	{
		Int_t High[64];		  //variable to save VadcHigh(0~63)
		tree->SetBranchAddress("VadcHigh", High); //set VadcHigh->High
		tree->GetEntry(entry_no);				  //do
		Int_t m = 0;
		for (Int_t i = 0; i <= bin_num_x * bin_num_y; i++)
		{
			if (High[i] > threshold)
				m++;
		}
		if (m < 1)continue;
		//prepare to get tan theta
		TGraph *f1 = new TGraph(); //2d color plot
		f1->SetMarkerColor(kRed);
		f1->SetMarkerStyle(21);
		TF1 *func = new TF1("", "[0]+[1]*x");

		Int_t j = 0;
		for (Int_t i = 0; i <= 31; i++)
		{
			if (High[i] > threshold)
			{
				f1->SetPoint(j, i % bin_num_x + bin_reg * j + 0.5, bin_num_y - i / bin_num_x + 0.5);
				//for(int j = 0; j <= High[i];j++){
				//f1->Fill(i%4,7-i/4);
				j++;
				//cout << j;
			}
		}
		f1->Fit(func, "Q");
		x = atan(func->GetParameter(1));
		//if(entry_no % 14 == 0)cout << entry_no <<"\t"<< x << endl;

		if (x <= 0)
		{
			y = x + half_pi;
		}
		else
		{
			y = x - half_pi;
		}
		hist->Fill(y);
		//f1->Draw("AP");int kkkkk;
		//cin >> kkkkk;
	}
	hist->Draw();
}
/*s
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
