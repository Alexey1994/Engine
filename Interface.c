#include "Interface.h"

#ifdef WIN32

char key(char key)
{
    if(GetAsyncKeyState(key)) return 1;
    return 0;
}

#endif //WIN32

#ifdef __linux__

char key(char key)
{
    return 0;
}

#endif //LINUX
