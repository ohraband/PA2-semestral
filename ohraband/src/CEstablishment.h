//
// Created by Andy on 5. 6. 2021.
//

#ifndef SEMESTRAL_CESTABLISHMENT_H
#define SEMESTRAL_CESTABLISHMENT_H


#include "CViewableItem.h"

//forward declarations
class CRepresentative;
class CRoute;

/**
 * Class CEstablishment represents a single establishment on the map.
 * Establishment hires and sends representatives to other establishments.
 * It is also an implementation of abstract class CViewableItem as it can be displayed.
 * (pretty much a base)
 */
class CEstablishment : public CViewableItem {
public:

    /**
     * Creates a single establishment.
     * @param pos - positionon the map
     * @param playername - name of the player controlling the establishment
     * @param MaxRep - maximum number of representatives, number of available representatives is set to be half of this number
     */
    CEstablishment (Position pos, char playername, int MaxRep = 30 ) : CViewableItem(pos, playername),
                                                                       MaxRepresentatives(MaxRep), AvailableRepresentatives(MaxRep/2)
    {
        route = nullptr;
        target = nullptr;
    };

    /**
     * Default CEstablishment destructor.
     */
    ~CEstablishment() override = default;

    /**
     * Determines if representatives can cross through this position.
     * @return false
     */
    bool Walkable() const override;

    /**
     * Displays establishment on the map.
     * @param src - Screen corresponding to the map.
     */
    void Show(CScreen *src) const override;

    /**
     * Highlights the number of the establishment on the map.
     * @param src - Screen corresponding to the map.
     * @param num - number of the establishment
     */
    void Highlight(CScreen *src, int num) ;

    /**
     * Increases the number of available representatives by one.
     * @return true if action was successful, false otherwise.
     */
    bool Hire();

    /**
     * Either decreases the number of available representatives by one or
     * if there are no more representatives available, changes the ownership
     * of the establishment to that of the arriving representative.
     * @param rep - arriving representative
     * @return true if action was successful, false otherwise.
     */
    bool Fire(CRepresentative* rep);

    /**
     * If representatives are available, creates a new object of CRepresentative.
     * @param road - CRoute* a representative will follow.
     * @return CRepresentative* if successful, nullptr otherwise.
     */
    CRepresentative* SendRep(CRoute * road);

    /**
     * Handles an arriving representative.
     * @param rep - CRepresentative*
     */
    void ArrivingRep(CRepresentative* rep );

    /**
     * Adds a route which representatives from this establishment will follow.
     * @param road - CRoute* from this establishment to the target establishment.
     * @param tar - target establishment
     */
    void AddRoute(CRoute *road, CEstablishment *tar);

    /**
     * Removes the CRoute* associated with the establishment.
     */
    void RemoveRoute();

    /**
     * Checks if a route is associated with this establishment.
     * @param tar - target establishment
     * @return CRoute if such road exists, nullptr otherwise.
     */
    CRoute * CheckRoute(CEstablishment *tar) const;

    /**
     * Sets the parameters of the establishment when loading from a savefile.
     * @param name - playername
     * @param reps - number of available representatives.
     * @param maxreps - number of maximum representatives.
     */
    void LoadSet(char name, int reps, int maxreps);

    /**
     * Gets maximum number of representatives in this establishment.
     * @return
     */
    int GetMaxRepresentatives() const;

    /**
     * Gets number of available representatives in this establishment.
     * @return
     */
    int GetAvailableRepresentatives() const;



private:
    int MaxRepresentatives;
    int AvailableRepresentatives;
    CRoute *route;
    CEstablishment *target;
};



#endif //SEMESTRAL_CESTABLISHMENT_H
