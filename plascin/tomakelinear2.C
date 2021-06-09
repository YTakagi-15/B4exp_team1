//
//	file name:tomakelinear2.C
//	author:Y.Takagi 
//	first create:2021/06/04(change from linear1)
//	final change:2021/06/08(add saveas)
//	
//	usage notion:plz use in the directory has led[datano].root files
//


//require vector = (fileno,ch,mean1,error1,mean2,error2....)
vector<double_t> tomakelinear2(vector<double> peak_bins){

//set variables
int peak_number = peak_bins.size();
TCanvas *c2 = new TCanvas("c2","c2",1000,500);	
TGraphErrors* g1 = new TGraphErrors();
	for(int i = 0; i < (peak_number - 2) / 2; i++) {//ex fileno,ch
		g1->SetPoint(i, i, peak_bins[2*i+2]);//2,4,...(mean)
		g1->SetPointError(i, 0, peak_bins[2*i+3]);//3,5,...(error)
	}

//set graph color	
  g1->SetMarkerColor(4);
  g1->SetLineColor(4);
  g1->SetMarkerStyle(8);
  g1->Draw("AP");

//set fit parameters
TF1 *func =  new TF1("","[0]+[1]*x");
func->SetParameter(0,0);
func->SetParameter(1,0);
g1->Fit(func);

//return results
vector<double_t> result;
result.push_back(func->GetParameter(1));
result.push_back(peak_bins[0]);
result.push_back(peak_bins[1]);
result.push_back(func->GetParameter(0));
TString graphname = Form("./linegraph/led%d_%d.gif",(Int_t)peak_bins[0],(Int_t)peak_bins[1]);
c2->SaveAs(graphname,"gif");

return result;
}


