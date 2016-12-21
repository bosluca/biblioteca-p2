#ifndef UTENTE_H
#define UTENTE_H
#include "info_utente.h"
#include "opera.h"
#include "database.h"
//#include "database_utente_opere.h"
#include <QXmlStreamWriter>
#include<QString>
#include<iostream>

class utente {
private:
    QString Nome;                          //nome dell'utente
    QString Cognome;                      //cognome dell'utente
    QString codicefiscale;                 //codice fiscale dell'utente
    QString password;                       //password per accedere alla biblioteca
    contenitore<opera>* opereuser;     //ogni utente ha un proprio contenitore di opere che ha in prestito
    database* puntdb;                               //puntatore al database della biblioteca
    unsigned int id;                                 //ogni utente ha un codice identificativo univoco

    static unsigned int maxid;                       //massimo id (ultimo id) che è stato assegnato ad un utente
                                            //(l'ultimo utente che è stato memorizzato nel database)
public:
    utente(QString,QString,QString,QString,database*);              //costruttore a 0,5 parametri (id del nuovo utente sarà id=maxid+1)


    virtual ~utente();
    QString GetNome() const;            //restituisce il nome di un utente
    QString GetCognome() const;         //restituisce il cognome di un utente
    QString GetCodicefiscale() const;   //restituisce il codice fiscale di un utente
    QString GetPassword() const;        //restituisce la password di un utente.
    contenitore<opera>* Getcontainer() const {return opereuser;}
    database* Getpuntdb() const {return puntdb;}
    unsigned int GetID() const;
    unsigned int Getmaxid() const;

    void SetID(unsigned int);

    //metodi propri di utente:
    virtual void Write_utente(QXmlStreamWriter&) const =0; //scrivo l'utente nel database
    virtual void Write_utenteopere(QXmlStreamWriter&) const =0;
    virtual QString Get_tipo_utente() const =0;   //ritorna il tipo di utente
    virtual info_utente infoutente() const =0;
    virtual void  ricevi_opera(unsigned int) =0; //metodo che da in prestito un opera a seconda del tipo di utente sono imposte certe condizioni
    virtual void restituisci_opera(unsigned int); //metodo che restituisce un opera alla biblioteca.

};

#endif // UTENTE_H
