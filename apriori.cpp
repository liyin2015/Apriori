//
// Created by Li Yin Sulimowicz on 9/16/16.
//
#include "apriori.hpp"


/********************************class Apriori**********************************************************/
Apriori::Apriori()
{
	numD = 0;
	L=NULL;
	minSupport = -1;
	minConf = 0.6;
}
Apriori::~Apriori()
{
	if(L!=NULL)
	{
		delete[] L;
		L=NULL;
	}
}
void Apriori::setMinSupport(int m)
{
	//minSupport = new double;
	//*minSupport = m;
	minSupport = m;
	return;
}


template<typename T>
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
		/*else if(ch==' '||ch == ',')
		{
			D.AddOneItem((int)str2double(str.c_str()),lines);
			str.clear();
		}*/

		else if(ch == ',')
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
}
void Apriori::loadData(std::string& filename)//load data and generate C1
{
	read_strfile(X_orig,numD,filename);

	//need to abandon the first number


	X_orig.deleteCol(0,minItem,maxItem);
	//X_orig.print();
}
void Apriori::generateCanidate(const AVector& Hk_1,int k, AVector& Ck)
{
	Ck.k = k;
	//AVector Ck(k);
	vector<AItem>::const_iterator iteo = Hk_1.V.begin();
	for(;iteo!=Hk_1.V.end();iteo++)
	{
		vector<AItem>::const_iterator itei = iteo+1;
		for(;itei!=Hk_1.V.end();itei++)
		{
			bool bEqual = true;
			for(int i=1;i<k-1;i++)
			{
				if(iteo->item[i]!=itei->item[i-1])
				{
					bEqual = false;
					break;
				}
			}
			if(bEqual)
			{
				AItem tmp(k);
				for(int i=0;i<k-1;i++)
				{
					tmp.insertElem(iteo->item[i]);
				}
				tmp.insertElem(itei->item[k-2]);
				Ck.AddItem(tmp);
			}
		}
	}
	//cout<<"C"<<k<<Ck<<endl;
	//return Ck;
	return;
}
void Apriori::countCK(AVector& C, int k)
{
	if(C.k!=k)
	{
		cout<<"you has inputed wrong k"<<endl;
		return;
	}
	if(C.IsEmpty())
	{
		cout<<"C"<<k<<"is empty"<<endl;
		return;
	}

	vector<AItem>::iterator c_ite = C.V.begin();
	for(;c_ite!=C.V.end();c_ite++)
	{
		for (int i = 0; i<numD; i++)
		{
			bool bAdd = true;
			for(int m=0;m<k;m++)
			{
				if(!X_orig.FindInSingleD(i,c_ite->item[m]))
				{
					bAdd = false;
					break;
				}
			}
			if(bAdd)
			{
				C.AddCountForItem(*c_ite);
			}
		}
	}
	//cout<<"Ltmp"<<k<<C<<endl;
	return;
}
void Apriori::createC1andGenerateL1(DVector& x_orig)
{
	AVector C1(1);
	int totalItem = maxItem-minItem+1; //minItem ->0, x=x-minItem,

	vector<int> assistSearch;
	assistSearch.assign(totalItem,-1);

	for (int i = 0; i<numD; i++) //scan the dataset for the first time
	{
		vector<int>::iterator ite = x_orig.D_orig[i].begin();
		for(;ite!=x_orig.D_orig[i].end();ite++)
		{
			AItem a(1);
			a.insertElem(*ite);
			//if(!C1.IsItemStored(a)) //here is a search operation, can be optimized
			if(assistSearch[*ite-minItem]==-1)
			{
				a.count = 1;
				C1.AddItem(a);
				assistSearch[*ite-minItem]=1;
			}
			else
			{
				C1.AddCountForItem(a);
			}

		}
	}
	//init L and the max dimension is (int)C1.V.size()
	totalItem =(int)C1.V.size();
	L= new AVector[(int)C1.V.size()+1];
	//cout<<"C"<<1<<endl<<C1<<endl;
	scanD(C1,1);
	return;
}
void Apriori::scanD(AVector& C, int k) //used for k>=1, count for C
{
	if(C.k!=k)
	{
		cout<<" not the same dimension"<<endl;
		return;
	}
	if(C.IsEmpty())
	{
		cout<<"C"<<k<<"is empty"<<endl;
		return;
	}
	L[k].k=k;
	vector<AItem>::iterator ite = C.V.begin();
	for(;ite!=C.V.end();ite++)
	{
		if(ite->count>=minSupport)
		{
			L[k].V.push_back(*ite);
		}
	}
	//cout<<"L"<<k<<endl<<L[k]<<endl;
}
void Apriori::generateL(int k)
{
	AVector Ck;
	generateCanidate(L[k-1],k, Ck);
	countCK(Ck,k);
	scanD(Ck,k);
}
void Apriori::runApriori()
{
	createC1andGenerateL1(X_orig);
	int k=1;

	for(;!L[k].IsEmpty();k++)
	{
		generateL(k+1);
	}
	endK = k-1;
	cout<<"endK"<<endl;
}
/***************************rules********************************************/
void Apriori::calcConf(AItem& freqset, AVector& H, AVector& prunedH)
{
	prunedH.k = H.k;
	//AVector prunedH(H.k);

	int k_former = freqset.k-H.k;
	int k_later = H.k;

	vector<AItem>::iterator ite = H.V.begin(); 
	for(;ite!=H.V.end();ite++)
	{
		int tmpk=ite->k;
		AItem former = freqset-*ite;
		if(former.k==0) //just in case
		{
			continue;
		}		
		double count_subseq = L[k_former].FindCountByItemValue(former);
		if(count_subseq!=-1)
		{
			double conf = (double)freqset.count/(double)count_subseq;
			if(conf>=minConf)
			{
				RuleItem a(k_former,k_later);
				//add former part
				for(int i=0;i<k_former;i++)
				{
					a.insertElemF(former.item[i]);
				}
				//add later part
				for(int i=0;i<k_later;i++)
				{
					a.insertElemL(ite->item[i]);
				}
				a.conf = conf;	
				R.AddItem(a);
				//add for prunedH
				prunedH.AddItem(*ite);
			}
		}
	}
	//return prunedH;
	return;
}
void Apriori::generateRulesFromConseq(AItem& freqset, AVector& H) //unprunedH3
{
	int m=H.k;
	if(freqset.k>m)
	{		
		AVector prunedh;
		calcConf(freqset,H, prunedh);//compute h1, and returen pruned h1
		AVector htmp;
		generateCanidate(prunedh,m+1,htmp); //generate the later
		if(htmp.k>1 && !htmp.IsEmpty())
		{
			generateRulesFromConseq(freqset,htmp);
		}
	}
}
void Apriori::generateRules()
{
	R.V.clear();
	if(endK<2)
	{
		cout<<"last freqset is smaller than 2, has no associate rules"<<endl;
		return;
	}
	//calc for i==2
	vector<AItem>::iterator  ite1 = L[2].V.begin();
	for(;ite1!=L[2].V.end();ite1++)
	{
		AVector H1(1);
		for(int i=0;i<ite1->k;i++)
		{
			AItem tmp(1);
			tmp.insertElem(ite1->item[i]);
			H1.AddItem(tmp);
		}
		cout<<"H"<<1<<H1<<endl;
		//calcConf(*ite1,H1);//use L1==H1 and freqset,H1
	}
	cout<<"RVector"<<1<<R<<endl;
	for(int i=3;i<=endK;i++)
	{
		vector<AItem>::iterator  ite2 = L[i].V.begin(); //unpruned H3
		for(;ite2!=L[i].V.end();ite2++)
		{
			AVector H2(1);
			for(int i=0;i<ite2->k;i++)
			{
				AItem tmp(1);
				tmp.insertElem(ite2->item[i]);
				H2.AddItem(tmp);
			}
			cout<<"H"<<2<<H2<<endl;
			generateRulesFromConseq(*ite2,H2);
		}		
	}
	cout<<"RVector"<<2<<R<<endl;
}
//interface
/*void Apriori::setPara()
{
	setMinSupport(para.minSupport);
	return;
}*/
void Apriori::executeAlgo()
{
	runApriori(); //apriori
	//generateRules(); //associate rules generated using minimum confidence
	return;
}