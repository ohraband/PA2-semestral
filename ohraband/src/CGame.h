//
// Created by Andy on 7. 6. 2021.
//

#ifndef SEMESTRAL_CGAME_H
#define SEMESTRAL_CGAME_H

#include "CHuman.h"
#include "CComputer.h"
#include "CScreen.h"

#include <utility>
#include <vector>
#include <string>

using namespace std;

/**
 * Class CGame controls the run of the entire gameplay from the moment a file is chosen until the winning screen.
 */
class CGame{
public:
    /**
     * Creates a new Game from a savefile
     * @param savedir - directory to save the game into
     * @param loadfilename - name of the file to load
     */
    CGame(string savedir , const string& loadfilename ) : savedir(std::move(savedir)), map(LoadMap(loadfilename).first) , establishmentcount(map.GetEstablishmentList().size()),
                                                                   difficulty(LoadMap(loadfilename).second){
        LoadGame(loadfilename);
        map.Show();
    };


    /**
     * Creates a new Game from based on a map.
     * @param savedir - directory to save the game into
     * @param mapfilename - name of the file to load
     * @param difficulty - difficulty of the Computer
     */
    CGame(string savedir , const string& mapfilename, int difficulty ) : savedir(std::move(savedir)), map(mapfilename), establishmentcount(map.GetEstablishmentList().size()),
                                                                         difficulty(difficulty){
        map.Show();

    };
    /**
     * Destructor for CGame
     * deletes all the players.
     */
    ~CGame(){
        for(auto p : players){
            delete p;
        }

    };

    /**
     * Handles all running of the game from start to end.
     */
    void RunGame();

    /**
     * Checks if a player has won the game.
     * @return true if the player has won the game, false otherwise.
     */
    bool Win() const;

    /**
     * Handles a single tun of the game.
     */
    void OneTurn();

    /**
     * Deletes all items on the screen.
     */
    void RefreshScreen() const;

    /**
     * Creates players for the game.
     */
    void AddPlayers();

    /**
     * Saves the game into a save file.
     * @param name of the save file.
     */
    void SaveGame(const string& filename) const;

    /**
     * Loads the game from a save file.
     * @param name of the load file.
     */
    void LoadGame(const string& filename) const;

    /**
     * Loads the map from a save file.
     * @param name of the load file.
     * @return pair consisting of name of the file with the map and difficulty
     */
    pair<string,int> LoadMap(const string& filename) const;

private:
    string savedir;
    vector<CPlayer*> players;
    vector<CAction*> actions;
    CMap map;
    int establishmentcount;
    int difficulty;
};

#endif //SEMESTRAL_CGAME_H

