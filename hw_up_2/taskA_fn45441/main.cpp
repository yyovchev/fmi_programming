#include <iostream>

using namespace std;

void read_tab(int sums[2][11], int n);
bool check_tab(int sums[2][11], int n);

int main()
{
    int sums[2][11]{{0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0}};
    int n;
    cin>>n;

    read_tab(sums , n);
    bool flag = check_tab(sums , n);

    if (flag)
        cout<<"True";
    else
        cout<<"False";

    return 0;
}


void read_tab(int sums[2][11], int n){
    for(int i=1 ; i<=n ; i++){
        for (int j=1 ; j<=n ; j++){
            int in;
            cin>>in;
            sums[0][i] += in;
            sums[1][j] += in;
            if (i == j) sums[0][0] += in;
            if (i+j == n+1) sums[1][0] += in;
        }
    }
}

bool check_tab(int sums[2][11], int n){
    if (sums[0][0] != sums[1][0]) return false;

    for(int i = 0 ; i<n ; i++)
        if (sums[0][i] != sums[0][i+1] || sums[1][i] != sums[1][i+1])
            return false;

    return true;
}









