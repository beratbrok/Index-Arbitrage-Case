// run.cpp
// Jonnathan Romero, April 2017
// compile with...
// c++ -o test -std=c++11 run.cpp
// execute with...
// ./test

#include "Declarations.h"
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <string>

struct Stock{

	std::string name;
	double* bid;
	double* ask;

	Stock(std::string sname, const int& size){
		
		name = sname;
		bid  = new double[size];
		ask  = new double[size];
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

struct Trader{

	std::string traderName;

	int Tposition;
	int Aposition;
	int Bposition;
	int TABposition;

	int Tlimit;
	int Alimit;
	int Blimit;
	int TABlimit;

	double PNL;

	Trader(std::string tname, int Tpos, int Apos, int Bpos, int TABpos, double profit){

		traderName  = tname;

		Tposition   = Tpos;
		Aposition   = Apos;
		Bposition   = Bpos;
		TABposition = TABpos;

		PNL         = profit;

		Tlimit   = 200;
		Alimit   = 300;
		Blimit   = 50;
		TABlimit = 100;
	}

	void order(Stock& s, int amount, int time){
		if(amount!=0){
			if(s.name == "TAPPLE"){
				if(Tlimit>=abs(Tposition+amount)){
					Tposition+=amount;
					if(amount<0){
						PNL += -amount*s.bid[time];
					}else{
						PNL += -amount*s.ask[time];
					}
					std::cout<<traderName<<time<<": Success attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" at "<<(amount>0?s.ask[time]:s.bid[time])<<", current position is "<<Tposition<<".\n";
				}else{
					std::cout<<traderName<<time<<": Unsuccess attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" current position is "<<Tposition<<", limit is "<<Tlimit<<".\n";
				}
			}else if(s.name == "APPCHAT"){
				if(Alimit>=abs(Aposition+amount)){
					Aposition+=amount;
					if(amount<0){
						PNL += -amount*s.bid[time];
					}else{
						PNL += -amount*s.ask[time];
					}
					std::cout<<traderName<<time<<": Success attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" at "<<(amount>0?s.ask[time]:s.bid[time])<<", current position is "<<Aposition<<".\n";
				}else{
					std::cout<<traderName<<time<<": Unsuccess attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" current position is "<<Aposition<<", limit is "<<Alimit<<".\n";
				}
			}else if(s.name == "BESLA"){
				if(Blimit>=abs(Bposition+amount)){
					Bposition+=amount;
					if(amount<0){
						PNL += -amount*s.bid[time];
					}else{
						PNL += -amount*s.ask[time];
					}
					std::cout<<traderName<<time<<": Success attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" at "<<(amount>0?s.ask[time]:s.bid[time])<<", current position is "<<Bposition<<".\n";
				}else{
					std::cout<<traderName<<time<<": Unsuccess attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" current position is "<<Bposition<<", limit is "<<Blimit<<".\n";
				}
			}else if(s.name == "TAB"){
				if(TABlimit>=abs(TABposition+amount)){
					TABposition+=amount;
					if(amount<0){
						PNL += -amount*s.bid[time];
					}else{
						PNL += -amount*s.ask[time];
					}
					std::cout<<traderName<<time<<": Success attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" at "<<(amount>0?s.ask[time]:s.bid[time])<<", current position is "<<TABposition<<".\n";
				}else{
					std::cout<<traderName<<time<<": Unsuccess attempt to "<<(amount>0?"BUY ":"SELL ")<<abs(amount)<<" of "<<s.name<<" current position is "<<TABposition<<", limit is "<<TABlimit<<".\n";
				}
			}
		}
	}

	void closeout(Stock& X, Stock& Y, Stock& Z, Stock XYZ, const int time){
		order(X,-Tposition,time);
		order(Y,-Aposition,time);
		order(Z,-Bposition,time);
		order(XYZ,-TABposition,time);
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

		W.fillBid(Bid1,len); W.fillAsk(Ask1,len);
		X.fillBid(Bid2,len); X.fillAsk(Ask2,len);
		Y.fillBid(Bid3,len); Y.fillAsk(Ask3,len);
		Z.fillBid(Bid4,len);Z.fillAsk(Ask4,len);

		infile.close();

	}else{
		
		std::cout<<"\nError Opening File 'Stocks.csv'.\n";
		
		double* zeroSeq = new double[len];

		for(i=0; i<len; ++i)
			zeroSeq[i] = 0; 

		W.fillBid(zeroSeq,len); W.fillAsk(zeroSeq,len);
		X.fillBid(zeroSeq,len); X.fillAsk(zeroSeq,len);
		Y.fillBid(zeroSeq,len); Y.fillAsk(zeroSeq,len);
		Z.fillBid(zeroSeq,len); Z.fillAsk(zeroSeq,len);

		delete[] zeroSeq;
	}
}

int Run(Trader& bar,const int& len, const std::string& fileName, Stock& X, Stock& Y, Stock& Z, Stock& XYZ){
	
	std::ifstream infile;
	std::string str;

	int amount;

	int check;
	int i;

	infile.open(fileName);

	if(infile.is_open()){

		std::cout<<std::endl;

		for(i=0; i<len-1; ++i){

			getline(infile, str, ',');                 // time

			check = stoi (str);

			if(check==i){

				check = 0;

				getline(infile, str, ',');
				amount = stoi (str);
				bar.order(X, amount, i);

				check += abs(amount);

				getline(infile, str, ',');
				amount = stoi (str);
				bar.order(Y, amount, i);

				check += abs(amount);

				getline(infile, str, ',');
				amount = stoi (str);
				bar.order(Z, amount, i);

				check += abs(amount);

				getline(infile, str, ',');
				amount = stoi (str);
				bar.order(XYZ, amount, i);

				check += abs(amount);

				if(check!=0)
					std::cout<<std::endl;

			}else{
				std::cout<<"Check commas (there should be 5 per line) or tick numbering (cannot skip ticks).\nThere should be 5 integers per line.\nCheck line"<<i<<"\n";

				bar.closeout(X,Y,Z,XYZ,i);
				return 0;
			}
		}

		infile.close();

		bar.closeout(X,Y,Z,XYZ,len-1);

		return 1;

	}else{
		
		std::cout<<"\nError Opening File '"<<fileName<<"'. Check the filename.\n";
		return 0;
	}
}

int main(){

	const int ticks = 1001;
	std::string str;

	Stock T("TAPPLE",  ticks);
	Stock A("APPCHAT", ticks);
	Stock B("BESLA",   ticks);
	Stock TAB("TAB",   ticks);

	prices("Stocks.csv", ticks, T, A, B, TAB);  // fills in the stock prices

	std::cout<<"Trader Name: ";
	std::cin>>str;

	Trader baruch(str, 0, 0, 0, 0, 0);

	std::cout<<"Enter strategy file name (eg. <strategy1.csv>): ";
	std::cin>>str;

	if(Run(baruch, ticks, str, T, A, B, TAB)==0){
		std::cout<<"\nThere was a mistake in your strategy file.\nFile should be a csv file type.\nShould look similar to the following:\n\n";

		std::cout<<"0,0,0,0,0,\n1,0,0,0,0,\n2,0,0,0,0,\n3,0,0,0,0,\n4,0,0,0,0,\n5,0,0,0,0,\n...\n1000,0,0,0,0,\n\n";
	}

	std::cout<<"\n"<<baruch.traderName<<" PNL: "<<baruch.PNL<<"\n";

	Pause();

	return 0;
}

#include "Definitions.h"