#ifndef BRANCH_H
#define BRANCH_H
#include <string>
#include "nuclide.h"
#include "transition.h"
using namespace std;

class Branch
{
public:
    Branch();


private:
    int id;
    Transition transition;
    Nuclide parent;
    Nuclide nuclide;
    Nuclide daugther;
};

#endif // BRANCH_H
