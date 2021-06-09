void(){


	string filename2("./ragraphs/chi&data.txt");
			fstream file_out;
			file_out.open(filename1, ios_base::app);		

			//kakikomi
			file_out << n << 
			"\t" << func[n]->GetChisquare() << 
			"\t" << func[n]->GetNDF() <<
			"\t" << func[n]->GetChisquare()/func[n]->GetNDF() << "\t" ;
	

}
