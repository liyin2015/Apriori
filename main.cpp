//
// Created by Li Yin Sulimowicz on 9/16/16.
//
//#include <iostream>
//#include <ctime>
//#include "apriori.hpp"
//using namespace std;

//clock_t t1;
/*int main() {

    Apriori a;
    string filename = "/Users/yinli/ClionProjects/Apriori/5000-out1.csv";
    //string filename = "/Users/yinli/ClionProjects/Apriori/apriori.txt";

    a.loadData(filename);
    t1 = clock();
    a.setMinSupport(2);
    a.executeAlgo();

    cout<<"total time: "<<(clock()-t1)/CLOCKS_PER_SEC<<"secs"<<endl;
    //cout << "Hello, World!" << endl;
    return 0;
}*/

/*----------------------------------------------------------------------
  File     : testfpgrowth.cpp
  Contents : FP-growth algorithm for finding frequent sets
  Author   : Bart Goethals
  Update   : 04/04/2003
----------------------------------------------------------------------*/

#include <iostream>

#include <stdlib.h>
#include <time.h>
#include "fpgrowth/data.hpp"
#include "fpgrowth/item.hpp"
#include "fpgrowth/fptree.hpp"
#include "fpgrowth/fpgrowth.hpp"
using namespace std;
int main()
{
    cout << "FP-growth frequent itemset mining implementation" << endl;
    cout << "by Bart Goethals, 2000-2003" << endl;
    cout << "http://www.cs.helsinki.fi/u/goethals/" << endl << endl;

    /*if(argc < 4){
        cerr << "usage: " << argv[0] << " datafile datatype minsup [output]" << endl;
        cerr << "datatype = 1 for Quest datagenerator binary" << endl;
        cerr << "datatype = 2 for Quest datagenerator ascii" << endl;
        cerr << "datatype = 3 for flat, i.e. all items per transaction on a single line" << endl;
        cerr << "datatype = 4 for ascii version of Quest datagenerator binary" << endl;
    }
    else{*/

    FPgrowth fPgrowth;
        //FPgrowth *fpgrowth = new FPgrowth();

        //fpgrowth->setData(argv[1],atoi(argv[2]));
        //fpgrowth->setMinsup(2);
        //if(argc==5) fpgrowth->setOutput(argv[4]);

        //clock_t start = clock();
        //int added = fpgrowth->mine();
        //cout << added << "\t[" << (clock()-start)/double(CLOCKS_PER_SEC) << "s]" << endl;
        //if(argc==5) cout << "Frequent sets written to " << argv[4] << endl;

       // delete fpgrowth;
   // }

    return 0;
}
