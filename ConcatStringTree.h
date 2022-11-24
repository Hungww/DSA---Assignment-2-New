#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ConcatStringTree {

public:
    class Node;
public:
    Node* root;

public:

    class ParentTree{
    public:
        int Size;
        class ParNode;          //PreDefine
    public:
        ParNode* root;
        //base
        ParentTree(){
            this->root= nullptr;
            Size=0;
        }
        ParentTree(int ID){
            this->root=new ParNode(ID);
            Size=1;
        }
        int height(ParNode* root){
            if(!root)return 0;
            else return root->h;
        }
        int getBalance(ParNode* root) {
            if (root == nullptr)
                return 0;
            return height(root->pLeft) - height(root->pRight);
        }
        void insertNode(int value){
            this->root= insertNode(this->root,value);
            Size++;
        }
        void deleteNode(int value){
            this->root= deleteNode(this->root,value);
            Size--;
        }


        int size() const{
            return this->Size;
        }

        string toStringPreOrder()const{
            string s="";
            s+="ParentsTree[";
            toStringPreOrder(this->root, s);
            s.erase(s.length()-1,1);
            s+="]";
            return s;
        };



        ~ParentTree(){
            if(this->root)cout<<"Delete a Node which still has ParNode";

        }

        //recur version
    protected:
    #define COUNT 10
        ParNode* getMaxOfLeft(ParNode* root);

        ParNode* rightRotate(ParNode* root);
        ParNode* leftRotate(ParNode* root);
        ParNode* insertNode(ParNode* root, int value);
        ParNode* deleteNode(ParNode* root, int value);
        void toStringPreOrder(ParNode* root, string& s)const;

    public:
        class ParNode{
        public:
            int KeyID;
            ParNode* pLeft;
            ParNode* pRight;
            int h;
            ParNode(int val){
                this->KeyID=val;
                pLeft=pRight= nullptr;
                h=1;
            }
        };


    };



    //NOTE




public:
    class Node{
    public:
        static int CURRENT_ID;
        long long LL;
        long long len;
        char* data;
        Node* pLeft;
        Node* pRight;
        ParentTree* ParTree;
        int ID;
        bool delData;

        Node(){
            LL=0;
            len=0;
            data=nullptr;
            pLeft=pRight= nullptr;
            if(CURRENT_ID==10000000)throw overflow_error("Id is overflow!");
            ID=CURRENT_ID;
            CURRENT_ID++;
            ParTree= new ParentTree(this->ID);
            delData=1;

        }
        Node(int flag){
            LL=0;
            len=0;
            data=nullptr;
            pLeft=pRight= nullptr;
            ID=CURRENT_ID;
            CURRENT_ID++;
            ParTree= new ParentTree();
            delData=1;
        }
        explicit Node(const char* s){
            LL=0;
            string stemp= s;
            this->len=stemp.size();
            data= new char[len+1];
            for(int i=0; i<len; i++){
                data[i]=stemp[i];
            }
            data[len]='\0';
            pLeft=pRight= nullptr;
            ID=CURRENT_ID;
            CURRENT_ID++;
            ParTree= new ParentTree(this->ID);
            delData=1;

        }
        //Copy data from another Node
        Node(const Node& base){
            this->LL=base.LL;
            this->len=base.len;
            string stemp= base.data;
            this->len=stemp.size();
            data= new char[len+1];
            for(int i=0; i<len; i++){
                data[i]=stemp[i];
            }
            data[len]='\0';
            pLeft=pRight= nullptr;
            ID=CURRENT_ID;
            CURRENT_ID++;
            ParTree= new ParentTree(this->ID);
            delData=1;


        }
        virtual ~Node(){
            delete ParTree;
            if(delData)
            delete data;
        }


    };




    //Base Version
    int getID(){
        return this->root->ID;
    }
    Node* getRoot(){
            return this->root;
    }
    explicit ConcatStringTree(const char * s);
    ConcatStringTree(const ConcatStringTree& base);
    ConcatStringTree(){
        this->root= new Node();
    }
    explicit ConcatStringTree(int i){           //To construct a null Concatstringtree
        this->root= nullptr;
    }
    int length() const;
    char get(int index){
        if(index>=this->length() || index<0 )throw out_of_range("Index of string is invalid!");
        else return get(this->root,index);
    };
    int indexOf(char c){
        return indexOf(root, c, 0);
    };
    string toStringPreOrder() const{
        string s="ConcatStringTree[";
        toStringPreOrder(this->root,s);
        s.erase(s.end()-1,s.end());
        s+="]";
        return s;
    };
    string toString() const{
        string s="";
        s+="ConcatStringTree[";
        s+='"';
        toString(this->root,s);
        s+='"';
        s+="]";
        return s;
    };
     ConcatStringTree concat(const ConcatStringTree & otherS) const;
     ConcatStringTree subString(int from, int to) const{
        if(from<0 || to>this->length())throw out_of_range("Index of string is invalid!");
        if(from>=to) throw logic_error("Invalid range!");
        ConcatStringTree temp(1);
        temp.root= subString(this->root,from,to-1,0);
        temp.reKey();
        return temp;
    };
     ConcatStringTree reverse() const{
        ConcatStringTree temp(1);
        temp.root= reverse(this->root,0);
        temp.reKey();
        return temp;
    };

    int getParTreeSize(const string & query) const{
        int slen= query.length();
        for(int i=0;i<slen;i++){
            if(query[i]!='l' && query[i]!='r') throw runtime_error("Invalid character of query");
        }
        return getParTreeSize(this->root,query,0,slen);
    };
    string getParTreeStringPreOrder(const string & query) const{
        int slen= query.length();
        for(int i=0;i<slen;i++){
            if(query[i]!='l' && query[i]!='r') throw runtime_error("Invalid character of query");
        }
        return getParTreeStringPreOrder(this->root,query,0,slen);
    };

    ~ConcatStringTree(){
        this->root->ParTree->deleteNode(this->root->ID);
        recurDestructor(this->root);
    }

    int getLL(){
        return this->root->LL;
    }
protected:
    void reKey(){
        reLen(this->root);
        reKey(this->root);
    }
//Recur version
protected:
    char get(Node* root, int index);
    int indexOf(Node* root, char& c, int curIndex);
    void toStringPreOrder(Node* root, string& s) const;
    void toString(Node* root, string& s) const;
     Node* subString(Node* root, int from, int to, int k) const;
     Node* reverse(Node* root,int k) const;                              //Return address of Root of new tree
    void recurDestructor(Node* &root);
    int getParTreeSize(Node* root,const string& s,int cur, int len) const;
    string getParTreeStringPreOrder(Node* root,const string& s,int cur, int len) const;

    int reLen(Node* root){
        if(!root)return 0;
        if(!root->data)
        root->len= reLen(root->pLeft)+ reLen(root->pRight);
        return root->len;
    };
    void reKey(Node*root){
        if(!root)return;
        if(root->data)return;
        if(root->pLeft)
            root->LL=root->pLeft->len;
        else
            root->LL=0;
        reKey(root->pLeft);
        reKey(root->pRight);
    };




};

class ReducedConcatStringTree; // forward declaration

class HashConfig {
public:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;
    HashConfig(int p, double c1, double c2,double lambda, double alpha, int initSize){
        this->p=p;
        this->c1=c1;    this->c2=c2;
        this->lambda=lambda;
        this->alpha=alpha;
        this->initSize=initSize;
    }

    friend class ReducedConcatStringTree;
    friend class LitStringHash;
};

class LitStringHash {
public:
    class LitString;
public:
    int LastInsertedIndex;
    LitString** HashTable;
    int currentsize;
    int capacity;


    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

public:
    LitStringHash(const HashConfig & hashConfig){
        this->p=hashConfig.p;
        this->c1=hashConfig.c1;    this->c2=hashConfig.c2;
        this->lambda=hashConfig.lambda;
        this->alpha=hashConfig.alpha;
        this->initSize=hashConfig.initSize;
        LastInsertedIndex=-1;
        HashTable= new LitString* [this->initSize];
        currentsize=0;
        capacity=this->initSize;
        for(int i=0;i<capacity;i++)HashTable[i]= nullptr;
    };
    ~LitStringHash(){
        if(this->HashTable){
            for(int i=0;i<this->capacity;i++)delete HashTable[i];
            delete[] HashTable;
        }
    }
    int sqr(int x) {
        return x*x;
    }
    int pow(int a, int b) {
        if (b == 0) return 1;
        else
        if (b % 2 == 0)
            return sqr(pow(a, b/2));
        else
            return a * (sqr(pow(a, b/2)));
    }
    int setKey(const char* s){
        int key=0;
        string str(s);
        int len=str.length();

        for(int i=0;i<len;i++){
            key+=str[i] * pow(this->p,i);
        }
        return  key;
    }
    int HashKey(const char* s){
        int key;
        string str(s);
        int len=str.length();

        for(int i=0;i<len;i++){
            key+=str[i] * pow(this->p,i);
        }
        key%=this->capacity;
        return key;
    }
    int HashKey(int key)const{
        key%=this->capacity;
        return key;
    }

    void reHash(int lastI){
        int oldCap= this->capacity;
        this->capacity= this->capacity * this->alpha;
        LitString** oldTable= this->HashTable;
        this->HashTable=new LitString* [this->capacity];
        for(int i=0;i<capacity;i++)HashTable[i]= nullptr;
        for(int i=0;i<oldCap;i++){
            if(oldTable[i]){
                int liidx=InsertForRehash(oldTable[i]);
                if(i==lastI)this->LastInsertedIndex=liidx;
            }
            oldTable[i]= nullptr;
        }
        for(int i=0;i<oldCap;i++)oldTable[i]= nullptr;

        delete[] oldTable;

    }
    LitString* Insert(const char* s){
        if(this->HashTable == nullptr){
            HashTable= new LitString* [this->initSize];
            currentsize=0;
            capacity=this->initSize;
            for(int i=0;i<capacity;i++)HashTable[i]= nullptr;
        }

        int key= setKey(s);
        int hashIndex= HashKey(key);
        string str1(s);
        int idx=0;

        for(int i=0;i< this->capacity;i++) {
            if (HashTable[i]) {
                string str2(HashTable[i]->data);
                if (str1 == str2) {
                    HashTable[i]->noRf += 1;
                    return HashTable[i];
                }
            }
        }
        double temp=0;
        for(int i=0;i<= this->capacity;i++){
            temp=hashIndex + this->c1*i + this->c2*i*i;
            idx=(int)temp;
            idx=idx%this->capacity;
            if(HashTable[idx]==nullptr){
                HashTable[idx]= new LitString(s,key);
                this->LastInsertedIndex=idx;
                currentsize++;
                LitString* temp=HashTable[idx];
                if((double(currentsize)/capacity)>lambda)reHash(idx);
                return temp;
                break;
            }
            else if(HashTable[idx]){
                string str2(HashTable[idx]->data);
                if(str1==str2){
                    HashTable[idx]->noRf+=1;
                    return HashTable[idx];
                }


            }
        }

        throw runtime_error("No possible slot");
    }
    void Remove(LitString* target){
        for(int i=0;i< this->capacity;i++){
            if(HashTable[i]==target && HashTable[i]->noRf==0){
                delete HashTable[i];
                HashTable[i]=nullptr;
                this->currentsize--;
                break;
            }

        }
        if(this->currentsize==0){
            delete[] this->HashTable;
            this->HashTable= nullptr;
        }
    }
    int InsertForRehash(LitString* s){
        if(this->HashTable == nullptr){
            HashTable= new LitString* [this->initSize];
            currentsize=0;
            capacity=this->initSize;
            for(int i=0;i<capacity;i++)HashTable[i]= nullptr;
        }
        int key= setKey(s->data);
        int hashIndex= HashKey(key);
        string str1(s->data);
        int idx=0;

        double temp=0;
        for(int i=0;i<= this->capacity;i++){
            temp=hashIndex + this->c1*i + this->c2*i*i;
            idx=(int)temp;
            idx=idx%this->capacity;
            if(HashTable[idx]==nullptr){
                HashTable[idx]= s ;

                return idx;
                break;
            }

        }

        throw runtime_error("No possible slot");

    }


    int getLastInsertedIndex() const{
        return this->LastInsertedIndex;
    };
    string toString() const{
        string s="LitStringHash[";
        for(int i=0;i<this->capacity;i++){
            if(HashTable[i]){
                s+="(litS=";
                s+='"';
                s+=HashTable[i]->data;
                s+='"';
                s+=");";
            }
            else s+="();";
        }
        s.erase(s.end()-1,s.end());
        s+="]";
        return s;
    };














    //Data
    class LitString{
    public:
        char* data;
        int key;
        int len;
        int noRf;

    public:

        LitString(const char* s, int key){
            noRf=1;
            string stemp= s;
            this->len=stemp.size();
            data= new char[len+1];
            for(int i=0; i<len; i++){
                data[i]=stemp[i];
            }
            data[len]='\0';
            this->key=key;


        };
        ~LitString(){
            delete this->data;
        }


    };

};

class ReducedConcatStringTree : public ConcatStringTree{
public:     class RNode;
    //Base
    ReducedConcatStringTree(LitStringHash* litStringHash, int i):ConcatStringTree(1){
        this->litStringHash=litStringHash;
    }
    ReducedConcatStringTree(LitStringHash* litStringHash):ConcatStringTree(1){
        this->litStringHash=litStringHash;
        this->root= new RNode(this->litStringHash);


    }
     ReducedConcatStringTree(const char * s, LitStringHash* litStringHash):ConcatStringTree(1){
        this->root= new RNode(s,litStringHash);
        this->litStringHash=litStringHash;
    }
    ReducedConcatStringTree subString(int from, int to) const{
        if(from<0 || to>this->length())throw out_of_range("Index of string is invalid!");
        if(from>=to) throw logic_error("Invalid range!");
        ReducedConcatStringTree temp(this->litStringHash,1);

        temp.root= subString(this->root,from,to-1,0);
        temp.reKey();

        return temp;
    };

    ReducedConcatStringTree reverse() const{
        ReducedConcatStringTree temp(this->litStringHash,1);
        temp.root= reverse(this->root,0);
        temp.reKey();
        return temp;
    };


    LitStringHash * litStringHash;

   ReducedConcatStringTree concat(const ReducedConcatStringTree &otherS) const;

   //Recur
   ConcatStringTree::Node* subString(Node *root, int from, int to, int k) const {
       if (!root)return nullptr;
       RNode* newNode;
       if(!k)
           newNode= new RNode(this-> litStringHash);
       else
           newNode= new RNode(this-> litStringHash,1);

       newNode->litStringHash=this->litStringHash;
       if (root->data) {
           long long size = to - from + 1;
           char *tmp = new char[size+1];
           for (int i = 0, j = from; i < size; i++, j++) {
               tmp[i] = root->data[j];
           }

           tmp[size] = '\0';
           newNode->LSData= newNode->litStringHash->Insert(tmp);
           newNode->data=newNode->LSData->data;
           newNode->len=size;
           newNode->LL = root->LL;
           return newNode;
       }
       if(to<root->LL){
           newNode->pLeft=subString(root->pLeft,from,to,1);
           if(newNode->pLeft)newNode->pLeft->ParTree->insertNode(newNode->ID);
       }
       else if(from>=root->LL){
           newNode->pRight= subString(root->pRight,from-root->LL,to-root->LL,1);
           if(newNode->pRight)newNode->pRight->ParTree->insertNode(newNode->ID);
       }
       else{
           newNode->pLeft= subString(root->pLeft,from,root->LL-1,1);
           if(newNode->pLeft)newNode->pLeft->ParTree->insertNode(newNode->ID);
           newNode->pRight= subString(root->pRight,0,to-root->LL,1);
           if(newNode->pRight)newNode->pRight->ParTree->insertNode(newNode->ID);
       }
       return newNode;
   }

    ConcatStringTree::Node* reverse(ConcatStringTree::Node *root,int k) const {
        if(!root)return nullptr;
        RNode* newNode;
        if(!k)
            newNode= new RNode(this-> litStringHash);
        else
            newNode= new RNode(this-> litStringHash,1);
        newNode->litStringHash=this->litStringHash;
        if(root->data){
            int size= root->len;
            char* tmp= new char[size+1];
            for(int i=0;i<size;i++){
                tmp[i]=root->data[size-i-1];
            }
            tmp[size]='\0';
            newNode->LSData= newNode->litStringHash->Insert(tmp);
            newNode->data=newNode->LSData->data;
            newNode->len=size;
            newNode->LL = root->LL;

        }

        newNode->pLeft= reverse(root->pRight,1);
        if(newNode->pLeft)newNode->pLeft->ParTree->insertNode(newNode->ID);
        newNode->pRight= reverse(root->pLeft,1);
        if(newNode->pRight)newNode->pRight->ParTree->insertNode(newNode->ID);

        return newNode;
    }


    class RNode:public Node{
    public:
        LitStringHash* litStringHash;
        LitStringHash::LitString* LSData;
        RNode(LitStringHash* litStringHash):Node(){
            this->litStringHash=litStringHash;
            this->LSData= nullptr;
            this->data= nullptr;
        };
        explicit RNode(const char* s, LitStringHash* litStringHash):Node(){
            //TODO: Process Data
            this->litStringHash=litStringHash;

            this->LSData=this->litStringHash->Insert(s);
            this->data=this->LSData->data;
            string str(this->data);
            this->len=str.length();
        }
        RNode(LitStringHash* litStringHash,int i):Node(1){
            this->litStringHash=litStringHash;
            this->LSData= nullptr;
            this->data= nullptr;
        };
        ~RNode(){
            if(LSData){
                delData=0;
                this->LSData->noRf-=1;
                if(this->LSData->noRf==0){
                    this->litStringHash->Remove(this->LSData);
                }

            }
        }

    };

};



#endif // __CONCAT_STRING_TREE_H__