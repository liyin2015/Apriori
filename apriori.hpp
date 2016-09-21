//
// Created by Li Yin Sulimowicz on 9/16/16.
//

#ifndef APRIORI_HPP_
#define APRIORI_HPP_

#include<iostream>
#include<vector>
#include "io_manager.h"
//#include "../io_manager.hpp"

using namespace std;

/************************class Apriori*****************************************************/

class Apriori
{
public:
	Apriori();
	~Apriori();
	void setMinSupport(int m);
	void loadData(std::string& filename); //interface
	void generateCanidate(const AVector& Hk_1,int k, AVector& result);//generate L1 to C2,
	void createC1andGenerateL1(DVector& x_orig);

	AVector generateC();//used to generate C2,C3,C4.....
	
	void countCK(AVector& C, int k);//used to get count for C2,C3,C4...

	void scanD(AVector& C, int k); //used to get those who has minsupport for C2,C3,C4....

	void generateL(int k);
	void runApriori(); //interface

	void generateRules();//use Lk and conf
	void generateRulesFromConseq(AItem& freqset, AVector& H);
	void calcConf(AItem& freqset, AVector& H, AVector& result);

	//interface

	//void setPara(OTHER_ALGO_PARA& para);
	void executeAlgo();
public:
	DVector X_orig;//change to matrix 
	AVector* L;  //real frequency items with support bigger than 2.
	RVector R;
	//int minSupport;//from 1 to k, at first, make it all the same
	//double* minSupport;
	double minSupport;
	double minConf;
	int numD;
	int endK;
	int totalItem;
	int minItem;
	int maxItem;
	vector<vector<int>> bucketSearch;
};

#endif
