#ifndef __ObjetoOgre_
#define __ObjetoOgre_
#include <Ogre.h>

#define FICHA 1 << 4
#define TABLERO 1 << 3
#define CASILLA 1 << 0  // Mascara para el escenario
#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2


class ObjetoOgre
{
public:
    ~ObjetoOgre(void);

    ObjetoOgre(std::string nombre);

    virtual bool setEntidad(Ogre::Entity* entidad);
    virtual Ogre::Entity* getEntidad();

    virtual bool setNodoOgre(Ogre::SceneNode* nodo);
    virtual Ogre::SceneNode* getNodoOgre();

    bool creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombre, Ogre::uint32 mask);

    bool agregaHijo(ObjetoOgre* objetoHijo);

    ObjetoOgre* getHijo(std::string posicion);

    ObjetoOgre* getHijo(int numero);


    void cambiaMaterial(std::string material);

    void rota(int grados);

    void trasladar(int x, int z);

    Ogre::Entity* entidad;
    Ogre::SceneNode* nodoEscena;

    Ogre::SceneManager* mSceneMgr;

        // bool NuevoObjetoDeOgre(void);

protected:



    std::vector<ObjetoOgre*> vectorHijos;

  //  std::vector<Ogre::SceneNode*> vectorHijos;


   // std::vector<Ogre::SceneNode> nodosHijo;

    Ogre::uint32 tipoObjeto;
    //Ogre::String nombreEntidad;
   // Ogre::String nombreNodo;

    std::string nombreObjeto;


private:
};

#endif
