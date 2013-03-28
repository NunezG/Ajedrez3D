#include "../headers/ModuloIA.h"

ModuloIA::ModuloIA()
{
    tablero = new TableroPrueba();

}

ModuloIA::~ModuloIA()
{

}

ModuloIA* ModuloIA::getCEGUISingletonPtr()
{
    static ModuloIA miFrameListener;
    static ModuloIA* miFrameListenerPtr = &miFrameListener;
    return miFrameListenerPtr;
}


bool ModuloIA::construyeArbol(int* listaCasillas){

    /*
 *
0 = Vacio
9 = Fuera del tablero
1 = (Blancas) Peon
2 =(Blancas) Caballo
3 =(Blancas) Alfil
4 = (Blancas) Torre
5 = (Blancas) Reina
6 = (Blancas) Rey

-1 = (Negras) Peon
-2 =(Negras) Caballo
-3 =(Negras) Alfil
-4 = (Negras) Torre
-5 = (Negras) Reina
-6 = (Negras) Rey
*/

    std::cout << "CONSTRUYE ARBOL" << std::endl;

    tablero->Score = 2;
    std::cout << "CONSTRUYE ARBOL" << std::endl;

    tablero->casillasInt = new int[144];
    std::cout << "CONSTRUYE ARBOL" << std::endl;





    //AÑADE LOS BORDES
    for (int i = 0; i<12; i++)
    {

        for (int y = 0; y<12; y++)
        {



            if((i > 9)
                    || (y > 9)
                    || (i < 2)
                    || (y < 2))
            {
                tablero->casillasInt[(i*12)+y] = 99;

            }else tablero->casillasInt[(i*12)+y] = listaCasillas[((i-2)*8)+y-2];


            //  std::cout << tablero->casillasInt[((i-2)*8)+y-2] << std::endl;
        }


    }
    std::cout <<  sizeof(tablero->casillasInt) << std::endl;



    for(int i=0; i<12;i++){


        std::cout  <<tablero->casillasInt[i*12]<<"        " << tablero->casillasInt[(i*12)+1]<<"        " << tablero->casillasInt[(i*12)+2]<<"        "<<tablero->casillasInt[(i*12)+3]<<"        "<<tablero->casillasInt[(i*12)+4]<<"        "<<tablero->casillasInt[(i*12)+5]<<"        "<<tablero->casillasInt[(i*12)+6]<<"        "<<tablero->casillasInt[(i*12)+7]<<"        "<<tablero->casillasInt[(i*12)+8]<<"        "<<tablero->casillasInt[(i*12)+9]<<"        "<<tablero->casillasInt[(i*12)+10]<<"        "<<tablero->casillasInt[(i*12)+11]<<std::endl;


    }



    //EMPIEZA A CREAR HIJOS POR CADA MOVIMIENTO

    //REY

    TableroPrueba* nuevo = tablero->tableroHijo;
    nuevo = new TableroPrueba();


    for (int nivel = 0; nivel < 20; nivel++){
        nuevo = nuevo->tableroHermano;
        nuevo = new TableroPrueba();



        for (int nivel = 0; nivel < 3; nivel++){
            nuevo = new TableroPrueba();
            nuevo = nuevo->tableroHijo;


        }

    }


    //REINA




    //ALFIL



    //CABALLO



    //TORRE



    //PEON



    std::cout << "MODULO IA: " << std::endl;




    //  Tablero* nodoPadre = new Tablero();

    //   nivel = 0;

    // for (int i = 0; i<10; i++){

    //      for (int i = 0; i<10; i++){
    //   nodoPadre.nodoNuevo() = new Tablero();
    //  nodoPadre.nodoDer = new Tablero();

    //corta la recursividad

    // nodoPadre.nodoIzq.construyeArbol();
    //  nodoPadre.nodoDer.construyeArbol();

    //    nivel++;
    //     }
    //   }
}

void ModuloIA::insert_helper( TableroPrueba **root, TableroPrueba *newkey, int profundidad ) {

    if (profundidad != 0){
        if ( (*root) == NULL ) {
            *root = newkey;
            TableroPrueba* tableroTemporal = siguienteMovimiento(newkey);
            // if (hijo) insert_helper( &((*root)->tableroHijo), tableroTemporal, --profundidad );
            // else insert_helper( &((*root)->tableroHermano), tableroTemporal, --profundidad);


        }

    }



}


TableroPrueba* ModuloIA::siguienteMovimiento(TableroPrueba *newkey){



}



void ModuloIA::insert( TableroPrueba* newKey  ) {
    //insert_helper( &tablero, newKey,4 );
    alphaBeta(tablero,100, -100, 4);
}


int ModuloIA::alphaBeta(TableroPrueba* table, int alpha, int beta, int depthleft ) {
    int score;
    if( depthleft == 0 ) return evaulaTablero();
    table->vectorMov = generaMovimientos();


    //for (vector<TableroPrueba>::iterator it = vectorMov.begin(); it!=vectorMov.end(); ++it) {
    //  cout << *it << endl;
    //}
    for (int i = 0; i<table->vectorMov.size();i++)
    {
        TableroPrueba* tab = &table->vectorMov[i];

        score = -alphaBeta(tab, -beta, -alpha, depthleft - 1 );
        if( score >= beta )
            return beta;   //  fail hard beta-cutoff
        if( score > alpha )
            alpha = score; // alpha acts like max in MiniMax
    }
    return alpha;
}

bool ModuloIA::evaulaTablero(){


}




std::vector<TableroPrueba> ModuloIA::generaMovimientos(){


    //   vectorTableros.push_back();
    //   vectorTableros.push_back(20);
    //  vectorTableros.push_back(30);

    //Recorre las fichas en juego y genera tableros con todos los movimientos posibles


    return vectorTableros;



}

//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?



bool ModuloIA::mueveTorre(){

    //mueve a todas las casillas posibles

    //mira si esta ocupada

    for(int i = 0; i < 8; i++){
        //diferenciaFila-1;
        //diferenciaCol;

    }

    for(int i = 0; i < 8; i++){
        //diferenciaFila+1;
        //diferenciaCol;

    }

    for(int i = 0; i < 8; i++){
        //diferenciaFila;
        //diferenciaCol+1;

    }


    for(int i = 0; i < 8; i++){
        //diferenciaFila;
        //diferenciaCol-1;

    }


}




bool ModuloIA::mueveAlfil(){


    //mueve a todas las casillas posibles

    for(int i = 0; i < 8; i++){
        // diferenciaFila-1
        //diferenciaCol-1

    }

    for(int i = 0; i < 8; i++){
        //diferenciaFila+1
        //diferenciaCol+1

    }

    for(int i = 0; i < 8; i++){
        //diferenciaFila-1
        //diferenciaCol+1

    }


    for(int i = 0; i < 8; i++){
        //diferenciaFila+1
        //diferenciaCol-1

    }




}


bool ModuloIA::mueveCaballo(){

    //HAY QUE HACERLO A PARTIR DE UNA POSICION

    int dif1 = 10;
    int dif2 = 20;

    /*
    diferencia[0]=-dif2;
    diferencia[1] = dif1;
    diferencia[1] = -dif1;



    diferencia[0] = dif2;
    diferencia[1] = dif1;
    diferencia[1] = -dif1;



    diferencia[0] = dif1;
    diferencia[1] = dif2;
    diferencia[1] = -dif2;



    diferencia[0] == -dif1;
    diferencia[1] == dif2;
    diferencia[1] == -dif2;
*/
    Ogre::list<int> lista;

    //devuelve una lista con todas las nuevas posiciones?

}



