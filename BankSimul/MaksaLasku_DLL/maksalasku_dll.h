#ifndef MAKSALASKU_DLL_H
#define MAKSALASKU_DLL_H
#include "maksalaskumoottori.h"

#include "maksalasku_dll_global.h"

class MAKSALASKU_DLLSHARED_EXPORT MaksaLasku_DLL: public MaksaLaskuMOOTTORI
{

public:
    MaksaLasku_DLL();
    void MAKSALASKU_DLLSHARED_EXPORT RajapintafunktioML();

private:
    MaksaLaskuMOOTTORI * YhdistajaML;


};

#endif // MAKSALASKU_DLL_H
