//
// Created by Andy on 5. 6. 2021.
//

#include "CRoute.h"
#include "CRepresentative.h"


Position CRoute::GetNextPosition(Position cpos, CEstablishment* store) const{
    if(store == store1){
        for(unsigned int i = 0 ; i < route.size() ; i++){
            if( route[i] == cpos ){
                cpos = route[i+1];
                return cpos;
            }
        }
    }

    if(store == store2){
        for(unsigned int i = 0 ; i < route.size() ; i++){
            if( route[i] == cpos ){
                cpos = route[i-1];
                return cpos;
            }
        }
    }

    return cpos;
}


vector<Position> CRoute::BFS(Position pos1, Position pos2) const{
    queue<Position> queue;
    //vector containing a position and its predecessor
    vector<pair<Position, Position>> previous;
    vector<Position> visited;

    queue.push(pos1);
    visited.push_back(pos1);

    while(!queue.empty()) {
        //check if we reached the end
        if(queue.front() == pos2){
            vector<Position> road;
            road.push_back(pos2);
            Position curr = pos2;
            //get the route by going back through predecessors
            while(curr != pos1){
                auto it = std::find_if( previous.begin(), previous.end(),
                                        [&curr]( pair<Position, Position> element){ return element.first == curr;} );
                road.push_back(it->second);
                curr = it->second;
            }
            reverse(road.begin(),road.end());
            return road;
        }

        visited.push_back(queue.front());

        //check all positions that are reachable from the current one
        for( const auto& place : map->PossibleMoves(queue.front(),store1,store2)){

            if(find(visited.begin(), visited.end(), place) == visited.end()){
                queue.push(place);
                visited.push_back(place);
                previous.emplace_back(place,queue.front());
            }
        }

        queue.pop();
    }

    vector<Position> empty;
    return empty;
}

bool CRoute::Arrived(Position cpos, CEstablishment* store) const{
    if(store == store1){
        return store2 == map->GetItem(cpos);
    }

    else if(store == store2){
        return store1 == map->GetItem(cpos);
    }
    return false;
}

void CRoute::ShowRoute(CScreen *src) const{

    for(const auto& pos : route){
        if(map->GetItem(pos) != store1 && map->GetItem(pos) != store2 ) {
            move(pos.y(), pos.x());
            printw("%c", '.');
            refresh();
        }
    }
    //ShowReps(src);
}

void CRoute::ShowReps(CScreen *src) {

    for(auto x : store1representatives){
        if(map->GetItem(x->GetPosition()) != store1 && map->GetItem(x->GetPosition()) != store2 ) {
            x->Show(src);
        }
    }

    for(auto x : store2representatives){
        if(map->GetItem(x->GetPosition()) != store1 && map->GetItem(x->GetPosition()) != store2 ) {
            x->ShowBad(src);
        }
    }

}

void CRoute::IncludeSecond(){
    store2attack = true;
}

CEstablishment* CRoute::GetEnemy(CEstablishment* store) const{
    if(store == store1){
        return store2;
    }

    else if(store == store2){
        return store1;
    }
    return store1;
}



void CRoute::RemoveDirection(CEstablishment* store){
    if(store == store1){
        store1attack = false;
    }

    else if(store == store2){
        store2attack = false;
    }
}

bool CRoute::CheckUsed() const{
    if(store1attack || store2attack){
        return true;
    }
    return false;
}


void CRoute::AssignRep(CRepresentative* rep, CEstablishment* employer){
    if(employer == store1){
        store1representatives.push_back(rep);
    }
    else if(employer == store2){
        store2representatives.push_back(rep);
    }
}

void CRoute::DismissRep(CRepresentative* rep, CEstablishment* employer){
    if(employer == store1){
        for (auto it = store1representatives.begin(); it != store1representatives.end(); ) {
            if((*it)->Occupied()){
                //delete(*it);
                it = store1representatives.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    else if(employer == store2){
        for (auto it = store2representatives.begin(); it != store2representatives.end(); ) {
            if((*it)->Occupied()){
                //delete(*it);
                it = store2representatives.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}


CRepresentative* CRoute::SpotEnemy(Position pos, CEstablishment* employer) const{
    if(employer == store1){
        for( const auto srep : store2representatives ){
            if(srep->GetPosition() == pos && srep->Playername() != employer->Playername()){ //
                return srep;
            }
        }
    }
    else if(employer == store2){
        for( const auto srep : store1representatives ){
            if(srep->GetPosition() == pos && srep->Playername() != employer->Playername()){
                return srep;
            }
        }
    }
    return nullptr;
}


bool CRoute::IsEmpty() const{
    if(route.empty()){
        return true;
    }
    return false;
}