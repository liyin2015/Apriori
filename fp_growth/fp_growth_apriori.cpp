//
// Created by Li Yin Sulimowicz on 9/16/16.
//

#include "fp_growth_apriori.h"

/**************************class ITEM**********************************************/
ITEM::ITEM()
{
    item = "";
    count = 0;
}
ITEM::ITEM(string item_v, int count_v)
{
    item = item_v;
    count = count_v;
}
ITEM::~ITEM()
{
    item = "";
}
ITEM::ITEM(const ITEM& m)
{
    if(this != &m)
    {
        this->item = m.item;
        this->count = m.count;
    }
}
bool ITEM::operator==(const ITEM& m)
{
    if(m.count == count && m.item.compare(item) == 0)
    {
        return true;
    }
    return false;
}
const ITEM& ITEM::operator=(const ITEM& m)
{
    if(this != &m)
    {
        item = m.item;
        count = m.count;
    }
    return *this;
}
ostream& operator<<(ostream& out,const ITEM& m)
{
    if(m.item.empty())
    {
        out<<"print item is empty!"<<endl;
        return out;
    }
    //out<<endl;
    //cout<<"oik"<<endl;
    //out<<endl;
    //stringstream ss;
    //ss<<m.item;
    //cout<<"ok1"<<endl;
    out<<m.item<<":"<<m.count;
    //cout<<"oik1"<<endl;
    return out;
}
/*********************************FVector*********************************************/
template <class T>
FVector<T>::FVector(int transId)
{
    transId = transId;
    all_bucket = NULL;
}
template <class T>
FVector<T>::FVector()
{
    all_bucket = NULL;
}
template <class T>
FVector<T>::~FVector()
{
    if(all_bucket!= NULL)
    {
        delete[] all_bucket;
        all_bucket = NULL;
    }
}
template <class T>
FVector<T>::FVector(const FVector& m)
{
    if(this != &m)
    {
        totalD = m.totalD;
        all_bucket= new vector<T>[totalD];
        for(int i=0;i<totalD;i++)
        {
            all_bucket[i].clear(); //bucket i
            vector<T>::iterator  ite = m.all_bucket[i].begin();
            for(;ite!=m.all_bucket[i].end();ite++)
            {
                all_bucket[i].push_back(*ite);
            }
        }
    }

}
template <class T>
const FVector<T>& FVector<T>::operator=(const FVector& m)
{
    if(this != &m)
    {
        if(all_bucket!=NULL)
        {
            delete[] all_bucket;
            all_bucket = NULL;
        }
        totalD = m.totalD;
        all_bucket= new vector<T>[totalD];
        for(int i=0;i<totalD;i++)
        {
            all_bucket[i].clear();
            vector<T>::iterator  ite = m.all_bucket[i].begin();
            for(;ite!=m.all_bucket[i].end();ite++)
            {
                all_bucket[i].push_back(*ite);
            }
        }
    }
    return *this;
}
template <class T>
void FVector<T>::print()
{
    for(int i=0;i<totalD;i++)
    {
        cout<<endl;
        cout<<"row = "<<i<<endl;
        vector<T>::iterator ite = all_bucket[i].begin();
        for(;ite!= all_bucket[i].end();ite++)
        {
            cout<<*ite<<"\t";
        }
        cout<<endl;
    }
}
template <class T>
void  FVector<T>::setCountByName(string& name, int index, int count_v)
{
    vector<T>::iterator ite = all_bucket[index].begin();
    for(;ite!=all_bucket[index].end();ite++)
    {
        if(ite->item.compare(name) == 0)
        {
            ite->count = count_v;
        }
    }
}

//void AddOneRow(string& item);
template <class T>
void FVector<T>::AddOneItem(T& item, int index)
{
    all_bucket[index].push_back(item);
}
template <class T>
void FVector<T>::sortByOrder()
{
    SortAlgo<T> sa;
    for(int i = 0;i <totalD; i++)
    {
        //step 1: copy bucket
        int size = all_bucket[i].size();
        //T* bucket_i =
        sa.a = new T[size];
        vector<T>::iterator ite;
        int j;
        for(j =0, ite = all_bucket[i].begin(); ite != all_bucket[i].end(); ite++,j++)
        {
            sa.a[j] = *ite;
        }
        //step2: sort bucket
        sa.runSort(size);
        //step 3: refill bucket
        all_bucket[i].clear();
        for(j=0; j<size && sa.a[j].count!=0;j++)
        {
            all_bucket[i].push_back(sa.a[j]);
        }
        //delete[] bucket_i;

    }
}
/*bool FVector::FindInSingleD(int index, ITEM& item)
{
    vector<ITEM>::iterator ite = D_orig[index].begin();
    for(;ite!= D_orig[index].end();ite++)
    {
        if(*ite==item)
        {
            return true;
        }
    }
    return false;
}*/
/*void FVector::filtAndSortByCount(int count)
{
}*/
/*****************************TreeNode***************************************************/


//BiTree tree;
//HeaderTable header;


/**********************class FpGrowth*************************************************/
FpGrowth::FpGrowth()
{
    headerTable = NULL;
    Apriori::Apriori();
    headerTableSize = 0;
}
FpGrowth::~FpGrowth()
{
    if(headerTable != NULL)
    {
        delete[] headerTable;
        headerTable = NULL;
    }
    Apriori::~Apriori();
}
//load data and put tge X_orig to FVector
void FpGrowth::loadData(std::string& name)
{
    Apriori::loadData(name);
    //copy X_orig to struct FVector
    transPerLine.totalD = numD;
    transPerLine.all_bucket = new vector<ITEM>[numD];
    for (int i = 0; i<numD; i++)
    {
        vector<int>::iterator ite = X_orig.D_orig[i].begin();
        for(;ite!=X_orig.D_orig[i].end();ite++)
        {
            string tmp = toString(*ite);
            ITEM a(tmp,0);
            transPerLine.AddOneItem(a,i);
        }
    }
    transPerLine.print();
}
void FpGrowth::setMinSupport(int k)
{
    Apriori::setMinSupport(k);
}

void FpGrowth::firstTimeScan()
{
    int level =1;
    Apriori::createC1andGenerateL1(X_orig); //first time scan
    //get count from L1
    //transPerLine.totalD = numD;
    //transPerLine.all_bucket = new vector<ITEM>[numD];

    //construct headertable and FVector
    int size = (int)L[level].V.size();
    headerTable = new HeaderNode<ITEM>*[size];
    for(int i = 0;i<size;i++)
    {
        headerTable[i] = new HeaderNode<ITEM>;
    }
    headerTableSize = size;
    for (int i = 0; i<numD; i++)
    {
        vector<AItem>::iterator ite = L[level].V.begin();
        for(int j =0;ite!=L[level].V.end();ite++, j++)
        {
            string tmp = toString(ite->item[0]);
            //set count for Fvector
            transPerLine.setCountByName(tmp, i, ite->count);
            if(i == 0)
            {
                ITEM item(tmp, ite->count);
                //HeaderTable header;
                headerTable[j]->data = item;
                headerTable[j]->nextLink = NULL;
            }
        }
    }
    transPerLine.sortByOrder();
    //transPerLine.print();
}
bool isInIndex(vector<IndexStruct>& indexStruct, string& name, int i)
{
    vector<IndexStruct>::iterator iter;
    for(iter = indexStruct.begin(); iter != indexStruct.end(); iter++)
    {
        if(iter->name.compare(name) == 0)
        {
            iter->avail_index[i] = true;
            return true;
        }
    }
    return false;
}
HeaderNode<ITEM>** FpGrowth::getPreLink(string& name)
{
    if(headerTable)
    {
        for(int i=0;i<headerTableSize;i++)
        {
            if(name.compare(headerTable[i]->data.item) == 0)
            {
                return &headerTable[i];
            }
        }
    }
    return NULL;
}

void FpGrowth::insertIndex(vector<IndexStruct>& indexStruct, int i, string& name,void** parent)
{
    vector<IndexStruct>::iterator iter;
    for(iter = indexStruct.begin(); iter != indexStruct.end(); iter++)
    {
        if(iter->name.compare(name) == 0)
        {
            if(!transPerLine.all_bucket[i].empty())
            {
                iter->avail_index[i] = true;
            }
            return;
        }
    }

    IndexStruct a;
    a.name = name;
    a.numD = numD;
    a.parent = parent;
    //a.pre_link = reinterpret_cast<void**>(getPreLink(name));
    a.avail_index = new bool[numD];
    for(int j=0;j<numD;j++)
    {
        a.avail_index[j] = false;
    }
    if(!transPerLine.all_bucket[i].empty())
    {
        a.avail_index[i]= true;
    }
    indexStruct.push_back(a);
}


void FpGrowth::secondTimeScanConstructFPTree(IndexStruct& index)
{
    vector<IndexStruct> indexStruct;
    vector<IndexStruct>::iterator index_iter;
    for (int i = 0; i<numD; i++)
    {
        if(index.avail_index[i] == false)
        {
            continue;
        }
        if(transPerLine.all_bucket[i].empty())
        {
            continue;
        }
        vector<ITEM>::iterator iter = transPerLine.all_bucket[i].begin(); //only scan the begin
        //updata the parent in the tree
        TreeNode<ITEM>** p = reinterpret_cast<TreeNode<ITEM>**>(index.parent);
        TreeNode<ITEM>** parent = updataTree<ITEM>(p, iter->item);
        string old_name = iter->item;
        transPerLine.all_bucket[i].erase(iter);//erase the begin node
        void** p2 = reinterpret_cast<void**>(parent);
        insertIndex(indexStruct,i,old_name,p2);
    }

    for(index_iter = indexStruct.begin(); index_iter != indexStruct.end(); index_iter++)
    {
        secondTimeScanConstructFPTree(*index_iter);
    }
}
void insertIn(vector<ITEM>& list, string& name)
{
    vector<ITEM>::iterator iter;
    for(iter = list.begin(); iter != list.end(); iter++)
    {
        if(iter->item.compare(name) == 0)
        {
            iter->count++;
            return;
        }
    }
    ITEM a(name,1);
    list.push_back(a);
    return;
}

void updataTree2(AnyNode<ITEM>** inTree, vector<ITEM>& items, vector<IndexStruct>& indexs)
{
    if(inTree)
    {
        int size = items.size();
        if(size == 0)
        {
            return;
        }
        (*inTree)->childNodeNum = size;
        (*inTree)->childNode = new AnyNode<ITEM>*[size];

        for(int j=0;j<size;j++)
        {
            (*inTree)->childNode[j] =  new AnyNode<ITEM>;
        }

        vector<ITEM>::iterator iter = items.begin();
        vector<IndexStruct>::iterator index_iter = indexs.begin();

        for(int i = 0; iter != items.end()&&index_iter != indexs.end(); iter++, index_iter++,i++ )
        {
            (*inTree)->childNode[i]->data = *iter;
            //deal with head link
            //reinterpret_cast<HeaderNodeindex_iter->pre_link
            AnyNode<ITEM>** p = &(*inTree)->childNode[i];
            (*inTree)->childNode[i]->parent = (*inTree);
            if(index_iter->parent == NULL)
            {
                index_iter->parent = reinterpret_cast<void**>(p);
            }
        }
    }
}

void FpGrowth::secondTimeScanConstructFPTree2(IndexStruct& index)
{
    vector<IndexStruct> indexStruct;
    vector<IndexStruct>::iterator index_iter;
    vector<ITEM> items;
    vector<ITEM>::iterator item_iter;

    for (int i = 0; i<numD; i++)
    {
        if(index.avail_index[i] == false)
        {
            continue;
        }
        if(transPerLine.all_bucket[i].empty())
        {
            continue;
        }
        vector<ITEM>::iterator iter = transPerLine.all_bucket[i].begin(); //only scan the begin
        //生成items
        insertIn(items, iter->item);
        string old_name = iter->item;
        transPerLine.all_bucket[i].erase(iter);//erase the begin node
        insertIndex(indexStruct,i,old_name,NULL); //right now parent is NULL
    }
    //updata the parent in the tree

    updataTree2(reinterpret_cast<AnyNode<ITEM>**>(index.parent), items, indexStruct);

    for(index_iter = indexStruct.begin(); index_iter != indexStruct.end(); index_iter++)
    {
        secondTimeScanConstructFPTree2(*index_iter);
    }
}
void FpGrowth::runFpGrowth()
{
    firstTimeScan();
    IndexStruct index;
    index.avail_index = new bool[numD];
    for(int i=0;i<numD;i++)
    {
        index.avail_index[i] = true;
    }
    tree.root = new TreeNode<ITEM>;
    tree.root->data.item = "header";

    tree2.root = new AnyNode<ITEM>;
    tree2.root->data.item = "header";
    index.parent = reinterpret_cast<void**>(&tree2.root);
    //secondTimeScanConstructFPTree(index);
    secondTimeScanConstructFPTree2(index);

    tree2.print();
    //tree2.printIte(tree.root);
}