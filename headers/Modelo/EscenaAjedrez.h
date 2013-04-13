#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_




#include "../Modelo/Modelo.h"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>


#include <Ogre.h>
#include "InputMan.h"
#include "Tablero.h"





//#define TABLERO 1 << 3
//#define CASILLA 1 << 0  // Mascara para el escenario


class  EscenaAjedrez
{
public:


    int peonesPromocionados;

    int* actualizaTablero(posicion casillaOrigen,posicion casillaDestino);

    int* mueveIA(int origen, int destino);

    ~EscenaAjedrez(void);

    //Singleton
    static EscenaAjedrez* getSingletonPtr();

    void createScene();

    FichaReina* promocionaPeon(Ficha* nodoFicha);

    // void createCamera(void);

    Ogre::Camera* createCamera(void);
    void createViewports(Ogre::RenderWindow* window);
    Ogre::RaySceneQueryResult& executeRay(int posx, int posy, char mascara);
    Ogre::RaySceneQuery* createRayQuery(void);


    void iluminaCasillaSobrevolada();
    void iluminaCasilla(Casilla* casilla);
    void apagaCasilla(Casilla* casilla);

    Casilla* casillaOcupada(Casilla* nodoCasilla);

    void setSceneManager(Ogre::SceneManager* sceneMgr);

    void mueveCamaraIzquierda();
    void mueveCamaraDerecha();

    bool vaIzquierda();
    bool vaDerecha();

    void noMueveCamara();

    bool esModoCamara();

    void empezarModoCamara();
    void acabarModoCamara();

    void DistanciaCamara(int distanciaRelativa);

    void rotacionCamara(Ogre::Degree angulo);
    void cambiaTurno();

    bool FichaComestible();

    Ogre::String columnas;

    //std::vector<Tablero*> HistorialMovimientos;


   Tablero* tablero;

    int* traduceTablero();

    int* mueveYTraduceTablero();

    bool seleccionaFichaEnPosicion(int posX, int posY);

private:   

     Modelo* modelo;

    //Ogre::Entity *entTablero;


    void creaIluminacion();


   // bool turnoNegras;

    InputMan::SdkCameraMan* mInputMan;

    bool mGoingLeft;
    //  bool mCambiaTurno;
    bool mGoingRight;

    bool mOrbiting;

    Ogre::Ray setRayQuery(int posx, int posy, Ogre::uint32 mask, Ogre::RenderWindow* win);

    //Singleton;
    EscenaAjedrez(void);
    void operator=(const EscenaAjedrez& escena ) ;
    EscenaAjedrez(const EscenaAjedrez& escena);

    Ogre::RenderWindow* mWindow;

    Ogre::SceneManager* mSceneMgr;
    Ogre::RaySceneQuery *mRaySceneQuery;

    Ogre::Camera* mCamera;

    short traduceFicha(tipoFicha tipo);



};

#endif
