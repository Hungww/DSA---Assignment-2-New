#include "ConcatStringTree.h"
void tc1(){
    ConcatStringTree* s1= new ConcatStringTree("Hell");
    ConcatStringTree* s2= new ConcatStringTree("World");
    ConcatStringTree* s3= new ConcatStringTree(s1->concat(*s2));
    cout<<s3->indexOf('o');
}
void tc2(){
    ConcatStringTree* d1= new ConcatStringTree("Hello");
    ConcatStringTree* d2= new ConcatStringTree(",_t");
    ConcatStringTree* d3= new ConcatStringTree("his_is");
    ConcatStringTree* d4= new ConcatStringTree("_an");
    ConcatStringTree* s1= new ConcatStringTree(d1->concat(*d2));
    ConcatStringTree* s2= new ConcatStringTree(d3->concat(*d4));
    ConcatStringTree* s3= new ConcatStringTree(s1->concat(*s2));
    delete s1;
    delete s3;
    delete d1;
    cout<<endl;

}
void tc3(){
    ConcatStringTree a("A");
    ConcatStringTree b("B");
    ConcatStringTree c("C");
    ConcatStringTree d("D");
    ConcatStringTree e("E");
    ConcatStringTree s1=a.concat(b);
    ConcatStringTree s2=b.concat(c);
    ConcatStringTree s3= s1.concat(s2);
    ConcatStringTree s4= b.concat(d);
    ConcatStringTree s5=s3.concat(s4);
    ConcatStringTree s6= s2.concat(e);
    ConcatStringTree s7=s5.concat(s6);
    ConcatStringTree s8=s7.reverse();
    for(int i=0;i<9;i++){
        cout<<s8.get(i);
    }
}
void tc4(){
    ConcatStringTree a("A");
    ConcatStringTree b("B");
    ConcatStringTree c("C");
    ConcatStringTree d("D");
    ConcatStringTree e("E");
    ConcatStringTree s1=a.concat(b);
    ConcatStringTree s2=b.concat(c);
    ConcatStringTree s3= s1.concat(s2);
    ConcatStringTree s4= b.concat(d);
    ConcatStringTree s5=s3.concat(s4);
    ConcatStringTree s6= s2.concat(e);
    ConcatStringTree s7=s5.concat(s6);
    ConcatStringTree s8=s5.subString(0,6);
    cout<<s8.toString();

}
void tc5(){
    ConcatStringTree s1("a");
    ConcatStringTree::Node* root=s1.getRoot();
    root->ParTree->insertNode(18);
    root->ParTree->insertNode(12);
    root->ParTree->insertNode(30);
    root->ParTree->insertNode(25);
    root->ParTree->insertNode(69);
    root->ParTree->insertNode(23);
    root->ParTree->print2DUtil();
    cout << "\n ------------Delete 12----------- \n";
    root->ParTree->deleteNode(12);
    root->ParTree->print2DUtil();
}
void tc6(){
    ConcatStringTree s1("a");
    ConcatStringTree::Node* root=s1.getRoot();
    root->ParTree->insertNode(10);
    root->ParTree->insertNode(5);
    root->ParTree->insertNode(15);
    root->ParTree->insertNode(3);
    root->ParTree->insertNode(12);
    root->ParTree->insertNode(17);
    root->ParTree->insertNode(11);
    root->ParTree->print2DUtil();
    cout << "\n ------------Delete 3----------- \n";
    root->ParTree->deleteNode(3);
    root->ParTree->print2DUtil();
}


int main() {
    tc6();
    return 0;
}