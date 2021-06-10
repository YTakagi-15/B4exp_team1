#include<fstream>
#include<TH1.h>
#include<iostream>
#include<string>
#include<stdio.h>
//#include<vector>
//#include<TGraph>

void tomakelinear(int j){

TGraphErrors* g1 = new TGraphErrors();
ifstream ifs("dotsdata.txt");
	if( !ifs ){
	cerr << "some error occured when load database!" << endl;
	}
double x[3];
double xer[3];
double  y;
int index = 0;
string dummy, dummy2;
getline(ifs,dummy2);
string bufferin;
	while (getline(ifs,bufferin)){
	istringstream buffer(bufferin);
	//cout << bufferin << endl;
		while(buffer >> dummy >> y >>  x[0] >> xer[0]  >> x[1] >> xer[1]  >> x[2] >> xer[2]) {
		cout << dummy << "\t" << y << "\t" << x[0] << "\t" << xer[0] << "\t" << x[1] <<  "\t" << xer[1] <<"\t" << x[2] <<  "\t" << xer[2] <<endl;
			if(x[j] * y != 0){
			g1->SetPoint(index, y, x[j]);
			g1->SetPointError(index, 0, xer[j]);
			
			}
		index++;
		}

	}
  g1->SetMarkerColor(4);
  g1->SetLineColor(4);
  g1->SetMarkerStyle(8);
  g1->Draw("AP");
g1->Fit("pol1");
}




/*
	//int k = stoi(argv[2]);
	gROOT->SetStyle("ATLAS");
	//gStyle->SetOptFit();

	TF1* func[2];
	func[0] = new TF1("funct", "[0]");//const
	//int datacolumn = ;

	
	//int l = 2;	
	for(int l = 1;l <= 2;l++){
	func[l]->SetParName(0, "A");
	func[l]->SetParameter(0, 5);
	func[l]->SetParLimits(0,1,10);
	//func[l]->FixParameter(0,ra222lambda);
	}
	
TCanvas *c1 = new TCanvas("c1","c1",1000,500);	
	int j = 0;
	TH1D* hist[3];

	//double nu = 0;			//how high energy?

while(true){
	hist[j] = new TH1D("name" ,"" ,260 ,0 ,260);
	TGraph graph = TGraph();
//ifstream buffer;
	//string dataname = a1;
	//ifstream ifs(a1);
	ifstream ifs("dotsdata.txt");
	//double x[5] = {105,117,59,47,111};
	//double y[5] = {1173,1332,661,511,1274};
	//int inx, iny;
	//string bufferin;

			
			cout << bufferin << "\t";	
			//buffer >> x[1] >> ;
			//inx = x;
			//iny = y;
				//for(int i=0; i >= iny; i++ ){
				hist[j]->Fill(inx,iny);	
			//nu++;
			//if(nu > 900){break;}
		}

for(int i = 0;i>=4; i++){
	hist[j]->Fill(x[i],y[i]);
	graph.Setpoint(graph.GetN(),x[i],y[i]);
}

	//}
	hist[j]->SetMaximum(250);//y軸の最大値
	hist[j]->GetXaxis()->SetTitle("Peak(ch)");
	hist[j]->GetYaxis()->SetTitle("energy(keV)");
	hist[j]->SetStats(0); 
	//hist[j]->SetLineColor(kRed);
	hist[j]->SetMarkerStyle(21);
	
//hist[j]->Fit("pol1","+");
//hist[j]->Draw("hist same");
//hist[j]->Draw("p ");
//hist[j]->Draw("e same");
graph->Draw("AP");


//integral peak
//cout << "integral" << hist[j]->Integral(130,160) << endl;



string drawmore;
cout << "do u wanna draw more?(y/n):";
cin >> drawmore;
	if(drawmore == "n"){
	break;
	}
j++;
}

}
*/
