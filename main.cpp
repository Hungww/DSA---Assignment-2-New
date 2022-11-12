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
    ConcatStringTree* a= new ConcatStringTree("A");
    ConcatStringTree* b= new ConcatStringTree("B");
    ConcatStringTree* c= new ConcatStringTree("C");
    ConcatStringTree* d= new ConcatStringTree("D");
    ConcatStringTree* e= new ConcatStringTree("E");
    ConcatStringTree* s1=new ConcatStringTree(a->concat(*b));
    ConcatStringTree* s2=new ConcatStringTree(b->concat(*c));
    ConcatStringTree* s3=new ConcatStringTree( s1->concat(*s2));
    ConcatStringTree* s4=new ConcatStringTree( b->concat(*d));
    ConcatStringTree* s5=new ConcatStringTree(s3->concat(*s4));
    ConcatStringTree* s6=new ConcatStringTree( s2->concat(*e));
    ConcatStringTree* s7=new ConcatStringTree(s5->concat(*s6));
    ConcatStringTree* s8=new ConcatStringTree(s7->reverse());
    for(int i=0;i<9;i++){
        cout<<s8->get(i);
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

    cout << "\n ------------Delete 12----------- \n";
    root->ParTree->deleteNode(12);

}
void tc6(){
    ConcatStringTree s1("a");
    ConcatStringTree::Node* root=s1.getRoot();
    root->ParTree->insertNode(2);
    root->ParTree->insertNode(5);
    root->ParTree->insertNode(15);
    root->ParTree->insertNode(3);
    root->ParTree->insertNode(12);
    root->ParTree->insertNode(17);
    root->ParTree->insertNode(11);

    cout << "\n ------------Delete 3----------- \n";
    root->ParTree->deleteNode(3);

}

void tc7(){
    ConcatStringTree* a= new ConcatStringTree("A");
    ConcatStringTree* b= new ConcatStringTree("B");
    ConcatStringTree* c= new ConcatStringTree("C");
    ConcatStringTree* d= new ConcatStringTree("D");
    ConcatStringTree* e= new ConcatStringTree("E");
    ConcatStringTree* s1=new ConcatStringTree(a->concat(*b));
    ConcatStringTree* s2=new ConcatStringTree(b->concat(*c));
    ConcatStringTree* s3=new ConcatStringTree( s1->concat(*s2));
    ConcatStringTree* s4=new ConcatStringTree( b->concat(*d));
    ConcatStringTree* s5=new ConcatStringTree(s3->concat(*s4));
    ConcatStringTree* s6=new ConcatStringTree( s2->concat(*e));
    ConcatStringTree* s7=new ConcatStringTree(s5->concat(*s6));
    delete s7;
    delete s6;

    cout<<"Success";
}
void tc8(){
    ConcatStringTree* t1 = new ConcatStringTree("a");
    ConcatStringTree* t2 = new ConcatStringTree("b");
    ConcatStringTree* t3 = new ConcatStringTree("c");
    ConcatStringTree* s0 = new ConcatStringTree(t1->concat(*t2));
    ConcatStringTree* s1 = new ConcatStringTree(t2->concat(*t3));
    ConcatStringTree* s2 = new ConcatStringTree(s0->concat(*s1));

    delete t1;

    delete t2;


    delete t3;

    delete s0;

    delete s1;

    delete s2;
}
void tc9(){
    ConcatStringTree* s4_1= new ConcatStringTree("Hello");
    ConcatStringTree* s4_2= new ConcatStringTree(",_this");
    ConcatStringTree* s4_3= new ConcatStringTree(s4_1->concat(*s4_2));
    ConcatStringTree* s4_4= new ConcatStringTree(s4_2->concat(*s4_1));
    ConcatStringTree* s4_5= new ConcatStringTree(s4_3->concat(*s4_4));
    cout<<s4_5->toString();
    delete s4_3;
    delete s4_4;
    delete s4_5;

}
int main() {

    //TODO: Delete utility funct (PrintTree,...)
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_t");
    ConcatStringTree s3 = s1.concat(s2);
    cout << s3.toStringPreOrder() << endl;
    cout << s3.toString() << endl;
     cout << s3.subString(5, 6).toString() << endl;
    cout << s3.reverse().toString() << endl;
    cout<<s3.toString()<<endl;
    cout<<s3.getParTreeSize("lr");
    return 0;

}