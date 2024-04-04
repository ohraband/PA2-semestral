//
// Created by Andy on 4. 6. 2021.
//

#ifndef SEMESTRAL_CSCREEN_H
#define SEMESTRAL_CSCREEN_H

#include <curses.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>


using namespace std;
/**
 * Class handling displaying to the terminal screen.
 * Utilizes ncurses library.
 */
class CScreen{
public:


    /**
     * Creates a new screen in a window and initializes the necessary parameters.
     */
    CScreen(){
        win = initscr(); //start screen
        raw(); //take input as is
        noecho(); //dont automatically write to screen
        cbreak(); //break on ctrl+c
        keypad(win, true); //register keys

        start_color();
        //list of color pairs
        init_pair(1, COLOR_WHITE, COLOR_BLACK); //default
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); //mc
        init_pair(3, COLOR_GREEN, COLOR_BLACK);  // source highlight
        init_pair(4, COLOR_RED, COLOR_BLACK); //target highlight
        init_pair(5, COLOR_WHITE, COLOR_WHITE); // obstacle
        init_pair(6, COLOR_CYAN, COLOR_BLACK); //player
        init_pair(7, COLOR_RED, COLOR_BLACK); //kc
        init_pair(8, COLOR_GREEN, COLOR_BLACK); //sbw
        init_pair(9, COLOR_MAGENTA, COLOR_BLACK); //dd

    }

    /**
     * Destructor ends the window and deletes it.
     */
    ~CScreen(){
        endwin();
        delwin(win);
    }

    /**
     * End the window and delete it.
     */
    void End() const;

    /**
     * Remove all objects from the screen.
     */
    void DeleteAll() const;

    /**
     * Refresh the screen to display changes.
     */
    void Refresh() const;

    /**
     * Wait a small amount of time until processing the next command.
     */
    void Sleep() const;

    /**
     * Displays a character on the screen and waits for user input to continue.
     * @param y - y coordinate (row number)
     * @param x - x coordinate (column number)
     * @param c - character to be displayed
     */
    void Show(int y,int x,char c) const;

    /**
     * Displays a string on the screen.
     * @param y - starting y coordinate (row number)
     * @param x - starting x coordinate (column number)
     * @param c - character to be displayed
     */
    void ShowString(int y,int x,const string& c) const;

    /**
     * Displays a character on the screen without waiting for user input to continue.
     * @param y - y coordinate (row number)
     * @param x - x coordinate (column number)
     * @param c - character to be displayed
     * @param color - number of the color pair to use
     */
    void QuickShow(int y,int x,char c, int color) const;


private:
    WINDOW *win;
};

















#endif //SEMESTRAL_CSCREEN_H