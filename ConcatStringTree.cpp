#include "ConcatStringTree.h"
int ConcatStringTree::Node::CURRENT_ID=0;
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
        s+="(";
        s+=root->data;
        s+=",";
        s+= to_string(root->len);
        s+=")  ";
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

ConcatStringTree::Node* ConcatStringTree::reverse(ConcatStringTree::Node *root) const {
    if(!root)return nullptr;
    Node* newNode= new Node();
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

    newNode->pLeft= reverse(root->pRight);
    newNode->pRight= reverse(root->pLeft);

    return newNode;
}

ConcatStringTree::Node* ConcatStringTree::subString(ConcatStringTree::Node *root, int from, int to) const {
    if (!root)return nullptr;
    Node *newNode = new Node();
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
        newNode->pLeft=subString(root->pLeft,from,to);
    }
    else if(from>=root->LL){
        newNode->pRight= subString(root->pRight,from-root->LL,to-root->LL);
    }
    else{
        newNode->pLeft= subString(root->pLeft,from,root->LL-1);
        newNode->pRight= subString(root->pRight,0,to-root->LL);
    }
    return newNode;
}