//
// Created by Li Yin Sulimowicz on 9/16/16.
//

#include "io_manager.h"
#include <vector>

double str2double(char const *  str)
{
    int x=0;
    double y=0;
    int j;
    int decimalnum=1;
    bool pointExist=false;
    bool bFirst = true;
    bool bNegative = false;
    while(*str)
    {
        if (*str>='0' && *str<='9')
        {
            if(pointExist)
            {
                j=(int)(*(str))-48;
                y=y+j*std::pow(0.1,decimalnum);
                decimalnum++;
            }
            else
            {
                x=x*10+*str-48;
            }
        }
        else if(*str=='.')
        {
            pointExist=true;
        }
        else if(*str=='-'&&bFirst)
        {
            bNegative = true;
            bFirst = false;
        }
        else
        {
            return -1;//unrecognize str
        }
        str++;
    }
    if(bNegative)
    {
        return -(x+y);
    }
    return x+y;
}


/*********************************DVector*********************************************/
DVector::DVector(int total)
{
    totalD = total;
    D_orig = new vector<int>[totalD];
}
DVector::DVector()
{
    totalD=0;
    D_orig = NULL;
}
DVector::~DVector()
{
    if(D_orig!= NULL)
    {
        delete[] D_orig;
        D_orig = NULL;
    }
}
DVector::DVector(const DVector& m)
{
    if(this != &m)
    {
        totalD = m.totalD;
        D_orig= new vector<int>[totalD];
        for(int i=0;i<totalD;i++)
        {
            D_orig[i].clear();
            vector<int>::iterator  ite = m.D_orig[i].begin();
            for(;ite!=m.D_orig[i].end();ite++)
            {
                D_orig[i].push_back(*ite);
            }
        }
    }

}
const DVector& DVector::operator=(const DVector& m)
{
    if(this != &m)
    {
        if(totalD!=0&&D_orig!=NULL)
        {
            delete[] D_orig;
            D_orig = NULL;
        }
        totalD = m.totalD;
        D_orig= new vector<int>[totalD];
        for(int i=0;i<totalD;i++)
        {
            D_orig[i].clear();
            vector<int>::iterator  ite = m.D_orig[i].begin();
            for(;ite!=m.D_orig[i].end();ite++)
            {
                D_orig[i].push_back(*ite);
            }
        }
    }
    return *this;
}

void DVector::deleteCol(const int col, int& minItemNo, int& maxItemNo)
{
    minItemNo = INT32_MAX;
    maxItemNo = -1;
    for(int i=0;i<totalD;i++)
    {
        D_orig[i].erase(D_orig[i].begin()+col); //col started from zero
        vector<int>::iterator iter = D_orig[i].begin();
        for(;iter!=D_orig[i].end();++iter)
        {
            if(*iter>maxItemNo)
                maxItemNo = *iter;
            if(*iter<minItemNo)
                minItemNo = *iter;
        }
    }
    return;

}
void DVector::print()
{
    for(int i=0;i<totalD;i++)
    {
        cout<<endl;
        cout<<"row = "<<i<<endl;
        vector<int>::iterator ite = D_orig[i].begin();
        for(;ite!= D_orig[i].end();ite++)
        {
            cout<<*ite<<"\t";
        }
        cout<<endl;
    }
}
//void AddOneRow(string& item);
void DVector::AddOneItem(int item, int index)
{
    if(index>=totalD)
    {
        cout<<"sorry, no enough space"<<endl;
        return;
    }
    D_orig[index].push_back(item);
}
bool DVector::FindInSingleD(int index, int& item)
{
    vector<int>::iterator ite = D_orig[index].begin();
    for(;ite!= D_orig[index].end();ite++)
    {
        if(*ite==item)
        {
            return true;
        }
    }
    return false;
}
/**************************************AItem********************************************************/
AItem::AItem()
{
    item = NULL;
    count =0;
    k=0;
}
AItem::AItem(int v)
{
    k=v;
    count =0;
    if(k>0)
    {
        item = new int[k];
        for(int i=0;i<k;i++)
        {
            item[i]=-1;
        }
    }
}
AItem::~AItem()
{
    if(item!=NULL&&k>0)
    {
        delete[] item;
        item = NULL;
    }
}
AItem::AItem(const AItem& m)
{
    if(this!=&m)
    {
        count =m.count;
        k=m.k;
        if(k>0)
        {
            item = new int[k];
            for(int i=0;i<k;i++)
            {
                item[i]=m.item[i];
            }
        }
    }
}
const AItem AItem::operator=(const AItem& m)
{
    if(&m!=this)
    {
        count=m.count;
        if(k>0&& item!=NULL)
        {
            delete[] item;
            item = NULL;
        }
        k=m.k;
        if(k>0)
        {
            item = new int[k];
            for(int i=0;i<k;i++)
            {
                item[i]=m.item[i];
            }
        }
    }
    return *this;
}

void insertByAscendOrder(int item[],int n,int value)
{
    int i=0;
    for(;i<n;)
    {
        if(item[i]!=-1&&value>item[i])
        {
            i++;
        }
        else
        {
            break;//insert at the 0th pos
        }
    }
    if(item[i]==-1)//insert directly
    {
        item[i]=value;
        return;
    }
    else//i֮���λ�������ƶ�
    {
        for(int j=n-1;j>i;j--)
        {
            if(item[j-1]!=-1)
            {
                item[j]=item[j-1];

            }
        }
        item[i]=value;
        return;
    }
}

void AItem::insertElem(int value) //it will insert by order
{
    insertByAscendOrder(item,k,value);
}
bool AItem::operator==(const AItem& m)//only comapre the item not the count
{
    for(int i=0;i<k;i++)
    {
        if(item[i]!=m.item[i])
        {
            return false;
        }
    }
    return true;
}
bool AItem::IsExisted(int value)
{
    for(int i=0;i<k;i++)
    {
        if(item[i]==value)
        {
            return true;
        }
    }
    return false;
}
AItem AItem::operator-(AItem& m2)
{
    AItem re(k-m2.k);
    if((k-m2.k)<=0)
    {
        return re;
    }
    for(int i=0;i<k;i++)
    {
        if(!m2.IsExisted(item[i]))
        {
            re.insertElem(item[i]);
        }
    }
    return re;
}
ostream& operator<<(ostream& out,const AItem& m)
{
    out<<endl;
    for(int i=0;i<m.k;i++)
    {
        out<<m.item[i]<<"\t";
    }
    out<<"count"<<m.count;
    out<<endl;
    return out;
}
/*************************Rule Item************************************************/

RuleItem::RuleItem()
{
    item_f = NULL;
    item_l=NULL;
    num_f=0;
    num_l=0;
    conf=0;
}
RuleItem::RuleItem(int f, int l)
{
    num_f=f;
    num_l=l;
    item_f = new int[num_f];
    item_l=new int[num_l];
    //init
    for(int i=0;i<num_f;i++)
    {
        item_f[i]=-1;
    }
    for(int i=0;i<num_l;i++)
    {
        item_l[i]=-1;
    }
    conf =0;
}
RuleItem::~RuleItem()
{
    if(item_f!=NULL)
    {
        delete[] item_f;
        item_f = NULL;
    }

    if(item_l!=NULL)
    {
        delete[] item_l;
        item_l = NULL;
    }
}

RuleItem::RuleItem(const RuleItem& m)
{
    if(this!=&m)
    {
        conf =m.conf;
        num_f=m.num_f;
        num_l=m.num_l;
        item_f = new int[num_f];
        item_l=new int[num_l];
        for(int i=0;i<num_f;i++)
        {
            item_f[i]=m.item_f[i];
        }

        for(int i=0;i<num_l;i++)
        {
            item_l[i]=m.item_l[i];
        }
    }
}
const RuleItem RuleItem::operator=(const RuleItem& m)
{
    RuleItem re;
    conf =m.conf;
    num_f=m.num_f;
    num_l=m.num_l;
    if(num_f!=0)
    {
        item_f = new int[num_f];
        for(int i=0;i<num_f;i++)
        {
            item_f[i]=m.item_f[i];
        }
    }
    if(num_l!=0)
    {
        item_l=new int[num_l];
        for(int i=0;i<num_l;i++)
        {
            item_l[i]=m.item_l[i];
        }
    }
    return re;
}
ostream& operator<<(ostream& out,const RuleItem& m)
{
    out<<endl;
    for(int i=0;i<m.num_f;i++)
    {
        out<<m.item_f[i]<<"\t";
    }
    out<<"-->";
    for(int j=0;j<m.num_l;j++)
    {
        out<<m.item_l[j];
    }
    out<<" conf: "<<m.conf<<endl;
    return out;
}
void RuleItem::insertElemF(int value)
{
    insertByAscendOrder(this->item_f,num_f,value);
}
void RuleItem::insertElemL(int value)
{
    insertByAscendOrder(this->item_l,num_l,value);
}

bool RuleItem::operator==(const RuleItem& m)
{
    if(num_f!=m.num_f || num_l!=m.num_l)
    {
        return false;
    }
    if(num_f>0)
    {
        for(int i=0;i<num_f;i++)
        {
            if(item_f[i]!=m.item_f[i])
            {
                return false;
            }
        }
    }
    if(num_l>0)
    {
        for(int i=0;i<num_l;i++)
        {
            if(item_l[i]!=m.item_l[i])
            {
                return false;
            }
        }
    }
    return true;
}

/******************************************AVector****************************************/
AVector::AVector(int v):k(v)
{
}
AVector::AVector()
{
}
AVector::~AVector()
{
}
bool AVector::IsEmpty()
{
    return V.empty()? true: false;
}
AVector::AVector(AVector& m)
{
    if(this!=&m)
    {
        k=m.k;
        V.clear();
        vector<AItem>::iterator ite = m.V.begin();
        for(;ite!=m.V.end();ite++)
        {
            V.push_back(*ite);
        }
    }
}
AVector AVector::operator=(AVector& m)
{
    if(this!=&m)
    {
        this->k=m.k;
        this->V.clear();
        vector<AItem>::iterator ite = m.V.begin();
        for(;ite!=m.V.end();ite++)
        {
            V.push_back(*ite);
        }
    }
    return *this;
}
ostream& operator<<(ostream& out,AVector& m)
{
    vector<AItem>::iterator ite = m.V.begin();
    for(;ite!=m.V.end();ite++)
    {
        out<<*ite;
    }
    return out;
}

bool AVector::IsItemStored(AItem& value)
{
    if(value.k!=k)
    {
        cout<<"size not same"<<endl;
        return true;
    }
    vector<AItem>::iterator ite = V.begin();
    for(;ite!=V.end();ite++)
    {
        if(*ite==value)
        {
            return true;
        }
    }
    return false;
}
double AVector::FindCountByItemValue(AItem& value)
{
    if(value.k!=k)
    {
        cout<<"size not same"<<endl;
        return -1;
    }
    vector<AItem>::iterator ite = V.begin();
    for(;ite!=V.end();ite++)
    {
        if(*ite==value)
        {
            return ite->count;
        }
    }
    return -1;
}

void AVector::AddItem(AItem value)
{
    if(value.k !=k)
    {
        cout<<"non avail k"<<endl;
        return;
    }
    if(IsItemStored(value))
    {
        //cout<<"it has been stored before"<<endl;
        return;
    }
    V.push_back(value);
}
void AVector::AddCountForItem(AItem& value)
{
    vector<AItem>::iterator ite = V.begin();
    for(;ite!=V.end();ite++)
    {
        if(*ite==value)
        {
            ite->count++;
            return;
        }
    }
    //cout<<"not found"<<endl;
}
/*******************************class RVector*********************************************************/
RVector::RVector(){}
RVector::RVector(RVector& m)
{
    if(this!=&m)
    {
        V.clear();
        vector<RuleItem>::iterator ite = m.V.begin();
        for(;ite!=m.V.end();ite++)
        {
            V.push_back(*ite);
        }
    }
}
RVector::~RVector(){}
RVector RVector::operator=(RVector& m)
{
    if(this!=&m)
    {
        vector<RuleItem>::iterator ite = m.V.begin();
        for(;ite!=m.V.end();ite++)
        {
            V.push_back(*ite);
        }
    }
    return *this;
}
ostream& operator<<(ostream& out,RVector& m)
{
    vector<RuleItem>::iterator ite = m.V.begin();
    for(;ite!=m.V.end();ite++)
    {
        out<<*ite<<" ";
    }
    return out;
}
bool RVector::IsItemStored(RuleItem& value)
{
    vector<RuleItem>::iterator ite = V.begin();
    for(;ite!=V.end();ite++)
    {
        if(*ite==value)
        {
            return true;
        }
    }
    return false;
}
void RVector::AddItem(RuleItem value) {
    if (IsItemStored(value)) {
        cout << "it has been stored before" << endl;
        return;
    }
    V.push_back(value);
}