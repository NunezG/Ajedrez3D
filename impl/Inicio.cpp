#include "../headers/Inicio.h"



//-------------------------------------------------------------------------------------
Inicio::Inicio(void)


{


}
//-------------------------------------------------------------------------------------
Inicio::~Inicio(void)
{
    std::cout << "destructor inicio"<< std::endl;


}






////////////////////////////////////////////////////////////////////////////////////////7


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
{
    try {
         std::cout << "EMPIEZA"<<std::endl;
      //  CreacionJuego cj;
        //  std::cout << "GO" << std::endl;
     //   cj.go();

        ControlJuego& control = ControlJuego::getControlSingleton();
        control.go();

        std::cout << "acaba el inicio"<< std::endl;

       // VistaAjedrez tut;

       //mI.createGUI();

    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occured: " <<
                     e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
