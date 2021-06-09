//
//	file name:scizero_search.C(cp from:totalfit.C
//	author:Y.Takagi 
//	first create:2021/06/04	 
//	final change:2021/06/04
//	
//	usage notion:plz use in the directory has led[datano].root files

#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include<vector>
//plz give me fileno, datachannel
void scizero_search(){
for(int nn = 10,)
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


//prepare to Draw(cuz h was deleted events some bins)
TFile *fin1 = new TFile(filename,"read");
TH1D *h1 = (TH1D*)fin1->Get(name);
TF1* func[gaus_peak_num];
vector<TString> fitname;
int max[gaus_peak_num];
int min[gaus_peak_num];
int means[gaus_peak_num];

	for(int i = 0;i < gaus_peak_num;i++){
	fitname.push_back(Form("fit%i",i));
	min[i] = 2 * max_bin - nowbin + i * (peak_to_peak - 3);
	max[i] = nowbin + i * (peak_to_peak);
	func[i] = new TF1(fitname[i], "TMath::Gaus(x,[1],[2])*[0]",min[i],max[i]);
	func[i]->SetParameter(0,100-i*20);
	func[i]->SetParameter(1,max_bin + i * peak_to_peak);
	func[i]->SetParameter(2,1);
	func[i]->SetParLimits(2,0,100);
	h1->Fit(func[i],"+","",min[i],max[i]);

	//put out fit result parameter
	cout << i << "\t" << max[i] << "\t"  << min[i] <<endl;
	means[i] = func[i]->GetParameter(1);
	cout << means[i] <<endl;
	
	result.push_back(means[i]);
	result.push_back(func[i]->GetParError(1));

	}


h1->Draw();
return result;

/*
			//write result to txt file
			TString filename1("./fitdatas.txt");
			fstream file_out;
			file_out.open(filename1, ios_base::app);		
			int write_to_file;
			cout << "write?(yes:1 no:0)";
			cin >> write_to_file;
			if(write_to_file == 1){
			if(!file_out.is_open()){cout << "fail to open" << endl;}else{
			file_out << nn << ":\t" << nono << ":\t";
			for(int i = 0;i < gaus_peak_num;i++){
			file_out << means[i] << "\t";}
			file_out << endl << "-------------------------------" << endl;
			}}
*/


}


//　 　　　＿＿＿＿　　 
//　　　／　　 　   ＼ 
//　 ／　　─　 　　 ─ ＼　 
//／ 　　 （●） 　（● ) ＼　
//|　 　　 　 （__人__） |　多分これ光子数増えると壊れるな　 
///　　　　　 ∩ノ ⊃　　／ 　光子数に対してイベントが
//(　＼　／ ＿ノ　|　 | 　　減ってる時しか使えない
//.＼　“　　／＿＿|　 | 　 
//　　＼ ／＿＿＿＿ ／ 　 
//
