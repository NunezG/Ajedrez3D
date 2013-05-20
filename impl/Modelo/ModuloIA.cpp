#include "../../headers/Modelo/ModuloIA.h"

ModuloIA::ModuloIA():
    BlackCheck(false),
    BlackMate(false),
    WhiteCheck(false),
    WhiteMate(false),
    StaleMate(false)
{

}

ModuloIA::~ModuloIA()
{

}

ModuloIA* ModuloIA::getCEGUISingletonPtr()
{
    static ModuloIA miFrameListener;
    static ModuloIA* miFrameListenerPtr = &miFrameListener;
    return miFrameListenerPtr;
}
