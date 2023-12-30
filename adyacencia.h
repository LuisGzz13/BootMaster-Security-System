#ifndef ADYACENCIA_H
#define ADYACENCIA_H
#include <string>

class adyacencia {
  private:
    std::string id;
    adyacencia *next = nullptr;
  public:
    adyacencia(std::string _id) {id = _id;}
    void setNext(adyacencia *_next) {next = _next;}
    adyacencia* getNext() {return next;}
    std::string Id() {return id;}
};

#endif