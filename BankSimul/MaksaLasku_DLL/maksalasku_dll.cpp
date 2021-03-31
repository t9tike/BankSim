#include "maksalasku_dll.h"
#include "maksalaskumoottori.h"


MaksaLasku_DLL::MaksaLasku_DLL()
{

}

void MaksaLasku_DLL::RajapintafunktioML()           // rajapintafunktio
{
    YhdistajaML = new MaksaLasku_DLL;
    YhdistajaML->show();
    YhdistajaML->exec();
    delete YhdistajaML;

}
