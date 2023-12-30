#ifndef ORDENAR_ADYACENCIA_H
#define ORDENAR_ADYACENCIA_H
#include <iostream>
#include <sstream>
#include <string>

#include "iP.h"

using namespace std;

class ordenarAdyacencia {
private:
  iP ip;
  string message;

public:
  ordenarAdyacencia();
  ordenarAdyacencia(string);

  iP getIP() const;
  string getMessage() const;

};

ordenarAdyacencia::ordenarAdyacencia() {
  iP auxiliarIp("0.0.0.0:0000");
  ip = auxiliarIp;
  message = "";
}

ordenarAdyacencia::ordenarAdyacencia(string _line) {
  istringstream iss(_line);
  
  string _mes, _dia, _hora, _ip, _message;

  // leer la linea sin mensaje
  iss >> _mes >> _dia >> _hora >> _ip;
  getline(iss, _message); // lee lo que sigue


  iP auxiliarIp(_ip);

 
  ip = auxiliarIp;
  message = _message;
}

iP ordenarAdyacencia::getIP() const { 
  return ip; 
}

string ordenarAdyacencia::getMessage() const { 
  return message; 
}

bool compararIP(const ordenarAdyacencia &objectOne, const ordenarAdyacencia &objectTwo) {
  return objectOne.getIP() < objectTwo.getIP();
};

#endif