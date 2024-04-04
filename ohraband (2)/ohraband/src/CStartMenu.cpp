
#include "CStartMenu.h"
#include "GameCheck.h"


void CStartMenu::DefaultMenu(){
    while(true){
        string input;
        cout << "Press \"n\" to start a new game." << endl;
        cout << "Press \"l\" to load game from a savefile." << endl;
        cout << "Press \"q\" to quit." << endl;
        cin >> input;
        if( input == "l" ){
            bool success = LoadMenu( savesdirectory);
            if(success){
                break;
            }
        }
        else if (input == "n"){
            bool success = NewGameMenu( savesdirectory,  mapsdirectory );
            if(success){
                break;
            }
        }
        else if (input == "q"){
            break;
        }
        else{
            cout << "Unknown command." << endl;
        }

    }
}

bool CStartMenu::LoadMenu(string savesdirectory){
            cout << "Please type the save name" << endl;
            cout << "Here are your saves: " << endl;
            for (const auto & entry : filesystem::directory_iterator(savesdirectory)){
                std::cout << entry.path().filename() << std::endl;
            }

            string loadname;
            cin >> loadname;
            string wholename = savesdirectory + loadname;

            if(CheckLoadMap(wholename)){
                auto* game = new CGame(savesdirectory, wholename);
                game->RunGame();
                delete game;
                return true;
            }
            else{
                cout << "Something went wrong!" << endl;
                return false;
            }
}

bool CStartMenu::NewGameMenu(string savesdirectory, string mapsdirectory ){
    cout << "Please type the map name" << endl;
    cout << "Here are your maps: " << endl;
    for (const auto & entry : filesystem::directory_iterator(mapsdirectory)){
        std::cout << entry.path().filename() << std::endl;
    }

    string loadname;
    cin >> loadname;
    string wholename = mapsdirectory + loadname;

    if(CheckViewItems(wholename) && CheckLines(wholename)){
        cout << "Choose difficulty (1,2,3): " << endl;
        int difficulty;
        cin >> difficulty;
        while(difficulty < 1 || difficulty > 3){
            cout << "Choose difficulty again (1,2,3): " << endl;
            cin >> difficulty;
        }
        auto* game = new CGame(savesdirectory, wholename, difficulty);
        game->RunGame();
        delete game;
        return true;
    }
    else{
        cout << "Something went wrong!" << endl;
        return false;
    }
}




