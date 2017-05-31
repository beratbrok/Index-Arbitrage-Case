// Jonnathan Romero, April 2017
// Skeleton.cpp 
// compile with
// c++ -o m main.cpp
// execute with
// ./m

#include "skeleton.cpp"

int main(){

	Trader trade("strategy.csv");

	int TAPPLE_amount, APPCHAT_amount, BESLA_amount, TAB_amount;

	for(int time=0; time<ticks; time++){

		trade.updatePrices(time);                                           // this code updates prices

		TAPPLE_amount = APPCHAT_amount = BESLA_amount = TAB_amount = 0;     // reset order amounts
		
		/*

		trade.Tpos                  &is Tapple position at the beginning of tick\\ \hline
	    trade.Apos                  &is Appchat position at the beginning of tick\\ \hline
	    trade.Bpos                  &is Besla position at the beginning of tick\\ \hline
	    trade.TABpos                &is TAB position at the beginning of tick\\ \hline

		trade.Tlim                  &is Tapple position limit\\ \hline
		trade.Alim                  &is Appchat position limit\\ \hline
		trade.Blim                  &is Besla position limit\\ \hline
		trade.TABlim                &is TAB position limit\\ \hline

		trade.T_bid_price           &is Tesla bid price\\ \hline
		trade.T_ask_price           &is Tesla ask price\\ \hline

		trade.A_bid_price           &is Appchat bid price\\ \hline
		trade,A_ask_price           &is Appchat ask price\\ \hline

		trade.B_bid_price           &is Besla bid price\\ \hline
		trade.B_ask_price           &is Besla ask price\\ \hline

		trade.TAB_bid_price         &is TAB bid price\\ \hline
		trade.TAB_ask_price         &is TAB ask price\\ \hline

		*/

		//*******************************ALGO HERE************************************************


		if(2*trade.T_bid_price + 4*trade.A_bid_price + trade.B_bid_price > trade.TAB_ask_price){
			TAPPLE_amount = -64;
			APPCHAT_amount = -128;
			BESLA_amount = -32;
			TAB_amount = 32;
		}

		if(2*trade.T_ask_price + 4*trade.A_ask_price + trade.B_ask_price < trade.TAB_bid_price){
			TAPPLE_amount = 64;
			APPCHAT_amount = 128;
			BESLA_amount = 32;
			TAB_amount = -32;
		}


		//****************************************************************************************
		trade.sendOrder(time,TAPPLE_amount, APPCHAT_amount, BESLA_amount, TAB_amount);
	}

	return 0;
}
