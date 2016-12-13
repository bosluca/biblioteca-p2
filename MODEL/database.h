#ifndef DATABASE_H
#define DATABASE_H

#include<iostream>
#include<QFile>
#include<QXmlStreamWriter>
#include<QXmlStreamReader>
#include<QString>
#include<vector>

#include"contenitore.h"
#include"opera.h"
#include"rivista.h"
#include"libro.h"
#include"info_opera.h"




class DataBase{
private:
    //campi dati
    static String filename;
    contenitore db;                                     //creo il contenitore leggendo il file xml

    void Load();
    void Close();                                       //salva tutti i cambiamenti eseguiti dall'utente nel file XML

public:
    DataBase();
    ~DataBase();

    bool vuoto() const;                                 //ritorna true <=> contenitore è vuoto altrimenti ritorna false
    void remove_opera(const int);                       //elimina una opera
    contenitore cerca_opera(const String&) const;        //cerca una opera cercando in tutti i campi di essa (ricerca polimorfa). la ricerca è caseInsensitive
    void add_Rivista(const info&);                             //aggiunge una rivista
    void add_Libro(const info&);                               //aggiunge una libro



    contenitore::iteratore db_iterator;

    contenitore::iteratore db_begin();
    contenitore::iteratore db_end();

};



#endif // DATABASE_H
