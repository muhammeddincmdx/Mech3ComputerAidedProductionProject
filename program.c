#include <ncurses.h>
#include <wiringPi.h>
#include <unistd.h>

#define signalPin 29
#define KEY_SPACE 32

int main(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    wiringPiSetup();
    pinMode(signalPin, OUTPUT);

    int signalState = 0; 

    while (1) {
        int ch = getch();
        if (ch == KEY_SPACE) {
            signalState = !signalState; 
            digitalWrite(signalPin, signalState);
            usleep(500000); 
        }
        usleep(10000); 
    }

    endwin();
    return 0;
}
