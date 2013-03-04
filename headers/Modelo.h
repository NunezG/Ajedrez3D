class Modelo
{
public:
    bool getApagar();
    int getNumPantalla();
    ~Modelo(void);

private:  
    bool mShutDown;
    int mPantalla;

    unsigned long mLastStatUpdateTime;    // The last time the stat text were updated

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);

};
