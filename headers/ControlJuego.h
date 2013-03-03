
#ifndef __ControlJuego_
#define __ControlJuego_


#include <CEGUI/CEGUISystem.h>
#include "BaseJuego.h"




class  ControlJuego : public BaseJuego
{
public:

    //Destructor
    ~ControlJuego(void);

    //Singleton
    static ControlJuego& getControlSingleton();


    void inicio(void);
    bool setupMenu(void);


private:


    void cambiaPantalla();



//void createGUI(void);
  //  void createMainMenu(void);

   // CEGUI::System* mGUISystem;
    CEGUI::Window *sheet;



    //Singleton
   // static ControlJuego* miControlJuego_;
    void operator=(const ControlJuego& controlJuego ) ;
    ControlJuego(const ControlJuego& control);
    ControlJuego(void);





    //BUCLE PRINCIPAL
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );



};

#endif // #ifndef __TutorialApplication_h_
