// generator.cpp
// Jonnathan Romero, April 2017
// compile with...
// c++ -o gen -std=c++11 generator.cpp
// execute with...
// ./gen

#include "Declarations.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

struct Stock{
	double mu;
	double sigma2;
	double V2;
	double s0;
	double s;
	double gam;
	double bet;
	double al;
	std::string name;

	Stock(std::string n, double st, double VV, double g, double b, double a, double m){
		name = name;
		s = s0 = st;
		sigma2 = V2 = VV;
		gam = g;
		bet = b;
		al = a;
		mu = m;
	}

};

int main(){

	double T           = .25;                                   // length of simulation 3 months
	int ticks          = 1000;                                  // ticks

	double dt          = 0.00025;                           // change in time;

	double rr          = 0.02;                                  // risk free rate

	double rubberband  = 300;                                   // rubberband

	double A, B, C;
	double W, X, Y, Z;

	double BM;

	double UT;

	Stock TAPPLE("TAPPLE", 100.00, (.25*.25),0.065,0.885,0.05,0);
	Stock APPCHAT("APPCHAT", 20.00, (.2*.2),0.035,0.955,0.01,0);
	Stock BESLA("BESLA", 300.00, (.4*.4), 0.105,0.865,0.03,0);
	Stock TAB("TAB", 580.00, 50, 0, 0, 0,0);
	
	std::cout<<"Please enter seed ('0' for random): ";
	int seed = 0;
	std::cin>>seed;

	if(seed==0)
		seed = time(NULL);

	MTUniform(seed);

	std::ofstream txt;

	txt.open("Stocks.csv");

	txt<<"Time,TAPPLE_BID,TAPPLE_ASK,APPCHAT_BID,APPCHAT_ASK,BESLA_BID,BESLA_ASK,TAB_BID,TAB_ASK\n";

	W = PsiInv(MTUniform(0));

	UT = sqrt(1/(2*rubberband))* W;

	TAB.s = TAB.s + TAB.sigma2*UT;

	txt<<std::setprecision(2)<<std::fixed;

	txt<<"0,"<<TAPPLE.s-0.02<<","<<TAPPLE.s+0.02<<","<<APPCHAT.s-0.01<<","<<APPCHAT.s+0.01<<","<<BESLA.s-0.03<<","<<BESLA.s+0.03<<","<<TAB.s-0.12<<","<<TAB.s+0.12<<",";
	

	for(int i = 1; i <= ticks; ++i){

			
		A = PsiInv(MTUniform(0));
		B = PsiInv(MTUniform(0));
		C = PsiInv(MTUniform(0));
	
		W = PsiInv(MTUniform(0));

		X = A;
		Y = 0.7 * A + 0.7141428 * B;
		Z = -0.4 * A + 0.8121624 * B + 0.424726 * C;

		//Tapple

		TAPPLE.mu = (rr - 0.5 * TAPPLE.sigma2) * dt;

		BM  = sqrt(TAPPLE.sigma2) * sqrt(dt) * A;

		TAPPLE.s = TAPPLE.s * exp(TAPPLE.mu + BM);

		TAPPLE.sigma2 = (TAPPLE.gam) * TAPPLE.V2 + (TAPPLE.bet) * TAPPLE.sigma2 + (TAPPLE.al) * BM * BM /dt;
		
		//Appchat

		APPCHAT.mu = (rr - 0.5 * APPCHAT.sigma2) * dt;

		BM  = sqrt(APPCHAT.sigma2) * sqrt(dt) * B;

		APPCHAT.s = APPCHAT.s *exp(APPCHAT.mu  + BM);

		APPCHAT.sigma2 = (APPCHAT.gam) * APPCHAT.V2 + (APPCHAT.bet) * APPCHAT.sigma2 + (APPCHAT.al) * BM * BM /dt;

		//Besla

		BESLA.mu = (rr - 0.5 * BESLA.sigma2) * dt;

		BM  = sqrt(BESLA.sigma2) * sqrt(dt) * C;

		BESLA.s = BESLA.s * exp(BESLA.mu + BM);

		BESLA.sigma2 = (BESLA.gam) * BESLA.V2 + (BESLA.bet) * BESLA.sigma2 + (BESLA.al) * BM * BM /dt;

		//Tab

		UT = UT * exp(-rubberband*dt) + W * sqrt((1-exp(-2*rubberband*dt))/(2*rubberband));

		if(i>(ticks-60))
			TAB.sigma2 -=  TAB.V2/60;

		TAB.s = 2 * TAPPLE.s + 4 * APPCHAT.s + BESLA.s + TAB.sigma2*UT;

		txt<<"\n"<<i<<","<<TAPPLE.s-0.02<<","<<TAPPLE.s+0.02<<","<<APPCHAT.s-0.01<<","<<APPCHAT.s+0.01<<","<<BESLA.s-0.03<<","<<BESLA.s+0.03<<","<<TAB.s-0.12<<","<<TAB.s+0.12<<",";
	}

	txt.close();

	std::cin.get();

	return 0;
}

#include "Definitions.h"