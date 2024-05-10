# Mech3ComputerAidedProductionProject
This project for practicing using pneumatic cylinder with control units. I use raspberry pi 4 and write control code in c languages. I use solenoid valve and relay for controlling parts.





## Code
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


## Shematics
![Ekran görüntüsü 2024-05-10 094828](https://github.com/muhammeddincmdx/Mech3ComputerAidedProductionProject/assets/54439858/c2fec999-0215-414e-8b2c-6ea3c973b231)


