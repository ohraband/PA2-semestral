//
// Created by Andy on 4. 6. 2021.
//

#include "CScreen.h"

using namespace std;

void CScreen::End() const{
    endwin();
    delwin(win);
}

void CScreen::DeleteAll() const{
    clear();
    refresh();
}

void CScreen::Refresh() const{
    refresh();
}

void CScreen::Sleep() const{
    usleep(93456); //microseconds
}

void CScreen::Show(int y, int x, const char c) const{
    //display character
    move(y,x);
    printw("%c",c);
    refresh();

    //wait for input
    getch();
}


void CScreen::ShowString(int y, int x, const string& c) const{
    move(y,x++);
    for(auto a : c){
        printw("%c",a);
        move(y,x++);
    }
    refresh();
}

void CScreen::QuickShow(int y, int x, char c, int color = 1) const{
    //display character with color
    attron(COLOR_PAIR(color));
    move(y,x);
    printw("%c",c);
    refresh();
    //remove color setting
    attroff(COLOR_PAIR(color));
}


