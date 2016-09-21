//
// Created by Li Yin Sulimowicz on 9/16/16.
//

#ifndef APRIORI_FP_GROWTH_APRIORI_H
#define APRIORI_FP_GROWTH_APRIORI_H

#include <iostream>
#include <string>
#include <vector>
#include "../apriori.hpp"
//#include "sort_algo.hpp"
#include "binary_tree.hpp"
using namespace std;


/*total id =2;  1,2,5*/
/*2,4*/
/*total item is 1,2,4,5, count is 1,2,1,1*/
/*************************/
//used for transaction
class ITEM
{
public:
    ITEM();
    ITEM(string item_v, int count_);
    ~ITEM();
    ITEM(const ITEM& m);
    bool operator==(const ITEM& m);
    const ITEM& operator=(const ITEM& m);
    friend ostream& operator<<(ostream& out,const ITEM& m);
public:
    string item;
    int count;
};
/**************************class FVector to represent table 12-2**********************************************************/
//used for a single transaction id
template <class T>
class FVector
{
public:
    FVector(int totalD);
    FVector();
    ~FVector();
    FVector(const FVector& m);
    const FVector& operator=(const FVector& m);
    void setCountByName(string& name, int index, int count_v);
    bool IsItemStored(T& item);
    void AddOneItem(T& item, int index); //index is  transId
    bool FindInSingleD(int index, T& item);
    void sortByOrder();//if count < int count, then, delete it from the transaction, and then sort those left
    void remove(int k);
    void print();
public:
    vector<T>* all_bucket; //index is transId, one vector<ITem> is one bucket/transaction
    int totalD;
};

class IndexStruct
{
public:
    IndexStruct(){name = ""; parent = NULL; avail_index = NULL;/*; pre_link = NULL;*/}
    IndexStruct(const IndexStruct& m)
    {
        if(this != &m)
        {
            this->name = m.name;
            this->numD = m.numD;
            this->parent = m.parent;
            //this->pre_link = m.pre_link;
            this->avail_index = new bool[m.numD];
            for(int i=0;i<numD;i++)
            {
                this->avail_index[i] = m.avail_index[i];
            }
        }
    }
    const IndexStruct& operator=(const IndexStruct& m)
    {
        if(this != &m)
        {
            this->name = m.name;
            this->numD = m.numD;
            this->parent = m.parent;
            //this->pre_link = m.pre_link;
            this->avail_index = new bool[m.numD];
            for(int i=0;i<numD;i++)
            {
                this->avail_index[i] = m.avail_index[i];
            }
        }
        return *this;
    }
    ~IndexStruct()
    {
        if(avail_index != NULL)
        {
            delete[] avail_index;
            avail_index = NULL;
        }
    }
public:
    string name;
    void** parent;//需要指向指针的指针
    //void** pre_link;
    bool* avail_index;
    int numD;
};

template <class T>
struct HeaderNode
{
    T data;
    struct HeaderNode *nextLink;
};

template <class T>
TreeNode<T>** updataTree(TreeNode<T>** inTree, string& name)
{
    if(inTree == NULL) //its header
    {
        cout<<"parent is NULL"<<endl;
        return NULL;
    }
    else
    {
        //cout <<"parent"<<(*inTree)->data<<endl;
        if((*inTree)->lchild == NULL)
        {
            //cout<<" insert in left"<<endl;
            (*inTree)->lchild = new TreeNode<T>;
            (*inTree)->lchild->data.item = name;
            (*inTree)->lchild->data.count =1;
            (*inTree)->lchild->parent = *inTree;
            return &((*inTree)->lchild);
        }
        else if((*inTree)->lchild->data.item.compare(name) == 0)
        {
            //cout<<"inc in left"<<name<<":"<<(*inTree)->lchild->data.count+1<<endl;
            (*inTree)->lchild->data.count++;
            return &((*inTree)->lchild);
        }
        else if((*inTree)->rchild == NULL)
        {
            //cout<<"insert in right"<<endl;
            (*inTree)->rchild = new TreeNode<T>;
            (*inTree)->rchild->data.item = name;
            (*inTree)->rchild->data.count = 1;
            (*inTree)->rchild->parent =  *inTree;
            return &((*inTree)->rchild);
        }

        else if((*inTree)->rchild->data.item.compare(name) == 0)
        {
            //cout<<"inc in right"<<name<<":"<<(*inTree)->rchild->data.count+1<<endl;
            (*inTree)->rchild->data.count++;
            return &((*inTree)->rchild);
        }
        //cout<<"not header, insert in left32332"<<endl;
        return NULL;
    }
}




/**********************************************FpGrowth*****************************************/
class FpGrowth:private Apriori
{
public:
    FpGrowth();
    ~FpGrowth();
    void loadData(std::string& name);
    void setMinSupport(int k);
    void insertIndex(vector<IndexStruct>& indexStruct, int i, string& name,void** parent);
    void firstTimeScan();
    void secondTimeScanConstructFPTree(IndexStruct& );
    void secondTimeScanConstructFPTree2(IndexStruct& );
    void runFpGrowth();
private:
    HeaderNode<ITEM>** getPreLink(string& name);
public:
    FVector<ITEM> transPerLine;
    BTree<ITEM> tree;
    AnyTree<ITEM> tree2;
    HeaderNode<ITEM>** headerTable;
    int headerTableSize;
};
#endif //APRIORI_FP_GROWTH_APRIORI_H
