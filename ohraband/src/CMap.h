//
// Created by Andy on 4. 6. 2021.
//

#ifndef SEMESTRAL_CMAP_H
#define SEMESTRAL_CMAP_H



#include "CViewableItem.h"
#include "CNothing.h"
#include "CObstacle.h"
#include "CEstablishment.h"
#include "CRoute.h"
#include "CScreen.h"


#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <memory>

using namespace std;
/**
 * Class CMap creates a list of all objects to be later
 * wonderully displayed on the screen as the map.
 */
class CMap{
public:
    /**
     * Creates a new instance of the object CMap
     * @param filename - name of the with the map
     */
    explicit CMap( const string & filename) : filename(filename) ,Coordinates(LoadMap(filename)){
        //crates a new screen
        src = new CScreen();
        //set width and height
        height = Coordinates.size();
        width = Coordinates[0].size();
        //create 2D vector of ViewableItems to be displayed
        PosItems = MakePosItems(Coordinates, height, width);
    }

    /**
     * Destructor for CMap.
     * Deletes every Viewable object and the screen.
     */
    ~CMap() {

        for(auto & i : EstablishmentList){
            delete i;
        }
        for(auto & i : NothingList){
            delete i;
        }
        for(auto & i : ObstacleList){
            delete i;
        }

        src->End();
        delete src;
    };

    /**
     * Creates a 2D vector of symbols from the map file.
     * @param filename - name of the map file
     * @return 2D vector "vector<vector<char>>" of symbols the map consists of
     */
    vector<vector<char>> LoadMap(const string & filename) const;

    /**
     * Show all Viewable objects on the map.
     */
    void Show() const;

    /**
     * Highlights all establishments numbers on the map.
     * Also highlights the source establishment with 'S'.
     * @param source - establishment to be highlighted as the source establishment.
     */
    void HighlightAllEst(CEstablishment* source) const;

    /**
     * Shows all representatives on the screen.
     */
    void ShowReps() const;

    /**
     * Shows all routes on the screen.
     */
    void ShowRoutes() const;

    /**
     * Shows a single route on the screen.
     */
    void ShowSingleRoute(CRoute* road) const;

    /**
     * Shows all establishments on the screen.
     */
    void ShowEstablishments() const;

    /**
     * Returns all establishments owned by the player.
     * @param name - name of the player
     * @return list of all establishments owned by the player
     */
    vector<CEstablishment*> PlayerEstablishments(char name) const;

    /**
     * @param name - name of the player
     * @return number of establishments owned by the player
     */
    int PlayerEstablishmentsNum(char name) const;

    /**
     * Increases number of available representatives in all establishments.
     */
    void HireRepresentatives() const;

    /**
     * @param pos - position of the item
     * @return object CViewableItem* at given position
     */
    CViewableItem* GetItem(Position pos) const;

    /**
     * Check for possible moves from a given position on the map.
     * @param pos - current position
     * @param store1 - source establishment
     * @param store2 - target establishment
     * @return vector of possible positions to move to
     */
    vector<Position> PossibleMoves(Position pos, CEstablishment *store1, CEstablishment *store2) const;

    /**
     * Checks if the given position can be moved to.
     * @param pos - current position
     * @param store1 - source establishment
     * @param store2 - target establishment
     * @return true if the position can be moved to, false otherwise.
     */
    bool IsWalkable(Position pos, CEstablishment *store1, CEstablishment *store2) const;

    /**
     * Add a route to the list of routes.
     * @param road - route to be added
     */
    void AddRoute(CRoute * road);
    /**
     * Remove a route from the list of routes.
     * @param road - route to be removed
     */
    void RemoveRoute(CRoute * road);

    /**
     * Checks if the player is on the map.
     * @param playername - name of the player to be checked
     * @return true if the player is present, false otherwise.
     */
    bool CheckPlayer(char playername);

    /**
     * @return width of the map
     */
    int GetWidth() const;

    /**
     * @return map filename
     */
    const string &GetFilename() const;

    /**
     * @return all establishments on the map
     */
    const vector<CEstablishment *> &GetEstablishmentList() const;

    /**
     * @return display screen
     */
    const CScreen* GetSrc() const;

    /**
     * Create a 2D vector of all CViewableItem* objects on the map.
     * @param Coordinates - 2D vector of all symbols on the map
     * @param height - map height
     * @param width - map width
     * @return 2D vector of all CViewableItem* objects on the map
     */
    vector<vector<CViewableItem*>> MakePosItems(vector<vector<char>> Coordinates , int height, int width);


private:
    string filename;
    CScreen *src;
    vector<CEstablishment*> EstablishmentList;
    vector<CNothing*> NothingList;
    vector<CObstacle*> ObstacleList;
    int height = 0;
    int width = 0;
    vector<vector<char>> Coordinates;
    vector<vector<CViewableItem*>> PosItems;
    vector<CRoute*> routes;
    set<char> players;
};

#endif //SEMESTRAL_CMAP_H