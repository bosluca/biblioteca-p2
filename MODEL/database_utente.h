#ifndef DATABASE_UTENTE_H
#define DATABASE_UTENTE_H

#include<iostream>
#include<QFile>
#include<QXmlStreamWriter>
#include<QXmlStreamReader>
#include<QString>
#include<vector>

#include"contenitore.h"
#include"opera.h"
#include"utente.h"
#include"utente_basic.h"
#include"utente_pro.h"




class database{
private:
    //campi dati
    static QString filename;
    contenitore db;                                     //creo il contenitore leggendo il file xml

    void Load();
    void Close();                                       //salva tutti i cambiamenti eseguiti dall'utente nel file XML

public:
     database();
    ~database();

    bool vuoto() const;                                 //ritorna true <=> contenitore è vuoto altrimenti ritorna false
    void remove_utente(const int);                       //elimina un utente
    opera* trova_utente(unsigned int) const;
    void add_utentepro(const info_utente&);                             //aggiunge un utente_pro
    void add_utentebasic(const info_utente&);                               //aggiunge un utente basic



    contenitore::iteratore db_iter;

    contenitore::iteratore db_begin();
    contenitore::iteratore db_end();

};

#endif // DATABASE_UTENTE_H