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

//ParentTree
void ConcatStringTree::ParentTree::print2DUtil(ParNode* root, int space) {
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

ConcatStringTree::ParentTree::ParNode *ConcatStringTree::ParentTree::rightRotate(ConcatStringTree::ParentTree::ParNode *root) {
    ParNode* x = root->pLeft;
    root->pLeft = x->pRight;
    x->pRight = root;

    // Thiết lập chiều cao
    root->h = 1 + max(height(root->pLeft), height(root->pRight));
    x->h = 1 + max(height(x->pLeft), height(x->pRight));

    // Return x - trả về root mới
    return x;
}

ConcatStringTree::ParentTree::ParNode *ConcatStringTree::ParentTree::leftRotate(ConcatStringTree::ParentTree::ParNode *root){
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

ConcatStringTree::ParentTree::ParNode *ConcatStringTree::ParentTree::Insert(ConcatStringTree::ParentTree::ParNode *root,
                                                                            int value) {

    // 1. Insert
    if (!root)
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


