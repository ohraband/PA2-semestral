//
// Created by Andy on 9. 5. 2021.
//

class CAction{
public:

    CAction(Outpost MyOutpost, Outpost TargetOutpost, CMap CurrentMap) : outpost1(MyOutpost), outpost2(TargetOutpost),
    NumberOfForces(NumberOfForces), CurrentMap(CurrentMap)
    {};

    vector<pair<int,int>> GeneratePath(Outpost MyOutpost, Outpost TargetOutpost, CMap CurrentMap){
        //some BFS
    };



    bool DoAction(Outpost MyOutpost, Outpost TargetOutpost, CMap CurrentMap)
    {
        vector<pair<int,int>> path = GeneratePath(Outpost MyOutpost, Outpost TargetOutpost, CMap CurrentMap);

        vector<CRepresentative> Forces;

        while(!Forces.empty()){
            for(auto const Representative& : Forces)
            {
                Representative.Move(const vector<pair<int,int>> & path);
            }
        }
    }


private:
    CMap CurrentMap;
    Outpost outpost1;
    Outpost outpost2;
    vector<pair<int,int>> path;
};
