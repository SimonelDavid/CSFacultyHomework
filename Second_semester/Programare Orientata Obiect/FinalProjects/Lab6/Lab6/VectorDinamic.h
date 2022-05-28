#pragma once
#include <iostream> 
#include "Validator.h"
class IteratorLista;

template<typename TElem>
class Lista {
private:
    struct node {
    public:
        TElem* payload;
        node* next;
        node* last;
    };
    node* start_node;
    node* end_node;

    int nrElems;
public:
    int getNrElems()const noexcept {
        return nrElems;
    }
    class iterator {
    public:
        node* curent;
        iterator() noexcept :curent{ nullptr } {}

        void operator++() noexcept {
            if (curent != nullptr)curent = curent->next;
        }
        iterator& operator+(int nr) noexcept {
            int i = 0;
            while (i < nr && curent != NULL)curent = curent->next, ++i;

            return (*this);
        }
        bool operator==(const Lista<TElem>::iterator& a)const noexcept {
            return curent == a.curent;
        }
        bool operator!=(const Lista<TElem>::iterator& a)const noexcept {
            return !(curent == a.curent);
        }
        TElem* operator->() noexcept {
            return curent->payload;
        }

        void operator=(const Lista<TElem>::iterator& a) noexcept {
            curent = a.curent;
        }
        TElem& operator*() noexcept {
            return *(curent->payload);
        }
    };

    Lista() :start_node{ NULL }, end_node{ NULL }, nrElems{ 0 }{};

    TElem& operator[](int index) {
        int i = 0;
        if (index < nrElems) {
            node* aux = start_node;
            while (i < index) {
                aux = aux->next;
                ++i;
            }

            return aux->payload;
        }
    }

    void push_back(TElem to_add) {
        if (empty()) {
            start_node = new node;
            end_node = new node;

            start_node->payload = new TElem(to_add);
            start_node->next = end_node;
            start_node->last = NULL;

            end_node->last = start_node;
            end_node->next = NULL;
        }
        else {
            node* aux = new node;

            end_node->payload = new TElem(to_add);
            end_node->next = aux;
            node* helper = end_node;

            end_node = aux;
            end_node->next = NULL;
            end_node->last = helper;
        }
        ++nrElems;
    }

    void pop_back() {
        node* aux = end_node;
        end_node = end_node->last;

        delete end_node->payload;
        end_node->payload = NULL;
        end_node->next = NULL;

        delete aux;
        --nrElems;
    }

    void erase(iterator& to_erase) {

        if (nrElems > 1 && to_erase.curent != NULL) {
            node* actual = to_erase.curent;

            if (actual != start_node) {
                actual->last->next = actual->next;
                actual->next->last = actual->last;
            }
            else if (actual == start_node) {
                actual->next->last = actual->last;
                start_node = actual->next;
            }

            delete actual->payload;
            delete actual;
            --nrElems;
        }
        else if (nrElems == 1 && to_erase.curent != NULL) {
            delete start_node->payload;
            delete start_node;
            delete end_node;

            start_node = NULL;
            end_node = NULL;
            nrElems = 0;
        }

    }

    void clear() {
        while (start_node != end_node) {
            delete start_node->payload;
            node* aux = start_node;

            start_node = start_node->next;
            delete aux;
        }
        nrElems = 0;
    }

    bool empty() const {
        return nrElems == 0;
    }

    iterator begin() const {
        Lista<TElem>::iterator i;
        i.curent = start_node;
        return i;
    }

    iterator end() const {
        Lista<TElem>::iterator i;
        i.curent = end_node;

        return i;
    }

    ~Lista() {
        if (start_node != nullptr && end_node != nullptr) {
            while (start_node != end_node) {
                node* aux = start_node;
                delete start_node->payload;
                start_node = start_node->next;
                delete aux;
            }
            delete end_node;
        }
    }

};