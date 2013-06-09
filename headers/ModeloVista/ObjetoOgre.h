#ifndef __ObjetoOgre_
#define __ObjetoOgre_

#include <OgreSceneManager.h>
#include <OgreEntity.h>

#define CASILLA 1 << 0  // Mascara para el escenario
#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3


class ObjetoOgre
{
public:
    ~ObjetoOgre(void);
    ObjetoOgre(std::string nombre);

    virtual bool setEntidad(Ogre::Entity* entidad);
    virtual Ogre::Entity* getEntidad();
    virtual bool setNodoOgre(Ogre::SceneNode* nodo);
    virtual Ogre::SceneNode* getNodoOgre();
    ObjetoOgre* getHijo(std::string posicion);
    ObjetoOgre* getHijo(int numero);
    std::string getNombre();
    bool eliminaHijo(ObjetoOgre* hijo);
    bool eliminaHijo(int hijo);

    bool creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombre, Ogre::uint32 mask);
    bool agregaHijo(ObjetoOgre* objetoHijo);
    int numeroHijos();
    bool sinHijos();
    void cambiaMaterial(std::string material);
    void rota(int grados);
    void trasladar(int x, int z);

protected:

    Ogre::uint32 tipoObjeto;

private:

    std::vector<ObjetoOgre*> vectorHijos;
    std::string nombreObjeto;
    Ogre::Entity* entidad;
    Ogre::SceneNode* nodoEscena;
    Ogre::SceneManager* mSceneMgr;
};

#endif
