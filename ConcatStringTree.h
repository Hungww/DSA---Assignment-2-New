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
        Node(){
            LL=0;
            len=0;
            data=nullptr;
            pLeft=pRight= nullptr;
            ID=CURRENT_ID;
            CURRENT_ID++;
            ParTree= new ParentTree(this->ID);

        }
        Node(int flag){
            LL=0;
            len=0;
            data=nullptr;
            pLeft=pRight= nullptr;
            ID=CURRENT_ID;
            CURRENT_ID++;
            ParTree= new ParentTree();
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


        }
        ~Node(){
            delete ParTree;
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

        toString(this->root,s);
        s+="]";
        return s;
    };
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const{
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
    string getParTreeStringPreOrder(const string & query) const;

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
    string getParTreeStringPreOrder(Node* root,const string& s) const;

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
private:
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
public://PreDefine
    class LitString;
public:
    int LastInsertedIndex;
    LitString** HashTable;
    int currentsize;
    const HashConfig*  CONFIG;

public:
    LitStringHash(const HashConfig & hashConfig){
        CONFIG=&hashConfig;
        LastInsertedIndex=-1;
        HashTable= new LitString* [CONFIG->initSize];
        currentsize=CONFIG->initSize;
    };
    int getLastInsertedIndex() const;
    string toString() const;














    //Data
    class LitString{
    public:
        char* data;
        int len;
        int noRf;

    public:

        LitString(const char* s){
            noRf=1;
            string stemp= s;
            this->len=stemp.size();
            data= new char[len+1];
            for(int i=0; i<len; i++){
                data[i]=stemp[i];
            }
            data[len]='\0';

        };

    };

};

class ReducedConcatStringTree /* */ {
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    LitStringHash * litStringHash;
};



#endif // __CONCAT_STRING_TREE_H__