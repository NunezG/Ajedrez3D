#ifndef __FichaAlfil_
#define __FichaAlfil_

#include "Ficha.h"


class FichaAlfil : public Ficha
{
public:

    ~FichaAlfil(void);
    FichaAlfil(std::string nombre);
protected:

    bool autorizaFicha(int diferencia[2]);


private:  


};


#endif
