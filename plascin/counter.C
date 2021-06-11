//
//	file name:counter.C
//	author:Y.Takagi 
//	first create:2021/06/03	 
//	final change:2021/06/05
//	
//	usage notion:plz use in the directory has led[datano].root files
//



//plz give me slope, fileno, datach, zero-peakmean
//vector<int> counter(int slope,int nn,int nono,int zpeak){//usethis when you wanna txt data
vector<int> counter(vector<double> fitdatas){

//change variable name from vector
const double_t slope = fitdatas[0];
const Int_t nn = fitdatas[1];
const Int_t nono = fitdatas[2];
const double_t zpeak = fitdatas[3];

//load .root file and choice histogram which 
TString name = Form("ADC_HIGH_%i",nono);
TString filename = Form("./data/led%i.root",nn);
TFile *fin = new TFile(filename,"read");
TH1D *h = (TH1D*)fin->Get(name);

//set variables
vector<Int_t> countn;//return variable
countn.push_back(fitdatas[1]);
countn.push_back(fitdatas[2]);
Int_t countsum = 0;
Int_t countave = 0;
const Int_t how_many_photons = 8;

//main function
for(int i = 0;i < how_many_photons;i++){
	int max = zpeak + i * slope + slope / 2;
	int min = zpeak + i * slope - slope / 2 ;
	countn.push_back(h->Integral(min,max));
	cout << "No." << i << "peak has:" << "\t" << countn[i] << "\t" << "events." << endl;//cout sum of events of each peak
	countave = countave + countn[i] * i;
	countsum = countsum + countn[i];
	//cout << i << "\t" << countave << endl;
}
	cout << "total peak events:" << countsum << "\t photon average:" << (double)countave / (double)countsum << endl;
	cout << "over " << how_many_photons << " photon events' count:" << h->Integral((int)(zpeak + how_many_photons * slope - slope / 2),-1) << endl;

/*
			//write to txt file
			TString filename1("./data/datas.txt");
			fstream file_out;
			file_out.open(filename1, ios_base::app);		
			int write_to_file;
			cout << "write?(yes:1 no:0)";
			cin >> write_to_file;
			if(write_to_file == 1){
			if(!file_out.is_open()){cout << "fail to open" << endl;}else{
			file_out << nn << ":\t" << nono << ":\t" << countave << "\t/\t" << countsum << "\t=\t" << (double)countave /(double)countsum << endl << "-------------------------------" << endl;
			}}
*/

return countn;
}

