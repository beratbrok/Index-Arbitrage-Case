// skeleton.cpp
// Jonnathan Romero, April 2017

#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <string>

const int ticks = 1001;

class Stock{

public:

	double* bid;
	double* ask;

	Stock(){
		
		bid  = new double[ticks];
		ask  = new double[ticks];
	} 

	void fillBid(double* seq, const int& size){

		int i;

		for(i = 0; i < size; ++i)
			bid[i] = seq[i];
		
	}

	void fillAsk(double* seq, const int& size){

		int i;

		for(i = 0; i < size; ++i)
			ask[i] = seq[i];
	}

};

void prices(std::string fileName, const int& len, Stock& W, Stock& X, Stock& Y, Stock& Z){

	std::ifstream infile;
	std::string str;
	int i;

	infile.open(fileName);

	if(infile.is_open()){

		getline(infile, str);

		double *Bid1, *Ask1, *Bid2, *Ask2, *Bid3, *Ask3, *Bid4, *Ask4;

		Bid1 = new double[len]; Ask1 = new double[len];
		Bid2 = new double[len]; Ask2 = new double[len];
		Bid3 = new double[len]; Ask3 = new double[len];
		Bid4 = new double[len]; Ask4 = new double[len];

		for(i=0; i<len; ++i){
			getline(infile, str,',');               // time

			getline(infile, str,',');               // TAPPLE bid
			Bid1[i] = stod (str);
			getline(infile, str,',');               // TAPPLE ask
			Ask1[i] = stod (str);

			getline(infile, str,',');               // TAPPLE bid
			Bid2[i] = stod (str);
			getline(infile, str,',');               // TAPPLE ask
			Ask2[i] = stod (str);

			getline(infile, str,',');               // TAPPLE bid
			Bid3[i] = stod (str);
			getline(infile, str,',');               // TAPPLE ask
			Ask3[i] = stod (str);

			getline(infile, str,',');               // TAPPLE bid
			Bid4[i] = stod (str);
			getline(infile, str,',');               // TAPPLE ask
			Ask4[i] = stod (str);
		}

		W.fillBid(Bid1,len);
		W.fillAsk(Ask1,len);

		X.fillBid(Bid2,len);
		X.fillAsk(Ask2,len);

		Y.fillBid(Bid3,len);
		Y.fillAsk(Ask3,len);

		Z.fillBid(Bid4,len);
		Z.fillAsk(Ask4,len);

		infile.close();

	}else{
		
		std::cout<<"Error Opening File 'Stocks.csv'.\n";
		
		double* zeroSeq = new double[len];

		for(i=0; i<len; ++i)
			zeroSeq[i] = 0; 

		W.fillBid(zeroSeq,len);
		W.fillAsk(zeroSeq,len);

		X.fillBid(zeroSeq,len);
		X.fillAsk(zeroSeq,len);

		Y.fillBid(zeroSeq,len);
		Y.fillAsk(zeroSeq,len);

		Z.fillBid(zeroSeq,len);
		Z.fillAsk(zeroSeq,len);

		delete[] zeroSeq;
	}
}

struct Trader{

	int Tpos;
	int Apos;
	int Bpos;
	int TABpos;

	int Tlim;
	int Alim;
	int Blim;
	int TABlim;

	double T_bid_price;
	double T_ask_price;
	double A_bid_price;
	double A_ask_price;
	double B_bid_price;
	double B_ask_price;
	double TAB_bid_price;
	double TAB_ask_price;

	std::ofstream strat;

	Stock T;
	Stock A;
	Stock B;
	Stock TAB;

	Trader(std::string fname){

		strat.open(fname);

		T_bid_price=T.bid[0];
		T_ask_price=T.ask[0];
		A_bid_price=A.bid[0];
		A_ask_price=A.ask[0];
		B_bid_price=B.bid[0];
		B_ask_price=B.ask[0];
		TAB_bid_price=TAB.bid[0];
		TAB_ask_price=TAB.ask[0];

		prices("Stocks.csv", ticks, T, A, B, TAB);

		Tpos=0;
		Apos=0;
		Bpos=0;
		TABpos=0;

		Tlim=0;
		Alim=0;
		Blim=0;
		TABlim=0;
	}

	void updatePrices(int t){
		T_bid_price=T.bid[t];
		T_ask_price=T.ask[t];
		A_bid_price=A.bid[t];
		A_ask_price=A.ask[t];
		B_bid_price=B.bid[t];
		B_ask_price=B.ask[t];
		TAB_bid_price=TAB.bid[t];
		TAB_ask_price=TAB.ask[t];		
	}

	void sendOrder(int t, int W, int X, int Y, int Z){
		
		strat<<t<<","<<W<<","<<X<<","<<Y<<","<<Z<<",";
		
		if(t!=1000) strat<<"\n";

		if(Tlim<=abs(Tpos+W))
			Tpos+=W;

		if(Alim<=abs(Apos+X))
			Apos+=X;
		

		if(Blim<=abs(Bpos+Y))
			Bpos+=Y;
		

		if(TABlim<=abs(TABpos+Z))
			TABpos+=Z;

	}

	~Trader(){
		strat.close();
	}
};