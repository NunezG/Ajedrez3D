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

    virtual Ogre::SceneNode* getNodoOgre();
    bool eliminaHijo(int hijo);
    bool creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombre, Ogre::uint32 mask);
    bool agregaHijo(ObjetoOgre* objetoHijo);
    bool sinHijos();
    void cambiaMaterial(std::string material);
    void rota(int grados);
    void trasladar(int x, int z);
    ObjetoOgre* getHijo(int numero);
    ObjetoOgre* getHijo(std::string posicion);

    std::string getNombre();

protected:


    ObjetoOgre(std::string nombre);



private:




    virtual bool setEntidad(Ogre::Entity* ent);
    virtual Ogre::Entity* getEntidad();
    virtual bool setNodoOgre(Ogre::SceneNode* nodo);

    bool eliminaHijo(ObjetoOgre* hijo);


    int numeroHijos();



    Ogre::uint32 tipoObjeto;
    std::vector<ObjetoOgre*> vectorHijos;
    std::string nombreObjeto;
    Ogre::Entity* entidad;
    Ogre::SceneNode* nodoEscena;
    Ogre::SceneManager* mSceneMgr;

};

#endif
