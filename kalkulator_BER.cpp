

#include "kalkulator_BER.h"


using namespace std;

int policzBadBits(char A, char B)
{
// compute number of different bits
    int liczbaBledow = 0;

    for (int i = 0; i < 8; i++) {

        // right shift both the numbers by 'i' and
        // check if the bit at the i'th position is different
        if (((A >> i) & 1) != ((B >> i) & 1)) {
            liczbaBledow++;
        }
    }
    return liczbaBledow;

}