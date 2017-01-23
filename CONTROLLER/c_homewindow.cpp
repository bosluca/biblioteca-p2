#include "CONTROLLER/c_homewindow.h"

c_homewindow::c_homewindow(database * db, database_utente * udb, database_utente_opere* uodb, homewindow* v, QObject *parent) :model(db), modelutenti(udb), modelutenteopere(uodb),view(v),  QObject(parent) {
    connect(view,SIGNAL(show_accedi()),this,SLOT(accedi_admin()));
    connect(view,SIGNAL(show_accediutente(QString,QString)),this,SLOT(accedi_utente(QString,QString)));
    //chiudi
    connect(view,SIGNAL(chiudi_app()),qApp,SLOT(quit()));
}


void c_homewindow::accedi_admin() {

    mainWindow* finestraamministratore= new mainWindow(model,modelutenti,modelutenteopere);
    C_mainWindow* controlleramministratore=new C_mainWindow(model,modelutenti,modelutenteopere,finestraamministratore);
    finestraamministratore->show();
    //view->disabilita_pulsanti_user();

}

void c_homewindow::accedi_utente(QString u,QString p) {

    //cerco utente nel database degli utenti con quel nome e quella password:
    contenitore<utente>::iteratore it;
    bool trovato=false;
    for(it=modelutenti->dbutenti_begin();it!=modelutenti->dbutenti_end() && !trovato;it++)
    {
        if((*it)->GetNome()==u && (*it)->GetPassword()==p)
        {
            trovato=true;
            int id=(*it)->GetID();

            //apro la finestra utente:
            utenteWindow*finestrautente=new utenteWindow(id,model,modelutenti,modelutenteopere);
            c_utentewindow*controllerutente= new c_utentewindow(id,model,modelutenti,modelutenteopere,finestrautente);
            finestrautente->show();
            //view->disabilita_pulsanti_admin();
        }
    }

}
