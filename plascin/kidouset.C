//
//	filename:rebin
// 	Author:Y.Takagi 
// 	first create:2021/06/04
//	final change:2021/06/04
//
//	no claim, no guarantee, and no responsibility
//	
//

//#include<>

void kidouset(){
gROOT->ProcessLine(".L ./rebin.C");
gROOT->ProcessLine(".L ./counter.C");
gROOT->ProcessLine(".L ./totalfit.C");
gROOT->ProcessLine(".L ./tomakelinear2.C");

cout << "Usage:(only type this sentence,without .x)" << endl << "rebin(counter(tomakelinear2(totalfit([fileNo.],[chNo.]))))" << endl;

cout << "fill variables now?(y/n)";
TString kk;
int kkk,kkkk;
cin >> kk;

if(kk == "y"){
cout << "give me fileNo xxxx";
cin >> kkk;
cout << "give me chNo";
cin >> kkkk;
cout << "copy and paste this sentence to commandline.";
cout << Form("rebin(counter(tomakelinear2(totalfit(%i,%i))))",kkk,kkkk) << endl;
}


}
