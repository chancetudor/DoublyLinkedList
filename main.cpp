#include <iostream>
using namespace std;
#include "dList.cpp"
#define SMALL 200
#define MAX 100000
#define ROUNDS 100
int main(){
    int i, x[MAX];
    char ch[MAX];

    for(i=0;i<SMALL;i++) {
      x[i] = (2*SMALL)-i;
      ch[i] = 'a' + (i % 26);
    }
    dList A(x,ch,SMALL), B;
    A.out(10);
    node *tmp = A.search(2*SMALL-8);
    A.moveFront(tmp);
    A.out(10);
    A.moveBack(tmp);
    A.out(10);
    A.find('b');
    A.sort();
    A.out(10);
    A.out(10,'b');
    A.addBack(500,'d');
    A.addFront(501,'z');
    A.out(10);
    A.out(10,'b');
    B.addFront(1,'a');
    B.addBack(2,'b');
    B.out(2);

    for(int j=0; j<ROUNDS; j++){
      cout << endl << "round " << j << endl;
      for(i=0;i<MAX;i++) {x[i] = 2*MAX-i; ch[i] = 'a'+ (i%26);}
      dList A(x,ch,MAX);
      node *tmp = A.search(2*MAX-8);
      A.moveFront(tmp);
      A.moveBack(tmp);
      A.sort();
      A.out(10);
      A.out(10,'b');
    }
}
