// * https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c

#include "winSize.h"

#include <sys/ioctl.h>
#include <unistd.h>

int getWinRow(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return (int)w.ws_row;
}

int getWinCol(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return (int)w.ws_col;
}
