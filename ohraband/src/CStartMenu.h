//
// Created by Andy on 9. 6. 2021.
//

#ifndef SEMESTRAL_CSTARTMENU_H
#define SEMESTRAL_CSTARTMENU_H


#include <iostream>
#include <fstream>
#include <string>
#include <set>


#include <filesystem>
#include <string>
#include <utility>
#include "CGame.h"

using namespace std;

/**
 * Class for handling what level to start.
 */
class CStartMenu{
public:

    /**
     * Creates a new Startmenu
     * @param mapsdirectory - directory with map levels
     * @param savesdirectory - directory with saved games
     */
    CStartMenu(string mapsdirectory, string savesdirectory) : mapsdirectory(std::move(mapsdirectory)), savesdirectory(std::move(savesdirectory)){
    };

    /**
     * Default destructor.
     */
    ~CStartMenu() = default;

    /**
     * First menu to choose whether to laod or start the game.
     */
    void DefaultMenu();

    /**
     * Menu for loading from a save file.
     * @param savesdirectory - directory with saved games
     * @return true if loading was successful, false otherwise.
     */
    bool LoadMenu(string savesdirectory);
    /**
     * Menu for creating a new game.
     * @param savesdirectory - directory with saved games
     * @param mapsdirectory - directory with map levels
     * @return true if creating a new game was successful, false otherwise.
     */
    bool NewGameMenu(string savesdirectory, string mapsdirectory );

private:
    string mapsdirectory;
    string savesdirectory;
};

#endif //SEMESTRAL_CSTARTMENU_H
