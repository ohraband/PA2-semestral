//
// Created by Andy on 10. 6. 2021.
//

#include <filesystem>
#include <iostream>

#include "CStartMenu.h"


namespace fs = std::filesystem;
using namespace std;

/**
 * Starting main function.
 * Checks if necessary directories exist and starts menu.
 * @return 0 if they exist, -1 otherwise.
 */
int main(){

    string mapsdirectory = "examples/Maps/";
    string savesdirectory = "examples/Savefiles/";

    fs::directory_entry maps { mapsdirectory };
    if (!maps.exists()) {
       cout << "No Maps directory found!" << endl;
        return -1;
    }


    fs::directory_entry saves { savesdirectory };
    if (!saves.exists()) {
        cout << "No Savefiles directory found!" << endl;
        return -1;
    }

    CStartMenu menu(mapsdirectory, savesdirectory);
    menu.DefaultMenu();
    return 0;
}