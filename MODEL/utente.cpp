#include "utente.h"
#include<QString>
#include "database_utente_opere.h"


//inizializzo maxid di un utente:
unsigned int utente::maxid=0;


//costruttore di utente:
utente::utente(database *db, database_utente_opere* udb, QString n ="Sconosciuto", QString c ="Sconosciuto", QString  cf ="Sconosciuto", QString psw ="Sconosciuto", unsigned int no=0): Nome(n), Cognome(c), codicefiscale(cf), password(psw),opereBiblioteca(db), opereUtente(udb),numeroopere(no) {
    maxid++;
    id=maxid;

}

utente::~utente() {}


QString utente::GetNome() const {return Nome;}

QString utente::GetCognome() const {return Cognome;}

QString utente::GetCodicefiscale() const {return codicefiscale;}

QString utente::GetPassword() const {return password;}

unsigned int utente::GetID() const {return id;}

unsigned int utente::Getmaxid() const {return maxid;}

void utente::Set_maxid(const int x) {maxid=x;}

void utente::SetID(unsigned int x) {id=x;}

void utente::Setnome(QString n) {Nome=n;}

void utente::Setcognome(QString cn) {Cognome=cn;}

unsigned int& utente::setnumeroopere() {return numeroopere;}
unsigned int utente::Getnumeroopere() const {return numeroopere;}

database* utente::GetopereBiblioteca() const {return opereBiblioteca;}


database_utente_opere* utente::GetdbOpereUtente() const {return opereUtente;}




