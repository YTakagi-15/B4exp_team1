void Am_20210617_8(){
	TCanvas* c1 = new TCanvas("1","1",1000,500);
	TCanvas* c2 = new TCanvas("2","2",1000,500);
	vector<string> filename = {"./Am_20210617_8_0.dat","./Bg_20210617_8_0.dat"};
	TH1D* hist[3];
	for(int i = 0; i < 2;i++){
		string buff ;
		int a = 1;
		int b;
		int c;
		ifstream ifs(filename[i]);
		hist[i] = new TH1D ("","", 200 , 0, 2000);
		while(ifs >> buff ){
			//cout << buff << endl;
			if( a != 2054 ){

				if( a >= 6 ){
					if( a % 2 == 0 ){
						b = stoi(buff);}
				}
			}
			if( c <= b ){ c = b;}
			if( a == 2053 ){
				hist[i]->Fill(c);}
			if ( a == 2055 ){
				a = 0;
				b = 0;
				c = 0;}
			a++;
		}}
	hist[2] = new TH1D ("","", 200 , 0, 2000);
	hist[2]->Add(hist[0],hist[1],1,-1);
	c1->cd();
	hist[2]->Draw("hist same");
	c2->cd();
	hist[1]->SetLineColor(kRed);
	hist[1]->Draw("hist same");
	hist[0]->Draw("hist same");
	//intger

}
