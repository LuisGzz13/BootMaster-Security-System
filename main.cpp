#include "grafo.h"
#include "nodo.h"
#include "ordenarAdyacencia.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;


// lee el txt y lo hace en un vector
vector<ordenarAdyacencia> leerTXT(const string &fileName) {
  vector<ordenarAdyacencia> archivoBitacora;
  ifstream file(fileName);

  // error test si abre el file
  if (!file.is_open()) {
    cout << endl << "Error al leer el archivo" << fileName << endl;
    return archivoBitacora;
  }

  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    ordenarAdyacencia temporary(line);                
    archivoBitacora.push_back(temporary); 
  }

  file.close();
  return archivoBitacora;
}

// funcion para generar el output file
void dump2TXT(vector<string> &bitacoraFile, string outputF) {
  ofstream outputFile(outputF);


  for (int i = 0; i <= bitacoraFile.size(); i++) {
    outputFile << bitacoraFile[i] << endl;
  }
}

struct messageCount {
  
  string mensaje;

  int cuenta;
};

bool comparamessageAmount(const messageCount &a, const messageCount &b) {
  return a.cuenta > b.cuenta;
}

int main() {
  // cargamos el archivo txt a un vector
  vector<ordenarAdyacencia> bitacoraFile = leerTXT("bitacora.txt");
  sort(bitacoraFile.begin(), bitacoraFile.end(), compararIP); // ordenar por IP

  // mapa para ordenar los mensajes malos
  unordered_map<string, int> badMessage;
  int messageAmount = 0;
  for (int i = 0; i < bitacoraFile.size(); i++) {
    string tempMessage = bitacoraFile[i].getMessage();

    if (badMessage.find(tempMessage) == badMessage.end()) {
      badMessage[tempMessage] =
          messageAmount++; 
    }
  }

  // vectorizamos los malos mensajes
  vector<vector<ordenarAdyacencia>>     
  datosMensaje(messageAmount);
 
  
  for (int i = 0; i < bitacoraFile.size(); i++) {
    
    string tempMessage = bitacoraFile[i].getMessage();
    int datosV = badMessage[tempMessage]; 
    
    datosMensaje[datosV].push_back(bitacoraFile[i]);
  }

  //Se crea el grafo
  grafo _grafo;
  
  for (int i = 0; i < messageAmount; i++) {
    
    nodo *n, *ramaIP;
    n = _grafo.addNodo(datosMensaje[i][0].getMessage());

    
    cout << "Se crea un nodo: " << datosMensaje[i][0].getMessage() << endl;

    // id es el IP y se va creando la dayacencia de cada nodo en base al mensaje de error de la bitacora
    for (int j = 0; j < datosMensaje[i].size(); j++) {
      
      ramaIP = _grafo.addNodo(datosMensaje[i][j].getIP().stringOut());
      _grafo.addAdyacencia(ramaIP, datosMensaje[i][0].getMessage());

      
      _grafo.addAdyacencia(n, datosMensaje[i][j].getIP().stringOut());
    }
  }
 
  vector<string> output;
  _grafo.BreadthFirst(output);

  dump2TXT(output, "outputFinal.txt");

  cout << "fan out con TOTALES: " << endl;
  vector<messageCount> cuentaMensajeTot(messageAmount);
  for (int i = 0; i < messageAmount; i++) {
    cuentaMensajeTot[i].mensaje = datosMensaje[i][0].getMessage();
    cuentaMensajeTot[i].cuenta = datosMensaje[i].size();
  }
  sort(cuentaMensajeTot.begin(), cuentaMensajeTot.end(), comparamessageAmount);

  for (int i = 0; i < messageAmount; i++) {
    cout << "|" << cuentaMensajeTot[i].mensaje  << " aparece: " << cuentaMensajeTot[i].cuenta << " veces" << endl;
  }

  return 0;
}