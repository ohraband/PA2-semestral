//
// Created by Andy on 6. 6. 2021.
//

#include "CAction.h"

void CAction::Navigation(){

    //if a route in the opposite direction doesn't exist, create a new one
    if(store2->CheckRoute(store1) == nullptr){
        route = new CRoute(store1, store2, map);
        map->AddRoute(route);
        store1->AddRoute(route, store2);
    }

    //if a route in the opposite direction exists, assign it
    else{
        store2->CheckRoute(store1)->IncludeSecond();
        route = store2->CheckRoute(store1);
        store1->AddRoute(route, store2);
    }
}

void CAction::Spawn(){
    //try to create a new representative
    auto * rep = store1->SendRep(route);
    if(rep != nullptr){
        route->AssignRep(rep, store1);
        activereps.push_back(rep);
    }
    //delete it if creating did not work
    else{
        delete rep;
    }
}

void CAction::Do(){
    //move each representative
    for (auto rep : activereps){
        rep->MoveForward();
    }
    //spawn a new representative
    if(readyreps > 0){
        if(store1->GetAvailableRepresentatives() > 0){
            Spawn();
        }
        readyreps--;
    }
    //remove all occupied representatives
    for (auto it = activereps.begin(); it != activereps.end(); ) {
        if((*it)->Occupied()){
            route->DismissRep(*it, store1);
            delete *it;
            it = activereps.erase(it);
        }
        else {
            ++it;
        }
    }
}

CRoute *CAction::GetRoute() const {
    return route;
}

bool CAction::Finished() const {
    //check if all representatives have been spawned and arrived
    if(!readyreps && activereps.empty() ){
        store1->RemoveRoute();
        return true;
    }
    else{
        return false;
    }
}