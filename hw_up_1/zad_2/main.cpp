#include <iostream>

#define COLLECTING_ONES     1
#define COLLECTING_ZEROS    0

int main()
{
    unsigned int num;
    std::cin >> num;

    bool state = COLLECTING_ZEROS;

    for(int n = 0, i = 31; i>=0; i--, n++){
        unsigned int current_bit = (num >> i)&(0x1);

        if( num >> i ){

            if (state != current_bit){
                state = current_bit;
                n = current_bit;
            }
            else if ( n%2 != state){
                current_bit = (current_bit|0x1)<<i;

                if (n%2 == 1)
                    num |= current_bit;
                else
                    num &= (0xFF ^ current_bit);
            }
        }
    }

    std::cout<<num;

    return 0;
}
