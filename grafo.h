#ifndef GRAFO_H
#define GRAFO_H
#include "nodo.h"
#include "stack2.h"
#include <iostream>
#include <queue>

using namespace std;
class grafo {
private:
  nodo *head = nullptr;

public:
  ~grafo();
  nodo *addNodo(std::string);
  void addAdyacencia(nodo *, std::string);
  void BreadthFirst(vector<string> &);
  void DepthFirst();
  nodo *getNodoByID(std::string);
};

void nodo::addAdyacencia(std::string _id) {
  adyacencia *nueva = new adyacencia(_id);
  if (conexiones == nullptr) {
    conexiones = nueva;
    return;
  }
  adyacencia *last = conexiones;
  while (last->getNext() != nullptr) {
    last = last->getNext();
  }
  last->setNext(nueva);
}

nodo::~nodo() {
  adyacencia *last = conexiones, *next;
  while (last != nullptr) {
    next = last->getNext();
    delete last;
    last = next;
  }
}

grafo::~grafo() {
  nodo *last = head, *next;
  while (last != nullptr) {
    next = last->getNext();
    delete last;
    last = next;
  }
}

nodo *grafo::addNodo(std::string id) {
  nodo *nuevo = new nodo(id);
  if (head == nullptr) {
    head = nuevo;
    return nuevo;
  }
  nodo *last = head;
  while (last->getNext() != nullptr) {
    last = last->getNext();
  }
  last->setNext(nuevo);
  return nuevo;
}

void grafo::addAdyacencia(nodo *nodo, std::string id) {
  nodo->addAdyacencia(id);
}

nodo *grafo::getNodoByID(std::string id) {
  nodo *v = head;
  while (v != nullptr) {
    if (v->Id() == id) {
      return v;
    }
    v = v->getNext();
  }
  return nullptr;
}

void grafo::BreadthFirst(vector<string> &strVect) {
  nodo *v = head;
  while (v != nullptr) {
    v->setEstatus(enEspera);
    v = v->getNext();
  }
  v = head;
  std::queue<nodo *> fila;
  while (v != nullptr) {
    if (v->getEstatus() == enEspera) {
      fila.push(v);
      while (!fila.empty()) {
        nodo *u = fila.front();
        fila.pop();
        std::cout << u->Id() << "\n";
        strVect.push_back(u->Id());
        u->setEstatus(procesado);
        adyacencia *adyacencias = u->getAdyacencia();
        while (adyacencias != nullptr) {
          nodo *a = getNodoByID(adyacencias->Id());
          if (a->getEstatus() == enEspera) {
            fila.push(a);
            a->setEstatus(listo);
          }
          adyacencias = adyacencias->getNext();
        }
      }
    }
    v = v->getNext();
  }
  std::cout << std::endl;
}

void grafo::DepthFirst() {
  nodo *v = head;
  while (v != nullptr) {
    v->setEstatus(enEspera);
    v = v->getNext();
  }
  v = head;
  stack2<nodo *> pila;
  while (v != nullptr) {
    if (v->getEstatus() == enEspera) {
      pila.push(v);
      while (!pila.isEmpty()) {
        nodo *u = pila.Top();
        pila.pop();
        if (u->getEstatus() == enEspera) {
          std::cout << u->Id() << " ";
          u->setEstatus(procesado);
          adyacencia *adyacencias = u->getAdyacencia();
          while (adyacencias != nullptr) {
            nodo *a = getNodoByID(adyacencias->Id());
            if (a->getEstatus() == enEspera) {
              pila.push(a);
            }
            adyacencias = adyacencias->getNext();
          }
        }
      }
    }
    v = v->getNext();
  }
  std::cout << std::endl;
}

#endif