#ifndef __FichaCaballo_
#define __FichaCaballo_

#include "Ficha.h"


class FichaCaballo : public Ficha
{
public:

    ~FichaCaballo(void);
    FichaCaballo(std::string nombre);

private:  
    bool autorizaFicha(int diferencia[2]);

};

#endif
