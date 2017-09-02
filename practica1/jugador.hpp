#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Inicializar Variables de Estado

      MAX_SIZE = size;

      for (int i = 0; i < 200; ++i)
        for (int j = 0; j < 200; ++j){
          mapaInicial[i][j] =0;
          miMapa[i][j]=0;
        }

      for (int i = 0; i < 4; ++i)
        misObjetos[i] = false;

      orientado = false;
      next = false;
      brujula = 0;
      last_action = actIDLE;
      fila = 99;
      columna = 99;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);

    ///////////////////////////////////////////////////////////////////

    void rellena(Sensores s);

    void rellena2(Sensores s);

    bool avanza(Sensores sensores);

    void pintaBordes();

    void pintaBosque();

    Action objetoMochila();

    Action recorreMapa(Sensores s, bool puedo);

    void actualizar(Action last, Sensores s);

    void capturaPK(Sensores s);

    void copiaMapa(int f_, int c_);

    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fila, columna;

    int MAX_SIZE;

    int brujula;

    bool orientado, next;

    int miMapa[200][200];

    unsigned char mapaInicial[200][200];

    bool misObjetos[4];

    Action last_action;


};


#endif
