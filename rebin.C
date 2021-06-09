//
//	filename:rebin.C
// 	Author:Y.Takagi 
// 	first create:2021/06/04
//	final change:2021/06/09(add saveas)
//
//	no claim, no return
//	usage notion:plz use in the files with .root
//


void rebin(vector<int> peak_mean){

int gaus_peak_num = peak_mean.size() - 2;

TCanvas *c3 = new TCanvas("c3","c3",1000,500);
TH1D *h = new TH1D("","",gaus_peak_num,0,gaus_peak_num); 
h->SetStats(0);

for(int j = 0; j < gaus_peak_num ;j++){
   for (int i = 0;i < peak_mean[j+2] ;i++) {
	h->Fill(j);
   }}
	h->Draw("hist");
TString graphname = Form("./rebingraph/led%d_%d.gif",(Int_t)peak_mean[0],(Int_t)peak_mean[1]);
c3->SaveAs(graphname,"gif");


}








//　　　　　　　_________
//　　　　　 ／　　　　 　＼
//　　　　／　　 ⌒　　　⌒ 　＼　　　こんなクソマクロのクソソースに
//　　 ／　　 （ ⌒） 　（⌒）　＼　　　よくきたおね
//　　 i::::::⌒  （__人__）⌒:: i 　　　粗茶ですお
//　　　ヽ、　　　 `ー '　　　 ／　　　ゆっくりしていってお
//　　　 　/　　　 　　 　┌─┐
//　　　 　i 　　 丶　ヽ{ .毒 }ヽ
//　　　 　ｒ 　 　 ヽ、__)一(_丿
//　　　 　ヽ、___　　　ヽ　ヽ　
//　　　　 と_＿＿_＿ノ＿ノ
//
