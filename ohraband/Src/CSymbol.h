//
// Created by Andy on 9. 5. 2021.
//

#pragma once

using namespace std;

class CSymbol{
public:
    CSymbol() = default;

    virtual void Show() = 0;
    virtual bool Walkable() {
        return true;
    }
    virtual string Type() {
        return "Nothing";
    }

private:

};
