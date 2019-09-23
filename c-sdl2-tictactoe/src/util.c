#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/******************************************************************************/

/**
 * @brief Generate a random number
 * @param min   Minimum value
 * @param max   Maximum value
 * @return Generated random number
 */
int util_random_number( int min, int max )
{
    int low     = 0;
    int high    = 0;
    int result  = 0;

    if ( min < max )
    {
        low     = min;
        high    = max + 1;
    }
    else
    {
        low     = max + 1;
        high    = min;
    }

    const unsigned seed = (unsigned) time( NULL );
    srand( seed );

    result = (  ( rand( ) % ( high - low ) ) + low );

    return result;
}

/******************************************************************************/
