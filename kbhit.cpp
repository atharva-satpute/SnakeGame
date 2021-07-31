#include "kbhit.hpp"
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/select.h>

static const int STDIN{0};
static bool initialized{false};
termios term,finish;

/*  Function to take input from user without pressing Enter/Return for linux.
    Same as _kbhit() in conio.h header file which works only in windows.
*/
int _kbhit(){
    if(!initialized){
        // Used terminos to turn off line buffering
        tcgetattr(STDIN,&finish);
        term = finish;
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN,TCSANOW,&term);
        setbuf(stdin,NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void kbhit_finish()
{
    tcsetattr(STDIN, TCSANOW, &finish);
    initialized = false;
}