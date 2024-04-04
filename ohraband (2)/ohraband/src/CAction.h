//
// Created by Andy on 6. 6. 2021.
//

#ifndef SEMESTRAL_CACTION_H
#define SEMESTRAL_CACTION_H

#include "CRoute.h"
#include "CRepresentative.h"

#include <vector>


/**
 * CAction class is used as a set of commands for handling
 * a single turn of one player in the game.
 */
class CAction{
public:

    /**
     * Creates a new CAction object
     * @param store1 - starting establishment
     * @param store2 - ending establishment
     * @param map - map of the level
     * @param readyreps - number of representatives assigned to one action (5 as default)
     */
    CAction(CEstablishment* store1, CEstablishment* store2, CMap* map, int readyreps = 5 ) : store1(store1),
    store2(store2), readyreps(readyreps), map(map){
        Navigation();
    }

    /**
     * Deletes the CAction object, it's associated representatives and
     * the route in case it is not used anymore.
     */
    ~CAction(){
        for(auto rep : activereps){
            delete rep;
        }

        route->RemoveDirection(store1);
        if(!route->CheckUsed()){
            map->ShowSingleRoute(route);
            map->RemoveRoute(route);
            delete route;
        }
    }

    /**
     * Assign or create a route from store1 to store2
    */
    void Navigation();

    /**
     * Make a step forward in the Action
     * Move all representatives by one step and spawn new ones if needed.
     * Remove all representatives who reached their destination.
    */
    void Do();

    /**
     * Create a new representative.
    */
    void Spawn();

    /**
     * Check if action ended.
    */
    bool Finished() const;

    /**
     * @return route object assigned to this action
    */
    CRoute *GetRoute() const;

private:
    /**
     * Starting Establishment
     */
    CEstablishment* store1;
    /**
     * Ending Establishment
     */
    CEstablishment* store2;
    CRoute* route;
    int readyreps;
    CMap* map;
    vector<CRepresentative*> activereps;
};


















#endif //SEMESTRAL_CACTION_H
