#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

class nodo{
	public:

		int fil;
		int col;
		int orientacion;
		int f;
		int g;
		int h;
		nodo *padre;

		int getF(){return fil;}

		int getC(){return col;}

		int getO(){return orientacion;}

		nodo(){
			fil = col = orientacion = f = g = h = 0;
		
			padre = NULL;
		}

		nodo(int f, int c, int o, int gf, nodo *p){
			fil = f;
			col = c;
			orientacion = o;
			g = gf;

			padre = p;
		}

		nodo operator=(const nodo  &copia) const{

			nodo cop = nodo(copia.fil, copia.col, copia.orientacion, copia.g, copia.padre);
			cop.f = copia.f;
			cop.h = copia.h;

			return cop;
		}

		bool operator==(const nodo &otro) const{
			if (this->fil == otro.fil and this->col==otro.col and this->orientacion==otro.orientacion 
				and this->f==otro.f and this->g==otro.g and this->h==otro.h and this->padre==otro.padre){
				return true;
			}else
				return false;

		}

		bool operator!=(const nodo  &otro) const{
			return !(*this==otro);
		}

		bool operator< (const nodo &otro) const{

			if (*this==otro)
				return false;
			else if (this->h<otro.h)
				return true;
			else if(this->f<otro.f)
				return true;
			else if(this->g<otro.g)
				return true;
			else 
				return false;
		}

		void heuristica(nodo otro){

			if (this->fil - otro.fil <0)
				h += otro.fil - this->fil;
			else
				h += this->fil - otro.fil;

			if (this->col - otro.col <0)
				h += otro.col - this->col;
			else
				h += this->col- otro.col;
		}

		int funcion(){
			this->f= this->g + this->h;

			return this->f;
		}

		
};

bool aStar( nodo &origen, pair<int,int> meta, stack<Action> &plan, vector<vector<unsigned char>> mapaResultado){

	nodo destino= nodo(meta.first, meta.second, 0, -1, NULL);

	origen.heuristica(destino);

	set<nodo> abiertos;
	set<nodo> cerrados;

	abiertos.insert(destino);  //***********************************************************
	abiertos.insert(origen);

	nodo actual = origen;

	bool primera = true;

	while(!abiertos.empty() and actual!=destino){

		if(primera){
			primera = false;
			cerrados.insert(actual);
			abiertos.erase(abiertos.begin());
		}else{
			cerrados.insert(actual);
			actual = *abiertos.begin();
			abiertos.erase(abiertos.begin());
		}

		nodo n1;
		nodo n2;
		nodo n3;


		unsigned char front;
		unsigned char left;
		unsigned char right;

		switch(origen.getO()){
			case 0://Norte
				n1 = nodo(actual.getF()-1, actual.getC(), actual.getO(), actual.g+1, &actual);
				n2 = nodo(actual.getF(), actual.getC(), 1, actual.g+1, &actual);
				n3 = nodo(actual.getF(), actual.getC(), 3, actual.g+1, &actual);

				front = mapaResultado[actual.getF()-1][actual.getC()];
				left = mapaResultado[actual.getF()][actual.getC()-1];
				right= mapaResultado[actual.getF()][actual.getC()+1];

				if (front == 'T' or front == 'S' or front == 'K'){
					n1.heuristica(destino);
					abiertos.insert(n1);
				}

				if (right == 'T' or right == 'S' or right == 'K'){
					n2.heuristica(destino);
					abiertos.insert(n2);
				}
	
				if (left == 'T' or left == 'S' or left == 'K'){
					n3.heuristica(destino);
					abiertos.insert(n3);
				}

				break;

			case 1://Este
				n1 = nodo(actual.getF(), actual.getC()+1, actual.getO(), actual.g+1, &actual);
				n2 = nodo(actual.getF(), actual.getC(), 2, actual.g+1, &actual);
				n3 = nodo(actual.getF(), actual.getC(), 0, actual.g+1, &actual);

				front = mapaResultado[actual.getF()][actual.getC()+1];
				left = mapaResultado[actual.getF()-1][actual.getC()];
				right= mapaResultado[actual.getF()+1][actual.getC()];

				if (front == 'T' or front == 'S' or front == 'K'){
					n1.heuristica(destino);
					abiertos.insert(n1);
				}

				if (right == 'T' or right == 'S' or right == 'K'){
					n2.heuristica(destino);
					abiertos.insert(n2);
				}
	
				if (left == 'T' or left == 'S' or left == 'K'){
					n3.heuristica(destino);
					abiertos.insert(n3);
				}

				break;
			case 2://Sur
				n1 = nodo(actual.getF()+1, actual.getC(), actual.getO(), actual.g+1, &actual);
				n2 = nodo(actual.getF(), actual.getC(), 3, actual.g+1, &actual);
				n3 = nodo(actual.getF(), actual.getC(), 1, actual.g+1, &actual);

				front = mapaResultado[actual.getF()+1][actual.getC()];
				left = mapaResultado[actual.getF()][actual.getC()+1];
				right= mapaResultado[actual.getF()][actual.getC()-1];

				if (front == 'T' or front == 'S' or front == 'K'){
					n1.heuristica(destino);
					abiertos.insert(n1);
				}

				if (right == 'T' or right == 'S' or right == 'K'){
					n2.heuristica(destino);
					abiertos.insert(n2);
				}
	
				if (left == 'T' or left == 'S' or left == 'K'){
					n3.heuristica(destino);
					abiertos.insert(n3);
				}
			
				break;
			case 3://Oeste
				n1 = nodo(actual.getF(), actual.getC()-1, actual.getO(), actual.g+1, &actual);
				n2 = nodo(actual.getF(), actual.getC(), 0, actual.g+1, &actual);
				n3 = nodo(actual.getF(), actual.getC(), 2, actual.g+1, &actual);

				front = mapaResultado[actual.getF()][actual.getC()-1];
				left = mapaResultado[actual.getF()+1][actual.getC()];
				right= mapaResultado[actual.getF()-1][actual.getC()];

				if (front == 'T' or front == 'S' or front == 'K'){
					n1.heuristica(destino);
					abiertos.insert(n1);
				}

				if (right == 'T' or right == 'S' or right == 'K'){
					n2.heuristica(destino);
					abiertos.insert(n2);
				}
	
				if (left == 'T' or left == 'S' or left == 'K'){
					n3.heuristica(destino);
					abiertos.insert(n3);
				}

				break;
		}//Fin Switch

	}


	while(actual != origen){

		actual = *cerrados.begin();

		if (actual.getF() != actual.padre->fil or actual.getC() != actual.padre->col){
			plan.push(actFORWARD);
		}else if(actual.getO() > actual.padre->getO()){
			plan.push(actTURN_R);
		}else if(actual.getO() < actual.padre->getO()){
			plan.push(actTURN_L);
		}

		cerrados.erase(actual);
	}

	return true;

}


/*
bool ComportamientoJugador::pathFinding(const Estado &origen, const Estado &destino, list<Action> &plan){

	//Borro la lista
	plan.clear();

	Estado st = origen;

	int difF = origen.fila - destino.fila;
	int difC = origen.columna - destino.columna;

		// Reduzco la distancia en columnas
		if (difC < 0){
			if (st.orientacion == 0){
				plan.push_back(actTURN_R);
				st.orientacion = 1;
			}
			else if (st.orientacion == 3){
						plan.push_back(actTURN_R);
						plan.push_back(actTURN_R);
						st.orientacion = 1;
			}
			else if (st.orientacion == 2){
						plan.push_back(actTURN_L);
						st.orientacion = 1;
			}
		}
		else if (difC > 0){
			if (st.orientacion == 0){
				plan.push_back(actTURN_L);
				st.orientacion = 3;
			}
			else if (st.orientacion == 1){
						plan.push_back(actTURN_R);
						plan.push_back(actTURN_R);
						st.orientacion = 3;
			}
			else if (st.orientacion == 2){
						plan.push_back(actTURN_R);
						st.orientacion = 3;
			}
		}

		// Avanzo la diferencia entre columnas
		if (difC<0)
		  difC = -difC;

	  for (int i=0; i < difC; i++){
			plan.push_back(actFORWARD);
		}

		// Reduzco la distancia en filas
		if (difF < 0){
			if (st.orientacion == 1){
				plan.push_back(actTURN_R);
				st.orientacion = 2;
			}
			else if (st.orientacion == 3){
						plan.push_back(actTURN_L);
						st.orientacion = 2;
			}
		}
		else if (difF > 0){
			if (st.orientacion == 1){
				plan.push_back(actTURN_L);
				st.orientacion = 0;
			}
			else if (st.orientacion == 3){
						plan.push_back(actTURN_R);
						st.orientacion = 0;
			}
		}


		// Avanzo la diferencia entre columnas
		if (difF<0)
		  difF = -difF;

	  for (int i=0; i < difF; i++){
			plan.push_back(actFORWARD);
		}

		return true;

}*/

void ComportamientoJugador::Reiniciar(){
	fil = col = 99;
	ultimaAccion = actIDLE;
	bien_situado = false;
	brujula = 0;
	estoy_ejecutando_plan =false;
	error_plan =false;
	tirar = false;

	mochila=0;

	for(int i =0 ;i<5;++i)
		misObjetos[i]= false;


}

bool hayObstaculoDelante(const vector<unsigned char> & terreno, const vector<unsigned char> & superficie){
	if ( (terreno[2]=='T' or terreno[2]=='S' or terreno[2]=='K') and
				superficie[2]=='_'){
					return false;
	}
	else{
	 return true;
 }
}

void PintaPlan(stack<Action> plan){
	/*auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;*/

	stack<Action> p = plan;

	Action elem = p.top();

	while(!p.empty()){
		if (elem== actFORWARD){
			cout << "A ";
		}
		else if (elem == actTURN_R){
			cout << "D ";
		}
		else if (elem == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}

		p.pop();
		elem = p.top();

	}//For
}

// --------------------------------------------------------------------------------------------------------------------------------------


bool ComportamientoJugador::avanza(Sensores sensores){

	bool resultado = true;

	if (sensores.superficie[2]!='_')
		resultado = false;


	if (sensores.terreno[2] == 'B' && !misObjetos[2])
		resultado = false;
	else if (sensores.terreno[2] == 'A' && !misObjetos[1])
		resultado = false;
	else if (sensores.terreno[2] == 'P')
		resultado = false;
  else if (sensores.terreno[2] == 'M')
        resultado = false;

	return resultado;

}

// --------------------------------------------------------------------------------------------------------------------------------------


Action ComportamientoJugador::objetoMochila(){

	if (ultimaAccion == actPUSH)
		return actPOP;
	else
		return actPUSH;

}

// --------------------------------------------------------------------------------------------------------------------------------------


Action ComportamientoJugador::recorreMapa(Sensores s, bool puedo, int tiempo){

	int left=0, right=0, front=0, minimo;
	Action accion;
	miMapa[fil][col]+=tiempo;

	switch(brujula){ // Norte
		case 0:
			left = miMapa[fil][col-1];
			right = miMapa[fil][col+1];
			front = miMapa[fil-1][col];

			if(!avanza(s) && !puedo)
				miMapa[fil-1][col] += tiempo+100;

			break;

		case 1: // Este
			left = miMapa[fil-1][col];
			right = miMapa[fil+1][col];
			front = miMapa[fil][col+1];

			if(!avanza(s) && !puedo)
				miMapa[fil][col+1] += tiempo+100;
			break;

		case 2: // Sur
			left = miMapa[fil][col+1];
			right = miMapa[fil][col-1];
			front = miMapa[fil+1][col];

			if(!avanza(s) && !puedo)
				miMapa[fil+1][col] += tiempo+100;

			break;

		case 3: // Oeste
			left = miMapa[fil+1][col];
			right = miMapa[fil-1][col];
			front = miMapa[fil][col-1];

			if(!avanza(s) && !puedo)
				miMapa[fil][col-1] += tiempo+100;

			break;

	}

	if (front <= left and front <=right and (avanza(s) or puedo)){
		accion = actFORWARD;
	}else if(left < right){
		accion = actTURN_L;
	}else if (left == right){
		int random = rand()%2;
		if (random == 1){
			accion = actTURN_R;
		}else
			accion = actTURN_L;
	}else
		accion = actTURN_R;
/*
	if (encerrau){
		encerrau = false;
		accion = actTURN_R;

	}else if(ultimaAccion == actTURN_L){
		encerrado = ultimaAccion;
	}else if (ultimaAccion == actTURN_R and encerrado == actTURN_L){
		encerrau = true;
		accion = actTURN_R;
	}*/


	return accion;

}


// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::pintaBordes() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			mapaResultado[i][j] = 'P';
			mapaResultado[j][i] = 'P';
			if (i != 3) {
				mapaResultado[MAX_SIZE - i - 1][j] = 'P';
				mapaResultado[j][MAX_SIZE - i - 1] = 'P';
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::pintaBosque() {
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (mapaResultado[i][j] == '?') {
				mapaResultado[i][j] = 'B';
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::copiaMapa(int f_, int c_){

	int dX, dY;

	if (fil - f_ < 0)
		dX = f_ - fil;
	else
		dX = fil - f_;

	if (col - c_ < 0)
		dY = c_ - col;
	else
		dY = col - c_;


	pintaBordes();

	for (int i = 0; i < 100; ++i){
		for (int j = 0; j < 100; ++j){

			mapaResultado[i][j] = mapaInicial[i+dX][j+dY];
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::rellena2(Sensores s){

    switch(brujula){
        case 0:

            mapaInicial[fil-1][col-1] = s.terreno[1];
            mapaInicial[fil-1][col] = s.terreno[2];
            mapaInicial[fil-1][col+1] = s.terreno[3];


            mapaInicial[fil-2][col-2] = s.terreno[4];
            mapaInicial[fil-2][col-1] = s.terreno[5];
            mapaInicial[fil-2][col] = s.terreno[6];
            mapaInicial[fil-2][col+1] = s.terreno[7];
            mapaInicial[fil-2][col+2] = s.terreno[8];

            mapaInicial[fil-3][col-3] = s.terreno[9];
            mapaInicial[fil-3][col-2] = s.terreno[10];
            mapaInicial[fil-3][col-1] = s.terreno[11];
            mapaInicial[fil-3][col] = s.terreno[12];
            mapaInicial[fil-3][col+1] = s.terreno[13];
            mapaInicial[fil-3][col+2] = s.terreno[14];
            mapaInicial[fil-3][col+3] = s.terreno[15];

            break;
        case 1:

            mapaInicial[fil-1][col+1] = s.terreno[1];
            mapaInicial[fil][col+1] = s.terreno[2];
            mapaInicial[fil+1][col+1] = s.terreno[3];

            mapaInicial[fil-2][col+2] = s.terreno[4];
            mapaInicial[fil-1][col+2] = s.terreno[5];
            mapaInicial[fil][col+2] = s.terreno[6];
            mapaInicial[fil+1][col+2] = s.terreno[7];
            mapaInicial[fil+2][col+2] = s.terreno[8];

            mapaInicial[fil-3][col+3] = s.terreno[9];
            mapaInicial[fil-2][col+3] = s.terreno[10];
            mapaInicial[fil-1][col+3] = s.terreno[11];
            mapaInicial[fil][col+3] = s.terreno[12];
            mapaInicial[fil+1][col+3] = s.terreno[13];
            mapaInicial[fil+2][col+3] = s.terreno[14];
            mapaInicial[fil+3][col+3] = s.terreno[15];


            break;
        case 2:

            mapaInicial[fil+1][col+1] = s.terreno[1];
            mapaInicial[fil+1][col] = s.terreno[2];
            mapaInicial[fil+1][col-1] = s.terreno[3];

            mapaInicial[fil+2][col+2] = s.terreno[4];
            mapaInicial[fil+2][col+1] = s.terreno[5];
            mapaInicial[fil+2][col] = s.terreno[6];
            mapaInicial[fil+2][col-1] = s.terreno[7];
            mapaInicial[fil+2][col-2] = s.terreno[8];

            mapaInicial[fil+3][col+3] = s.terreno[9];
            mapaInicial[fil+3][col+2] = s.terreno[10];
            mapaInicial[fil+3][col+1] = s.terreno[11];
            mapaInicial[fil+3][col] = s.terreno[12];
            mapaInicial[fil+3][col-1] = s.terreno[13];
            mapaInicial[fil+3][col-2] = s.terreno[14];
            mapaInicial[fil+3][col-3] = s.terreno[15];

            break;
        case 3:

            mapaInicial[fil+1][col-1] = s.terreno[1];
            mapaInicial[fil][col-1] = s.terreno[2];
            mapaInicial[fil-1][col-1] = s.terreno[3];

            mapaInicial[fil+2][col-2] = s.terreno[4];
            mapaInicial[fil+1][col-2] = s.terreno[5];
            mapaInicial[fil][col-2] = s.terreno[6];
            mapaInicial[fil-1][col-2] = s.terreno[7];
            mapaInicial[fil-2][col-2] = s.terreno[8];

            mapaInicial[fil+3][col-3] = s.terreno[9];
            mapaInicial[fil+2][col-3] = s.terreno[10];
            mapaInicial[fil+1][col-3] = s.terreno[11];
            mapaInicial[fil][col-3] = s.terreno[12];
            mapaInicial[fil-1][col-3] = s.terreno[13];
            mapaInicial[fil-2][col-3] = s.terreno[14];
            mapaInicial[fil-3][col-3] = s.terreno[15];

            break;


    }

}

// --------------------------------------------------------------------------------------------------------------------------------------

void ComportamientoJugador::rellena(Sensores s){

    switch(brujula){
        case 0:

            mapaResultado[fil-1][col-1] = s.terreno[1];
            mapaResultado[fil-1][col] = s.terreno[2];
            mapaResultado[fil-1][col+1] = s.terreno[3];


            mapaResultado[fil-2][col-2] = s.terreno[4];
            mapaResultado[fil-2][col-1] = s.terreno[5];
            mapaResultado[fil-2][col] = s.terreno[6];
            mapaResultado[fil-2][col+1] = s.terreno[7];
            mapaResultado[fil-2][col+2] = s.terreno[8];

            mapaResultado[fil-3][col-3] = s.terreno[9];
            mapaResultado[fil-3][col-2] = s.terreno[10];
            mapaResultado[fil-3][col-1] = s.terreno[11];
            mapaResultado[fil-3][col] = s.terreno[12];
            mapaResultado[fil-3][col+1] = s.terreno[13];
            mapaResultado[fil-3][col+2] = s.terreno[14];
            mapaResultado[fil-3][col+3] = s.terreno[15];

            break;
        case 1:

            mapaResultado[fil-1][col+1] = s.terreno[1];
            mapaResultado[fil][col+1] = s.terreno[2];
            mapaResultado[fil+1][col+1] = s.terreno[3];

            mapaResultado[fil-2][col+2] = s.terreno[4];
            mapaResultado[fil-1][col+2] = s.terreno[5];
            mapaResultado[fil][col+2] = s.terreno[6];
            mapaResultado[fil+1][col+2] = s.terreno[7];
            mapaResultado[fil+2][col+2] = s.terreno[8];

            mapaResultado[fil-3][col+3] = s.terreno[9];
            mapaResultado[fil-2][col+3] = s.terreno[10];
            mapaResultado[fil-1][col+3] = s.terreno[11];
            mapaResultado[fil][col+3] = s.terreno[12];
            mapaResultado[fil+1][col+3] = s.terreno[13];
            mapaResultado[fil+2][col+3] = s.terreno[14];
            mapaResultado[fil+3][col+3] = s.terreno[15];


            break;
        case 2:

            mapaResultado[fil+1][col+1] = s.terreno[1];
            mapaResultado[fil+1][col] = s.terreno[2];
            mapaResultado[fil+1][col-1] = s.terreno[3];

            mapaResultado[fil+2][col+2] = s.terreno[4];
            mapaResultado[fil+2][col+1] = s.terreno[5];
            mapaResultado[fil+2][col] = s.terreno[6];
            mapaResultado[fil+2][col-1] = s.terreno[7];
            mapaResultado[fil+2][col-2] = s.terreno[8];

            mapaResultado[fil+3][col+3] = s.terreno[9];
            mapaResultado[fil+3][col+2] = s.terreno[10];
            mapaResultado[fil+3][col+1] = s.terreno[11];
            mapaResultado[fil+3][col] = s.terreno[12];
            mapaResultado[fil+3][col-1] = s.terreno[13];
            mapaResultado[fil+3][col-2] = s.terreno[14];
            mapaResultado[fil+3][col-3] = s.terreno[15];

            break;
        case 3:

            mapaResultado[fil+1][col-1] = s.terreno[1];
            mapaResultado[fil][col-1] = s.terreno[2];
            mapaResultado[fil-1][col-1] = s.terreno[3];

            mapaResultado[fil+2][col-2] = s.terreno[4];
            mapaResultado[fil+1][col-2] = s.terreno[5];
            mapaResultado[fil][col-2] = s.terreno[6];
            mapaResultado[fil-1][col-2] = s.terreno[7];
            mapaResultado[fil-2][col-2] = s.terreno[8];

            mapaResultado[fil+3][col-3] = s.terreno[9];
            mapaResultado[fil+2][col-3] = s.terreno[10];
            mapaResultado[fil+1][col-3] = s.terreno[11];
            mapaResultado[fil][col-3] = s.terreno[12];
            mapaResultado[fil-1][col-3] = s.terreno[13];
            mapaResultado[fil-2][col-3] = s.terreno[14];
            mapaResultado[fil-3][col-3] = s.terreno[15];

            break;


    }

}
//***************************************************************************************

Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;
	tiempo++;

	if (sensores.reset){
		Reiniciar();
	}

	// Actualización de la información del mundo
	switch (ultimaAccion) {
		case actFORWARD:
		  if (!sensores.colision){
				switch (brujula) {
					case 0: // Norte
					  fil--;
						break;
					case 1: // Este
					  col++;
						break;
					case 2: // Sur
						fil++;
						break;
					case 3: // Oeste
						col--;
						break;
				}
			}
			break;
		case actTURN_L:
			brujula = (brujula+3)%4;
			if (rand()%2==0) girar_derecha=true;
			else  girar_derecha=false;
		  break;
		case actTURN_R:
			brujula = (brujula+1)%4;
			if (rand()%2==0) girar_derecha=true;
			else  girar_derecha=false;
		  break;
	}

	//cout << tiempo << " fil: " << fil << " col: " << col << endl;

	if (bien_situado){
		rellena(sensores);
	}else{
		rellena2(sensores);
	}

	if (sensores.terreno[0]=='K' and !bien_situado){
		int f = fil;
		int c = col;
		fil = sensores.mensajeF;
		col = sensores.mensajeC;
		bien_situado = true;
		copiaMapa(f,c);
	}

	// Decidir la nueva acción

	if (next){					//Guarda objeto tras cogerlo
			next = false;
			accion = actPUSH;
	}else if (sensores.terreno[0] == 'T' or sensores.terreno[0] == 'S' or sensores.terreno[0] == 'K'){
			
			switch (sensores.superficie[2]){
				case '0':
					if(!misObjetos[0]){
						accion = actPICKUP;
						misObjetos[0] = true;
						next = true;
						mochila++;
					}

					break;

				case '1':
					if(!misObjetos[1]){
						accion = actPICKUP;
						misObjetos[1] = true;
						next = true;
						mochila++;
					}

					break;

				case '2':
					if(!misObjetos[2]){
						accion = actPICKUP;
						misObjetos[2] = true;
						next = true;
						mochila++;
					}

					break;

				case '3':
					if(!misObjetos[3]){
						accion = actPICKUP;
						misObjetos[3] = true;
						next = true;
						mochila++;
					}

					break;

				case '4':
					if(mochila < 4){
						accion = actPICKUP;
						misObjetos[4] = true;
						next = true;
						mochila++;
					}

					break;

			}//Switch
		}
	

	// Decidir la nueva acción
/*
	if (tirar){
		tirar = false;
		accion = actTHROW;
	}else if(sensores.superficie[2] == '0' or sensores.superficie[2] == '1' or sensores.superficie[2] == '2' or sensores.superficie[2] == '3')
	{
		accion=actPICKUP;
		tirar = true;
	}*/

	if (error_plan){
		estoy_ejecutando_plan = false;
	}

	if (estoy_ejecutando_plan and plan.top() == actFORWARD and hayObstaculoDelante(sensores.terreno, sensores.superficie)){
		if (sensores.superficie[2] == 'a' or sensores.superficie[2] == 'l'){
			plan.push(actIDLE);
			error_plan = false;
		}
		else {
			error_plan=true;
		}
	}
	else {
		error_plan = false;
	}


	// Encontrar reyes
	if (noRey and bien_situado){

		unsigned char rey;

		for (int i = 0; i < MAX_SIZE; ++i){
			for (int j = 0; j < MAX_SIZE; ++j){
				rey = mapaResultado[i][j];

				if (rey == 'r')
				{
					reyes[reyes.size()].first=i;
					reyes[reyes.size()].second=j;

					noRey = false;
				}
			}
		}

		
	}

	if(!noRey and bien_situado and tengo_regalo and !estoy_ejecutando_plan){
		nodo origen;
		origen.fil = fil;
		origen.col = col;
		origen.orientacion = brujula;

		int distancia[reyes.size()];

		for (int i = 0; i < reyes.size(); i++) {

			distancia[i] = 0;

			if ((reyes[i].first - fil) < 0) {
				distancia[i] += fil-reyes[i].first;
			}else
				distancia[i] += reyes[i].first-fil;

			if ((reyes[i].second - col) < 0) {
				distancia[i] += col-reyes[i].second;
			}else
				distancia[i] += reyes[i].second-col;

		}

		int *menor = &(distancia[0]);
		int index=0;

		for(int j=1; j<reyes.size(); ++j){
			if(*(menor) > distancia[j]){
				menor=&(distancia[j]);
				index = j;
			}
		}

		pair<int,int> destino;
		destino.first = reyes[index].first;
		destino.second = reyes[index].second;

		estoy_ejecutando_plan = aStar(origen, destino, plan, mapaResultado);



	}else if (tiempo>=50 and bien_situado and !tengo_regalo and !estoy_ejecutando_plan and sensores.regalos.size()>0){
		nodo origen;
		origen.fil = fil;
		origen.col = col;
		origen.orientacion = brujula;
/*
		Estado destino;
		destino.fila = sensores.regalos[0].first;
		destino.columna = sensores.regalos[0].second;*/

		int distancia[sensores.regalos.size()];

		for (int i = 0; i < sensores.regalos.size(); i++) {

			distancia[i] = 0;

			if ((sensores.regalos[i].first - fil) < 0) {
				distancia[i] += fil-sensores.regalos[i].first;
			}else
				distancia[i] += sensores.regalos[i].first-fil;

			if ((sensores.regalos[i].second - col) < 0) {
				distancia[i] += col-sensores.regalos[i].second;
			}else
				distancia[i] += sensores.regalos[i].second-col;

		}

		int *menor = &(distancia[0]);
		int index=0;

		for(int j=1; j<sensores.regalos.size(); ++j){
			if(*(menor) > distancia[j]){
				menor=&(distancia[j]);
				index = j;
			}
		}

		if (*menor <= 350 ) {
			pair<int,int> destino;
			destino.first = sensores.regalos[index].first;
			destino.second = sensores.regalos[index].second;

			estoy_ejecutando_plan = aStar(origen, destino, plan, mapaResultado);
		}


	}


	// Decidir la nueva acción de movimiento
	else if (estoy_ejecutando_plan and !error_plan){
		accion = plan.top();
		plan.pop();
		PintaPlan(plan);
		if (plan.size()==0){
			estoy_ejecutando_plan = false;
		}
	}


	// Movimiento reactivo
   else if(accion == actIDLE){
		// Decidir acciones de no movimiento
			if (sensores.superficie[2] == 'r' and sensores.objetoActivo == '4'){
				accion = actGIVE;
			}else if(sensores.superficie[2] == 'r' and misObjetos[5]){
				accion = objetoMochila();
			}
			else if (sensores.terreno[2] == 'A' && sensores.objetoActivo == '1'){ //*************************** AGUA + BIKINI
				accion = recorreMapa(sensores,true,tiempo);
			}else if (sensores.terreno[2] == 'A' && misObjetos[1]){
				accion = objetoMochila();

			}else if (sensores.terreno[2] == 'B' && sensores.objetoActivo == '2'){			//***************************  BOSQUE + ZAPATILLAS
				accion = recorreMapa(sensores,true,tiempo);
			}else if(sensores.terreno[2] == 'B' && misObjetos[2]){
				accion = objetoMochila();

			}else if (sensores.superficie[2] == 'a' ){
	    	accion = actIDLE;
	    }else if(sensores.superficie[2]== 'r'){
				accion = actTURN_L;
			}else{
	        accion = recorreMapa(sensores,false,tiempo);

	    }

    }





	// Recordar la ultima accion
	ultimaAccion = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
