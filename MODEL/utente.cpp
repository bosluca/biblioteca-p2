#include "utente.h"
#include<QString>
#include "database_utente_opere.h"


//inizializzo maxid di un utente:
unsigned int utente::maxid=0;


//costruttore di utente:
utente::utente(database *db, QString n ="Sconosciuto", QString c ="Sconosciuto", QString  cf ="Sconosciuto", QString psw ="Sconosciuto"): Nome(n), Cognome(c), codicefiscale(cf), password(psw),opereBiblioteca(db) {
    maxid++;
    id=maxid;
}

//il distruttore di utente va a distruggere anche le sue opere che aveva in prestito
utente::~utente() {}


QString utente::GetNome() const {return Nome;}

QString utente::GetCognome() const {return Cognome;}

QString utente::GetCodicefiscale() const {return codicefiscale;}

QString utente::GetPassword() const {return password;}

unsigned int utente::GetID() const {return id;}

unsigned int utente::Getmaxid() const {return maxid;}

void utente::SetID(unsigned int x) {id=x;}



database* utente::GetopereBiblioteca() const {return opereBiblioteca;}


database_utente_opere* utente::GetdbOpereUtente() const {return opereUtente;}



bool utente::ricerca_campi(const QString& text) const {
int ID=text.toInt();
if((QString::compare(text,GetNome(),Qt::CaseInsensitive))==0) return true;
if((QString::compare(text,GetCognome(),Qt::CaseInsensitive))==0) return true;
if(ID==GetID()) return true;
return false;
}



void utente::restituisci_opera(unsigned int idopera) {
 opera*o=GetdbOpereUtente()->trova_operadelutente(GetID(),idopera);
 if(o!=0)
 {
     o->Setappartenenza(-1);
     o->Riscatta();
     //GROSSO DILEMMA!!!!!!!!!!!!!!!!!!
 }
 {std::cout<<"ATTENZIONE!"<<" "<<"nessuna opera in prestito impossibile restituirla!";}

}
