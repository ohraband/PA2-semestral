//
// Created by Andy on 5. 6. 2021.
//

#include "CEstablishment.h"
#include "CRepresentative.h"

bool CEstablishment::Walkable() const {
    return false;
}

void CEstablishment::Show(CScreen *src) const{
    //sets appropriate color for the name
    int colorpair = AssignColorPair();
    //show all the associated blocks
    src->QuickShow(pos.y(), pos.x(), Playername(),colorpair);
    src->QuickShow(pos.y(),pos.x()+1,'n',colorpair);
    src->QuickShow(pos.y(),pos.x()+2,'n',colorpair);
    attron(COLOR_PAIR(colorpair));
    mvprintw(pos.y(),pos.x()+1,"%d",AvailableRepresentatives, colorpair);
    attroff(COLOR_PAIR(colorpair));
    src->QuickShow(pos.y()+1,pos.x(),'n',colorpair);
    src->QuickShow(pos.y()+1,pos.x()+1,'n',colorpair);
    src->QuickShow(pos.y()+1,pos.x()+2,'n',colorpair);
}



void CEstablishment::Highlight(CScreen *src, int num) {
    int colorpair = 3;
    if(num >= 0 && num <= 9){
        num +=48;
        colorpair = 4;
    }
    src->QuickShow(pos.y()+1,pos.x(),(signed char)num,colorpair);
}



void CEstablishment::AddRoute(CRoute *road, CEstablishment *tar){
    route = road;
    target = tar;
}

void CEstablishment::RemoveRoute(){
    route = nullptr;
    target = nullptr;
}

CRoute * CEstablishment::CheckRoute(CEstablishment *tar) const{
    if(target == tar){
        return route;
    }
    else{
        return nullptr;
    }
}

void CEstablishment::LoadSet(char name, int reps, int maxreps){
    playername = name;
    AvailableRepresentatives = reps;
    MaxRepresentatives = maxreps;
}


int CEstablishment::GetMaxRepresentatives() const {
    return MaxRepresentatives;
}


int CEstablishment::GetAvailableRepresentatives() const {
    return AvailableRepresentatives;
}



bool CEstablishment::Hire(){
    if(AvailableRepresentatives < MaxRepresentatives){
        AvailableRepresentatives++;
        return true;
    }
    return false;
}


bool CEstablishment::Fire(CRepresentative* rep){ //Representative rep
    if(AvailableRepresentatives > 0){
        AvailableRepresentatives--;
        return true;
    }
    else if (AvailableRepresentatives == 0){
        playername = rep->Playername();
        AvailableRepresentatives = 3;
        return true;
    }
    return false;
}

void CEstablishment::ArrivingRep(CRepresentative* rep ){
    if(rep->Playername() != this->Playername()){
        Fire(rep);
    }
    else{
        Hire();
    }
}

CRepresentative *CEstablishment::SendRep(CRoute * road) {
    if(AvailableRepresentatives > 0){
        AvailableRepresentatives--;
        auto* rep = new CRepresentative(this, road);
        return rep;
    }

    return nullptr;
}
