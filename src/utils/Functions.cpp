// Included headers
#include "utils/Functions.h"

template <class type>
short sign(type n)
{
    return ((n < 0) * -2) + 1;
}