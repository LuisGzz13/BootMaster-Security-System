#ifndef IP_H
#define IP_H
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class iP {
private:
  int ip1, ip2, ip3, ip4, port;

public:
  iP();
  iP(std::string);

  void stringIn(std::string);
  std::string stringOut();

  bool operator<(const iP &other) const;
  bool operator==(const iP &other) const;
};

// Constructor default (todo en 0)
// entrada: nada
// proceso: todas variables en 0
// salida: nada
iP::iP() {
  ip1 = 0;
  ip2 = 0;
  ip3 = 0;
  ip4 = 0;
  port = 0;
}

// Constructor no default llama a stringIN
// entrada: un string en formato de ip con puerto
// proceso: llama a stringIN
// salida: nada
iP::iP(std::string _strIN) { stringIn(_strIN); }

// Toma un valor string y lo convierte en 4 direcciones y 1 puerto
// entrada: un string en formato de ip con puerto
// proceso: separa los valores de ip (toma los INT antes de cada ".", y después
// del ":"" puerto) salida: nada (se guarda valores en variables de la clase)
void iP::stringIn(std::string ipAddress) {
  std::istringstream ss(ipAddress);
  char dot, colon;
  ss >> ip1 >> dot >> ip2 >> dot >> ip3 >> dot >> ip4 >> colon >> port;
}

// Regresa un valor string de la dirección IP
std::string iP::stringOut() {
  std::ostringstream oss;
  oss << ip1 << '.' << ip2 << '.' << ip3 << '.' << ip4 << ":" << port;
  return oss.str();
}

// comparación de ip, regresa valor TRUE o FALSE
// entrada: una variable tipo iP
// proceso: compara todos los enteros de la clase para determinar si uno es
// menor que otro salida: bool (TRUE || FALSE)
bool iP::operator<(const iP &other) const {
  if (ip1 != other.ip1)
    return ip1 < other.ip1;
  if (ip2 != other.ip2)
    return ip2 < other.ip2;
  if (ip3 != other.ip3)
    return ip3 < other.ip3;
  if (ip4 != other.ip4)
    return ip4 < other.ip4;
  return port < other.port;
}

// comparación de ip, regresa valor TRUE o FALSE
// entrada: una variable tipo iP
// proceso: compara todos los enteros de la clase para determinar si son iguales
// salida: bool (TRUE || FALSE)
bool iP::operator==(const iP &other) const {
  return ip1 == other.ip1 && ip2 == other.ip2 && ip3 == other.ip3 &&
         ip4 == other.ip4 && port == other.port;
}

#endif