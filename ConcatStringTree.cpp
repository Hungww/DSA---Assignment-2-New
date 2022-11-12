#include "ConcatStringTree.h"
int ConcatStringTree::Node::CURRENT_ID=1;
ConcatStringTree::ConcatStringTree(const char * s){
    this->root= new Node(s);
}

ConcatStringTree::ConcatStringTree(const ConcatStringTree &base) {
    this->root= new Node(*base.root);
}

int ConcatStringTree::length() const {
    return this->root->len;
}

void ConcatStringTree::toString(ConcatStringTree::Node *root, std::string &s) const {
    if(!root)return;
    if(root->data){

        s+=root->data;


    }
    toString(root->pLeft,s);
    toString(root->pRight,s);
}

char ConcatStringTree::get(ConcatStringTree::Node *root, int index) {
    if(root->data)return root->data[index];
    else{
        if(index>=root->LL)return get(root->pRight, index - root->LL);
        else if (index<root->LL) return get(root->pLeft, index);
    }
    return ' ';
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree &otherS) const {
    ConcatStringTree temp;
    temp.root->pLeft=this->root;
    temp.root->pRight=otherS.root;
    temp.root->len=this->length()+otherS.length();
    temp.root->LL=temp.root->pLeft->len;
    temp.root->pLeft->ParTree->insertNode(temp.root->ID);
    temp.root->pRight->ParTree->insertNode(temp.root->ID);
    return temp;
}

int ConcatStringTree::indexOf(ConcatStringTree::Node *root, char &c, int curIndex) {
    if(!root)return -1;
    else if(root->data){
        for(int i=0; i< root->len;i++){
            if(root->data[i]==c)return i+curIndex;
        }
        return -1;
    }
    int res1= indexOf(root->pLeft,c,curIndex);
    int res2= indexOf(root->pRight,c,curIndex+root->LL);
    if(res1==-1)return res2;
    else return res1;
}

void ConcatStringTree::toStringPreOrder(ConcatStringTree::Node *root, std::string &s) const {
    if(!root)return;

    //PROCESS
    s+="(LL=";
    s+= to_string(root->LL);
    s+=",L=";
    s+= to_string(root->len);
    s+=',';
    if(root->data){
        s+='"';
        s+=root->data;
        s+='"';
    }
    else{
        s+="<NULL>";
    }
    s+=");";
    //END PROCESS

    toStringPreOrder(root->pLeft,s);
    toStringPreOrder(root->pRight,s);

}

ConcatStringTree::Node* ConcatStringTree::reverse(ConcatStringTree::Node *root,int k) const {
    if(!root)return nullptr;
    Node* newNode;
    if(!k)
        newNode= new Node();
    else
        newNode= new Node(1);
    if(root->data){
        int size= root->len;
        char* tmp= new char[size+1];
        for(int i=0;i<size;i++){
            tmp[i]=root->data[size-i-1];
        }
        tmp[size]='\0';
        newNode->data=tmp;
        newNode->len=size;
        newNode->LL=root->LL;

    }

    newNode->pLeft= reverse(root->pRight,1);
    if(newNode->pLeft)newNode->pLeft->ParTree->insertNode(newNode->ID);
    newNode->pRight= reverse(root->pLeft,1);
    if(newNode->pRight)newNode->pRight->ParTree->insertNode(newNode->ID);

    return newNode;
}

ConcatStringTree::Node* ConcatStringTree::subString(ConcatStringTree::Node *root, int from, int to, int k) const {
    if (!root)return nullptr;
    Node* newNode;
    if(!k)
        newNode= new Node();
    else
        newNode= new Node(1);
    if (root->data) {
        int size = to - from + 1;
        char *tmp = new char[size+1];
        for (int i = 0, j = from; i < size; i++, j++) {
            tmp[i] = root->data[j];
        }
        tmp[size] = '\0';
        newNode->data = tmp;
        newNode->len = size;
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

//ParentTree


ConcatStringTree::ParentTree::ParNode *ConcatStringTree::ParentTree::rightRotate(ConcatStringTree::ParentTree::ParNode *root) {
    ParNode* x = root->pLeft;
    root->pLeft = x->pRight;
    x->pRight = root;



    root->h = 1 + max(height(root->pLeft), height(root->pRight));
    x->h = 1 + max(height(x->pLeft), height(x->pRight));


    return x;
}

ConcatStringTree::ParentTree::ParNode *ConcatStringTree::ParentTree::leftRotate(ConcatStringTree::ParentTree::ParNode *root){
    ParNode* y = root->pRight;


    root->pRight = y->pLeft;
    y->pLeft = root;


    root->h = 1 + max(height(root->pLeft), height(root->pRight));
    y->h = 1 + max(height(y->pLeft), height(y->pRight));


    return y;
}

ConcatStringTree::ParentTree::ParNode *ConcatStringTree::ParentTree::insertNode(ConcatStringTree::ParentTree::ParNode *root,
                                                                                int value) {


    if (!root)
        return new ParNode(value);
    if (value > root->KeyID)
        root->pRight = insertNode(root->pRight, value);
        else if (value < root->KeyID)
            root->pLeft = insertNode(root->pLeft, value);
        else if(value==root->KeyID) //No duplicate accept
            return root;
        else return root; //Never happen


    int leftH=height(root->pLeft);
    int rightH=height(root->pRight);
    if(leftH>rightH)root->h=leftH+1;
        else root->h=rightH+1;



    int valBalance = getBalance(root);


    if (valBalance > 1 && getBalance(root->pLeft)>=0)
        return rightRotate(root);


    if (valBalance < -1 && getBalance(root->pRight)<=0)
        return leftRotate(root);


    if (valBalance > 1 && getBalance(root->pLeft)<0) {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }


    if (valBalance < -1 && getBalance(root->pRight)>0) {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }

    return root;
}
ConcatStringTree::ParentTree::ParNode* ConcatStringTree::ParentTree::getMaxOfLeft(
        ConcatStringTree::ParentTree::ParNode *root){
    if(!root->pRight)return root;
    else return getMaxOfLeft(root->pRight);
};
ConcatStringTree::ParentTree::ParNode* ConcatStringTree::ParentTree::deleteNode(ConcatStringTree::ParentTree::ParNode *root,
                                                                            int value){
    if(!root)return root;
    else if(root->KeyID > value)root->pLeft=deleteNode(root->pLeft,value);
    else if(root->KeyID < value)root->pRight=deleteNode(root->pRight,value);
    else{
        if(root->pLeft && root->pRight){
            ParNode* temp= getMaxOfLeft(root->pLeft);
            root->KeyID=temp->KeyID;
            root->pLeft=deleteNode(root->pLeft, temp->KeyID);
            return root;
        }
        else if(!root->pLeft){
            ParNode* temp= root->pRight;
            delete root;
            return temp;
        }
        else if(!root->pRight){
            ParNode* temp= root->pLeft;
            delete root;
            return temp;
        }
    }

    int leftH=height(root->pLeft);
    int rightH=height(root->pRight);
    if(leftH>rightH)root->h=leftH+1;
    else root->h=rightH+1;

    int valBalance = getBalance(root);


    if (valBalance > 1 && getBalance(root->pLeft) >= 0)
        return rightRotate(root);


    if (valBalance < -1 && getBalance(root->pRight) <= 0)
        return leftRotate(root);


    if (valBalance > 1 && getBalance(root->pLeft) < 0){
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }


    if (valBalance < -1 && getBalance(root->pRight) > 0){
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }


    return root;

}void ConcatStringTree::recurDestructor(ConcatStringTree::Node *&root) {
    {
        if(!root)return;
        if(root->ParTree->Size!=0)return;
        else{
            if(root->pLeft)root->pLeft->ParTree->deleteNode(root->ID);
            if(root->pRight)root->pRight->ParTree->deleteNode(root->ID);
            recurDestructor(root->pLeft);
            recurDestructor(root->pRight);

            delete root;
            root= nullptr;
        }
    }
}

void ConcatStringTree::ParentTree::toStringPreOrder(ConcatStringTree::ParentTree::ParNode *root,
                                                      std::string &s) const {
    if(!root)return;

    //Process
    s+="(id=";
    s+= to_string(root->KeyID);
    s+=");";
    //End Process

    toStringPreOrder(root->pLeft,s);
    toStringPreOrder(root->pRight,s);
}

int ConcatStringTree::getParTreeSize(ConcatStringTree::Node* root, const std::string &s, int cur, int len) const {
    if(!root)throw runtime_error("Invalid query: reaching NULL");
    if(cur<len){
        if(s[cur]=='l')return getParTreeSize(root->pLeft,s, cur+1,len);
        else return getParTreeSize(root->pRight,s, cur+1,len);
    }
    else{
        return root->ParTree->size();
    }
}



