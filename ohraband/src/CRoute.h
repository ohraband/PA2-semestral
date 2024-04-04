//
// Created by Andy on 5. 6. 2021.
//

#ifndef SEMESTRAL_CROUTE_H
#define SEMESTRAL_CROUTE_H



#include "CMap.h"
#include "CEstablishment.h"

#include <vector>
#include <queue>
#include <map>
#include <algorithm>

//forward declaratoins
class CMap;
class CRepresentative;

/**
 * class implements a route from one establishment to another that representatives follow
 */
class CRoute{
public:

    /**
     * create a new route
     * @param store1 - first establishment
     * @param store2 - second establishment
     * @param map - map of the level
     */
    CRoute(CEstablishment* store1, CEstablishment *store2, CMap* map): store1(store1), store2(store2), map(map), store1attack(true), store2attack(false)
    {
        route = BFS(store1->GetPosition(),store2->GetPosition());
    };
    /**
     * default destructor
     */
    ~CRoute() = default;

    /**
     * Pathfinding algorithm using Breadth first search.
     * @param pos1 - starting position
     * @param pos2 - ending position
     * @return vector of positions connecting start to end - route
     */
    vector<Position> BFS( Position pos1, Position pos2)const;

    /**
     * @param cpos - current position
     * @param store - starting establishment
     * @return next position on the route
     */
    Position GetNextPosition(Position cpos, CEstablishment* store)const;

    /**
     * Display route on screen.
     * @param src - screen
     */
    void ShowRoute(CScreen *src) const;
    /**
     * Display all representatives on the route.
     * @param src
     */
    void ShowReps(CScreen *src);

    /**
     * Check if the position corresponds to end of the route
     * (ending establishment).
     * @param cpos - current position
     * @param store - starting establishment
     * @return true if it is the end, false otherwise
     */
    bool Arrived(Position cpos, CEstablishment* store)const;

    /**
     * Include opposite direction ("end to start").
     */
    void IncludeSecond();

    /**
     * @param store - starting establishment
     * @return ending establishment
     */
    CEstablishment* GetEnemy(CEstablishment* store)const;

    /**
     * Removes one of the directions on the route.
     * @param store
     */
    void RemoveDirection(CEstablishment* store);

    /**
     * @return true if at least one direction is used, false otherwise
     */
    bool CheckUsed() const;

    /**
     * Add a new representative to the route.
     * @param rep - representative
     * @param employer - establishment representative belongs to
     */
    void AssignRep(CRepresentative* rep, CEstablishment* employer);
    /**
     * Remove a representative from the route.
     * @param rep - representative
     * @param employer - establishment representative belongs to
     */
    void DismissRep(CRepresentative* rep, CEstablishment* employer);

    /**
     * Check if there is an enemy representative going on the same route in the opposite direction.
     * @param pos - position of the representative
     * @param employer - establishment representative belongs to
     * @return enemy representative
     */
    CRepresentative* SpotEnemy(Position pos, CEstablishment* employer) const;

    /**
     * Checks if vector of positions going from store1 to store2 is empty.
     * (if such a route exists)
     * @return true if empty, false otherwise.
     */
    bool IsEmpty() const;



private:
    //starting point
    CEstablishment* store1;
    //ending point
    CEstablishment* store2;
    vector<CRepresentative*> store1representatives;
    vector<CRepresentative*> store2representatives;
    CMap* map;
    bool store1attack;
    bool store2attack;
    //the route
    vector<Position> route;
};





#endif //SEMESTRAL_CROUTE_H
