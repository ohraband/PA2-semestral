//
// Created by Andy on 6. 6. 2021.
//

#include "CRepresentative.h"

void CRepresentative::MoveForward() {
    Position newpos = route->GetNextPosition(pos, employer);

        //check if representative reached the destination
        if(route->Arrived(newpos, employer)){
            this->ChangeOccupied();
            route->GetEnemy( employer )->ArrivingRep(this);
        }

        //check if representative encountered another representative
        else if(route->SpotEnemy(newpos, employer) != nullptr){
            Occupy(route->SpotEnemy(newpos, employer));
        }

        //set new position
        else{
            pos = newpos;
        }
}


bool CRepresentative::Walkable() const  {
    return false;
}

void CRepresentative::Show(CScreen *src) const {
    int colorpair = AssignColorPair();
    src->QuickShow(pos.y(),pos.x(),'Y',colorpair);
}

void CRepresentative::ShowBad(CScreen *src) const{
    int colorpair = AssignColorPair();
    src->QuickShow(pos.y(),pos.x(),'I',colorpair);
}


void CRepresentative::ChangeOccupied(){
    occupied = true;
}

bool CRepresentative::Occupied() const{
    return occupied;
}

void CRepresentative::Occupy(CRepresentative* second){
    this->ChangeOccupied();
    second->ChangeOccupied();
}

CEstablishment* CRepresentative::GetEmployer() const{
    return employer;
}

