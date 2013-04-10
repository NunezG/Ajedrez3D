#ifndef __FichaReina_
#define __FichaReina_

#include "Ficha.h"


class FichaReina : public Ficha
{
public:

    ~FichaReina(void);
    FichaReina(std::string nombre);

    bool mueveFicha();
    bool autorizaFicha(int diferencia[2]);

    FichaReina( const Ficha& fichaOriginal, std::string nombre );


private:  


};

#endif
