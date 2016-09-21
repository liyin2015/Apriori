//
// Created by Li Yin Sulimowicz on 9/16/16.
//

#ifndef APRIORI_IO_MANAGER_H
#define APRIORI_IO_MANAGER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

double str2double(char const *  str);


/**************************class DVector**********************************************************/
class DVector //used for transaction X_orig
{
public:
	DVector(int totalD); //total D means total item in one transaction
	DVector();
	~DVector();
	DVector(const DVector& m);
	const DVector& operator=(const DVector& m);
	void AddOneItem(int item, int index);
	bool FindInSingleD(int index, int& item);
	void print();
	void deleteCol(const int col, int& min, int& max);
public:
	vector<int>* D_orig;
	int totalD;
};
/***************************class AItem*************************************************/
class AItem
{
public:
	AItem();
	AItem(int v);
	~AItem();
	AItem(const AItem& m);
	AItem operator-(AItem& m2);
	friend ostream& operator<<(ostream& out,const AItem& m);
	const AItem operator=(const AItem& m);
	void insertElem(int value);
	bool IsExisted(int value);
	bool operator==(const AItem& m);
public:
	int* item;
	int k;
	int count;
};
/***************************************RuleItem********************************/
class RuleItem
{
public:
	RuleItem();
	RuleItem(int f, int l);
	~RuleItem();
	RuleItem(const RuleItem& m);
	friend ostream& operator<<(ostream& out,const RuleItem& m);
	const RuleItem operator=(const RuleItem& m);
	void insertElemF(int value);
	void insertElemL(int value);
	bool operator==(const RuleItem& m);
public:
	int* item_f;
	int* item_l;
	int num_f;
	int num_l;
	double conf;
};
/************************class AVector*************************************************************/
class AVector//used for candidates and l
{
public:
	AVector(int v);
	AVector();
	~AVector();
	AVector(AVector& m);
	AVector operator=(AVector& m);
	friend ostream& operator<<(ostream& out,AVector& m);
	bool IsItemStored(AItem& value);
	double FindCountByItemValue(AItem& value);
	void AddItem(AItem value);
	void AddCountForItem(AItem& value);
	bool IsEmpty();
public:
	vector<AItem> V;
	int k;
};
/**************************RVector************************************************************/
class RVector//used for candidates and l
{
public:
	RVector();
	RVector(RVector& m);
	~RVector();
	RVector operator=(RVector& m);
	friend ostream& operator<<(ostream& out,RVector& m);
	bool IsItemStored(RuleItem& value);
	void AddItem(RuleItem value);
public:
	vector<RuleItem> V;
};


/*template<typename T>
int read_strfile(T& D, int& totalD, std::string filename)//in
{
	totalD=0;
	ifstream  inputfile(filename);

	if(!inputfile)
	{
		cout << "cannot open file."<<endl;
		return -1;
	}

	char ch;

	inputfile.get(ch);
	while(!inputfile.eof())
	{
		std::ostringstream  ss;
		ss<<ch;
        if(ch=='\n')
		{
			totalD++;
		}
		inputfile.get(ch);
	}
	inputfile.close();
	totalD+=1;

	cout<<"totalD"<<totalD<<endl;
	D = DVector(totalD);

	//read the second time
	ifstream  in(filename);

	if(!in)
	{
		cout << "cannot open file."<<endl;
		return -1;
	}

	int lines = 0;
	std::string str = "";
	in.get(ch);
	while(!in.eof())
	{
		std::ostringstream  ss;
	    ss<<ch;
        if(ch=='\n') //transfer former input to num
        {
			D.AddOneItem((int)str2double(str.c_str()),lines);
			str.clear();
			lines++;
        }
        else if(ch==' '||ch == ',')
        {
			D.AddOneItem((int)str2double(str.c_str()),lines);
			str.clear();
        }
		else if((ch>='0'&&ch <= '9'))
		{
			str.append(ss.str());
		}
		in.get(ch);
   }
   D.AddOneItem((int)str2double(str.c_str()),lines);
   in.close();
   return 0;
}*/



#endif //APRIORI_IO_MANAGER_H
