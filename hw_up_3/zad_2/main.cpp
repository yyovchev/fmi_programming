#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand((int) time(0));
    const char *words[3];
    words[0] = new char[4];
    words[0] = "dog";
    words[1] = new char[4];
    words[1] = "cat";
    words[2] = new char[4];
    words[2] = "cow";

    int n = rand() % 3;
    cout<<rand()<<"  "<<rand()<<endl;
    cout<<words[n]<<endl;
    return 0;
}