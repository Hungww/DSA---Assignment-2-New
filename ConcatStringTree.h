#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ConcatStringTree {

public:
    class Node;
protected:
    Node* root;

public:

    class ParentTree{
    public:
        class ParNode;          //PreDefine
    public:
        ParNode* root;
        //base
        ParentTree(int ID){
            this->root=new ParNode(ID);
        }
        int height(ParNode* root){
            if(!root)return 0;
            else return root->h;
        }
        void Insert(int value){
            this->root= Insert(this->root,value);
        }
        void print2DUtil(){
            print2DUtil(this->root,0);
        }

        //recur version
    protected:
#define COUNT 10
        void print2DUtil(ParNode* root, int space){
            if (root == NULL)
                return;
            space += COUNT;

            print2DUtil(root->pRight, space);
            cout << endl;

            for (int i = COUNT; i < space; i++)
                cout << " ";
            cout << root->KeyID<< " (" << root->h << ") " << "\n";

            print2DUtil(root->pLeft, space);
        }
        ParNode* rightRotate(ParNode* root){
            ParNode* x = root->pLeft;


            root->pLeft = x->pRight;
            x->pRight = root;

            // Thiết lập chiều cao
            root->h = 1 + max(height(root->pLeft), height(root->pRight));
            x->h = 1 + max(height(x->pLeft), height(x->pRight));

            // Return x - trả về root mới
            return x;
        };
        ParNode* leftRotate(ParNode* root) {
            ParNode* y = root->pRight;

            // Bắt đầu quay trái
            root->pRight = y->pLeft;
            y->pLeft = root;

            // Thiết lập chiều cao
            root->h = 1 + max(height(root->pLeft), height(root->pRight));
            y->h = 1 + max(height(y->pLeft), height(y->pRight));

            // Return y - trả về root mới
            return y;
        }

        ParNode* Insert(ParNode* root, int value) {
            // 1. Insert
            if (root == NULL)
                return new ParNode(value); // Trả về Node có height = 1
            if (value > root->KeyID)
                root->pRight = Insert(root->pRight, value);
            else if (value < root->KeyID)
                root->pLeft = Insert(root->pLeft, value);
            else
                return root; // Neu bang thi khong them

            // 2. Set height
            root->h = 1 + max(height(root->pLeft), height(root->pRight));

            // 3. Rotate
            int valBalance = height(root->pLeft) - height(root->pRight);

            // Kiểm tra 4 TH xảy ra:
            // 3.1. Left left
            if (valBalance > 1 && value < root->pLeft->KeyID)
                return rightRotate(root);

            // 3.2. Right Right
            if (valBalance < -1 && value > root->pRight->KeyID)
                return leftRotate(root);

            // 3.3. Left Right
            if (valBalance > 1 && value > root->pLeft->KeyID) {
                root->pLeft = leftRotate(root->pLeft);
                return rightRotate(root);
            }

            // 3.4. Right Left
            if (valBalance < -1 && value < root->pRight->KeyID) {
                root->pRight = rightRotate(root->pRight);
                return leftRotate(root);
            }

            return root;
        }

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
        toString(this->root,s);
        return s;
    };
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const{
        ConcatStringTree temp(1);
        temp.root= subString(this->root,from,to-1);
        temp.reKey();
        return temp;
    };
    ConcatStringTree reverse() const{
        ConcatStringTree temp(1);
        temp.root= reverse(this->root);
        temp.reKey();
        return temp;
    };

    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;

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
    Node* subString(Node* root, int from, int to) const;
    Node* reverse(Node* root) const;                              //Return address of Root of new tree

    int getParTreeSize(Node* root) const;
    string getParTreeStringPreOrder(Node* root) const;

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

    friend class ReducedConcatStringTree;
};

class ReducedConcatStringTree /* */ {

public:
    class LitStringHash {
    public:
        LitStringHash(const HashConfig & hashConfig);
        int getLastInsertedIndex() const;
        string toString() const;
    };

public:
    static LitStringHash litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__