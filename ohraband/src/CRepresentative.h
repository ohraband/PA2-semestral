//
// Created by Andy on 6. 6. 2021.
//

#ifndef SEMESTRAL_CREPRESENTATIVE_H
#define SEMESTRAL_CREPRESENTATIVE_H

#include "CViewableItem.h"
#include "CRoute.h"

/**
 * class implements a single employee - representative that can be displayed on the screen
 */
class CRepresentative : public CViewableItem{
public:
    /**
     * Creates a new representative
     * @param employer - establishment representative belongs to
     * @param route - route the representative is following
     */
    CRepresentative(CEstablishment* employer, CRoute* route) : CViewableItem(employer->GetPosition(),
                                                                             employer->Playername()), employer(employer), route(route), occupied(false){

    };

    /**
     * Default destructor
     */
    ~CRepresentative() override = default;

    /**
     * Moves the representative one step forward on the screen.
     */
    void MoveForward();

    /**
     * Checks if representative can be walked on.
     * @return false
     */
    bool Walkable() const override;

    /**
     * Display representative on the screen
     * @param src - screen
     */
    void Show(CScreen *src) const override;

    /**
     * Display representative going in the opposite direction on the screen.
     * @param src - screen
     */
    void ShowBad(CScreen *src) const;

    /**
     * Change status of the representative.
     */
    void ChangeOccupied();

    /**
     * Check status of the representative.
     * @return true if occupied, false if not.
     */
    bool Occupied() const;

    /**
     * Change status of two representatives meeting each other.
     * @param second - second representative
     */
    void Occupy(CRepresentative* second);

    /**
     * @return - establishment representative belongs to
     */
    CEstablishment* GetEmployer() const;


private:
    CEstablishment* employer;
    CRoute* route;
    bool occupied;
};


#endif //SEMESTRAL_CREPRESENTATIVE_H