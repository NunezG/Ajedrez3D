#ifndef __ObjetoOgre_
#define __ObjetoOgre_
#include <Ogre.h>

#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3
#define CASILLA 1 << 0  // Mascara para el escenario




class ObjetoOgre
{
public:
    ~ObjetoOgre(void);

    ObjetoOgre(Ogre::SceneManager* sceneMgr, Ogre::String nombre);


    virtual bool setEntidad(Ogre::Entity* entidad);
    virtual Ogre::Entity* getEntidad();

    virtual bool setNodoOgre(Ogre::SceneNode* nodo);
    virtual Ogre::SceneNode* getNodoOgre();


    virtual bool creaModelo3D(Ogre::String nombre);

    virtual bool NuevoObjetoDeOgre();


private:

    Ogre::SceneManager* mSceneMgr;


    Ogre::Entity* entidad;
    Ogre::SceneNode* nodoEscena;

    Ogre::uint32 tipoObjeto;
    Ogre::String nombreEntidad;
    Ogre::String nombreNodo;


};

#endif
