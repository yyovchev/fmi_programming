/*
    autor   :   yyovchev
    date    :   23.10.2017
    problem :   1
*/

#include <iostream>

using namespace std;

int main()
{
    unsigned int num;
    cin >> num;
    bool isTrion = true;

    int previous, middle, next;

    for (unsigned i = 0; i < num; i++){
        int in;
        cin>>in;

        if (i == 0){
            previous = in;
            continue;
        }
        if (i == 1){
            middle = in;
            continue;
        }
        if (i == 2){
            next = in;
        }
        else {
            previous = middle;
            middle = next;
            next = in;
        }


        bool conditions = false;

        conditions |= (middle >= previous) && (middle >= next);
        conditions |= (middle <= previous) && (middle <= next);

        isTrion &= conditions;

    }

    if (isTrion){
        cout<<"yes";
    }
    else{
        cout<<"no";
    }

    return 0;
}
