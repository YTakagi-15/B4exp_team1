//
//	file name:totalfit.C
//	author:Y.Takagi 
//	first create:2021/06/03	 
//	final change:2021/06/09(add correct parameter for right)
//	
//	usage notion:use in the directory has led[datano].root files
//			if u wanna change the range of fit, plz change xx_correction
//

//plz give me fileno, datachannel
vector<double> totalfit(int nn,int nono){

//vector for return (nn(file number),nono(channel),mean1,mean1error,mean2,....)
vector<double> result;
result.push_back(nn);
result.push_back(nono);

//variables
const Int_t gaus_peak_num = 5;// change this to the number of peaks
const double_t peak_height = 5;
double_t left_correction = 2;//gaus no hani wo hosei suru yo!
double_t right_correction = 0;
double_t center_correction = 0;

//load .root file-channel as hist
TCanvas *c1 = new TCanvas("c1","c1",1000,500);	
TString filename = Form("./led%i.root",nn);
TString name = Form("ADC_HIGH_%i",nono);
TFile *fin = new TFile(filename,"read");
TH1D *h = (TH1D*)fin->Get(name);
h->SetStats(0);


//search status
//maximum(now,0photon) peak
int max_bin = h->GetMaximumBin();//maximum x
int max_event = h->GetMaximum();//maximum y
int nowcount = max_event;
int nowbin;
	for(int j = max_bin; nowcount >= max_event / peak_height ;j++){
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
	min[i] = 2 * max_bin - nowbin + i * (peak_to_peak - left_correction);
	max[i] = nowbin + i * (peak_to_peak);
	func[i] = new TF1(fitname[i], "TMath::Gaus(x,[1],[2])*[0]",min[i],max[i]);
	func[i]->SetParameter(0,100-i*20);
	func[i]->SetParameter(1,max_bin + i * peak_to_peak);
	func[i]->SetParameter(2,1);
	func[i]->SetParLimits(2,0,1000);
	h1->Fit(func[i],"+","",min[i],max[i]);

	//cout fit result parameter
	cout << "↑is No."<< i << "peak's fit data. fit range:" << "\t" << max[i] << "\t~\t"  << min[i] <<endl;
	means[i] = func[i]->GetParameter(1);
	

	result.push_back(means[i]);
	result.push_back(func[i]->GetParError(1));
	}


h1->Draw();
TString graphname = Form("./fitgraph/led%d_%d.gif",nn,nono);
c1->SaveAs(graphname,"gif");
return result;
}
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
