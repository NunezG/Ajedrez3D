#ifndef __ModuloIA_
#define __ModuloIA_



class ModuloIA
{
public:
    //Singleton
    static ModuloIA* getCEGUISingletonPtr();
     ~ModuloIA(void);


private:



    bool construyeArbol();
        bool generaMovimientos();

    //Singleton;
    ModuloIA(void);
    void operator=(const ModuloIA& frameListener ) ;
    ModuloIA(const ModuloIA& ModuloIA);

};


#endif
