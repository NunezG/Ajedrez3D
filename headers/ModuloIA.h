#ifndef __ModuloIA_
#define __ModuloIA_
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <iostream>
#include <string>



enum tipoF
{
    Vac,
    Pe,
    Cab,
    Alf,
    Tor,
    Rein,
    Re
};



struct TableroPrueba
{

    // StringClass(char *ptr);
    TableroPrueba();
    ~TableroPrueba();

    //constructor de copia
    TableroPrueba( const TableroPrueba& original );


    std::vector<TableroPrueba*> vectorMov;


    int Score;
    //  Casilla* casillas[64];
    int casillasInt[144];
    int movimiento[2];
    int numeroHijos;

    int alPaso;

    // Ficha* fichasNegras[16];
    // Ficha* fichasBlancas[16];
    // int casillas[8][8];
    //TableroPrueba* tableroHermano;
    //TableroPrueba* tableroHijo;
    bool turnoN;
    std::string fichaMovida;

private:

};





class ModuloIA
{
public:
    //Singleton
    static ModuloIA* getCEGUISingletonPtr();
    ~ModuloIA(void);


    bool construyeArbol(const int listaCasillas[144]);

    void insert( TableroPrueba *newKey);



    bool BorraArbol();
    bool evaluaJaque(const int casillasInt[144], bool turnoNegras);


    TableroPrueba* tableroPadre;

    TableroPrueba* tableroElegido;
    int casillaCambiada;



private:


    bool BlackCheck;
    bool BlackMate;
    bool WhiteCheck;
    bool WhiteMate;
    bool StaleMate;

    int evaulaTablero(const int casillasInt[144], bool turnoN);

   // std::vector<TableroPrueba> vectorTableros;

    int alphaBeta(TableroPrueba* table,int alpha,int beta,const int depthleft );

    TableroPrueba* siguienteMovimiento(TableroPrueba *newkey);


    void insert_helper( TableroPrueba **root, TableroPrueba *newkey, const int profundidad);


    void aplicaMovimiento(TableroPrueba& miTablero,const int casOrigen,const int casDestino);


    bool mueveTorre(TableroPrueba* miTablero, const int casilla);

    bool mueveAlfil(TableroPrueba* miTablero, const int casilla);

    bool mueveCaballo(TableroPrueba* miTablero,const int casilla);

    bool mueveReina(TableroPrueba* miTablero,const int casilla);

    void muevePeon(TableroPrueba* miTablero,const int casilla);

    bool mueveRey(TableroPrueba* miTablero, const int casilla);





    void generaMovimientos(TableroPrueba* miTablero);

    //Singleton;
    ModuloIA(void);
    void operator=(const ModuloIA& frameListener ) ;
    ModuloIA(const ModuloIA& ModuloIA);


    short valorFicha(const tipoF tipo);


};


#endif
