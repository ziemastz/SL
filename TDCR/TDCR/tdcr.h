#ifndef TDCR_H
#define TDCR_H
#include <string>
//globa
enum unit {
    Year,
    Day,
    Hour,
    Minute,
    Second,
};


//nuclide;

class NuclideData
{
public:
    std::string name;       // H-3
    int A;                  // mass number
    int Z;                  // proton number
    bool isStable;
    double halfLifeValue;   // half-life value in unit
    double halfLifeUncer;   // half-life uncer in unit
    unit halfLifeUnit;      // half-life unit
    double R;               // nuclear radius in natural units
    double beta2;           // quadrupole deformation
    double spinParity;      // double of nuclear spin
};

enum Transition {
    Alfa,
    BetaMinus,
    BetaPLus,
    EC,
    GammaIC
};

class Branch
{
public:
    NuclideData parent;
    double intensive;
    Transition type;
    NuclideData daughter;
};
class Decay
{
public:
    NuclideData nuclide;
    vector<Branch> branches
};

class TDCR
{
public:
    TDCR();
};

#endif // TDCR_H
