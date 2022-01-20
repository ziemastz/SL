#ifndef TRANSITION_H
#define TRANSITION_H

class BetaData {

};

class ElectronCaptureData
{

};

class AlphaData
{

};

class GammaData
{

};

class Transition
{
public:
    enum PROCESS {
        BeataPlus = 1,
        BetaMinus = -1,
        ElectronCapture = 0,
        GammaIC = 2,
        Alfa = 3
    };
    Transition();
    void addBeta(BetaData beta);
    void addEC(ElectronCaptureData ec);
    void addAlpha(AlphaData alpha);
    void addGamma(GammaData gamma);
private:
    GammaData *_gammaList;

};

class BetaMinus
{

};

#endif // TRANSITION_H
