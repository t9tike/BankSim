#include "dlltilitapahtumat.h"


DLLTiliTapahtumat::DLLTiliTapahtumat()
{
}

DLLTiliTapahtumat::~DLLTiliTapahtumat()
{
    delete olioTiliTapahtumatMoottoriDialog;
}

void DLLTiliTapahtumat::rajapintafunktioDLLTiliTapahtumat()     //funktiossa asetetaan moottoridialog näkyväksi
{
    olioTiliTapahtumatMoottoriDialog = new TiliTapahtumatMoottoriDialog;
    olioTiliTapahtumatMoottoriDialog->show();
    olioTiliTapahtumatMoottoriDialog->exec();
    delete olioTiliTapahtumatMoottoriDialog;
}


