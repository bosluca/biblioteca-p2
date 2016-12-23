#include "MODEL/database_utente_opere.h"

//faccio l'include del file xml:
QString database_utente_opere::filename="../biblioteca-p2/opereutenti.xml";



contenitore<opera>::iteratore database_utente_opere::dbopereutenti_begin() {return dbopereutente.begin();}

contenitore<opera>::iteratore database_utente_opere::dbopereutenti_end() {return dbopereutente.end();}



//creare un database significa caricare il file database.xml:
database_utente_opere::database_utente_opere(database_utente * u) : utenti(u) {database_utente_opere::Load();}


//"distruggere" un database significa fare la chiusura del file database.xml:
database_utente_opere::~database_utente_opere() {database_utente_opere::Close();}


//quando carico il database scrivo tutte le opre nel mio contenitore:
void database_utente_opere::Load() {
    QString Titolo="Sconosciuto",Autore="Sconosciuto", AnnoUscita="Sconosciuto";
     int Idutente=-1, Id=-1, Stato=-1, Tipoutente=0, Tipo=0;
    opera*tmp=NULL;
    utente*tmp1=NULL;
    QFile file(filename);
         file.open(QIODevice::ReadOnly);
           // if (!file.open(QFile::ReadOnly | QFile::Text))  std::cout << "Errore: Impossibile leggere il file"<< std::endl;
         QXmlStreamReader xmlReader(&file);
         xmlReader.readNext();
         while(!xmlReader.atEnd())
         {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name()=="opereutente" || xmlReader.name()=="utente") xmlReader.readNext();
                else
                    if(xmlReader.name()=="Tipoutente") Tipoutente=xmlReader.readElementText().toInt();
                    else
                        if(xmlReader.name()=="Idutente") Idutente=xmlReader.readElementText().toInt();
                        else
                    if(Tipoutente==1)//sto leggendo un utente_basic e relative opere:
                    {
                        if(xmlReader.name()=="database" || xmlReader.name()=="opera") xmlReader.readNext();
                        else
                            if(xmlReader.name()=="Tipo") Tipo=xmlReader.readElementText().toInt();
                            else
                                if(xmlReader.name()=="Id") Id=xmlReader.readElementText().toInt();
                                else
                                    if(xmlReader.name()=="Stato") Stato=xmlReader.readElementText().toInt();
                                    else
                            if(Tipo==1)//sto leggendo un libro:
                            {
                                if(xmlReader.name()=="Titolo") Titolo=xmlReader.readElementText();
                                else
                                    if(xmlReader.name()=="Autore") Autore=xmlReader.readElementText();
                                else std::cout<<"Errore nella lettura di un libro";
                            }
                            else if(Tipo==2)
                            {
                                if(xmlReader.name()=="Titolo") Titolo=xmlReader.readElementText();
                                else
                                    if(xmlReader.name()=="AnnoUscita") AnnoUscita=xmlReader.readElementText();
                                else std::cout<<"Errore nella lettura di una rivista";
                            }
                    }
                    else if(Tipoutente==2)
                    {
                        if(xmlReader.name()=="database" || xmlReader.name()=="opera") xmlReader.readNext();
                        else
                            if(xmlReader.name()=="Tipo") Tipo=xmlReader.readElementText().toInt();
                            else
                                if(xmlReader.name()=="Id") Id=xmlReader.readElementText().toInt();
                                else
                                    if(xmlReader.name()=="Stato") Stato=xmlReader.readElementText().toInt();
                                    else
                            if(Tipo==1)//sto leggendo un libro:
                            {
                                if(xmlReader.name()=="Titolo") Titolo=xmlReader.readElementText();
                                else
                                    if(xmlReader.name()=="Autore") Autore=xmlReader.readElementText();
                                else std::cout<<"Errore nella lettura di un libro";
                            }
                            else if(Tipo==2)
                            {
                                if(xmlReader.name()=="Titolo") Titolo=xmlReader.readElementText();
                                else
                                    if(xmlReader.name()=="AnnoUscita") AnnoUscita=xmlReader.readElementText();
                                else std::cout<<"Errore nella lettura di una rivista";
                            }
                    }

         }
         else //sono alla fine del documento quindi:
         {      //sono al tag /utente
                //devo salvare le opere di ciascun utente nel proprio contenitore:
             if(xmlReader.isEndDocument() && xmlReader.name()=="utente")
             {
                 if(Tipoutente==1)
                 {
                    database_utente* prova=Getutente();
                    utente* prova2=prova->trova_utente(Idutente);

                 }
                 else if(Tipoutente==2)
                 {

                 }

                xmlReader.readNext();
              }
             else xmlReader.readNext();
         }
         }


}

//apporto le modifiche riscrivendo tutto il database:
void database_utente_opere::Close() {
    QFile file(filename);
         file.open(QIODevice::WriteOnly);

         QXmlStreamWriter xmlWriter(&file);
         xmlWriter.setAutoFormatting(true);
         xmlWriter.writeStartDocument();
        if(!vuoto())
        {
         xmlWriter.writeStartElement("database");
         contenitore<opera>::iteratore it;
         for(it=dbopereutente.begin();it!=dbopereutente.end();it++)
         {
             (*it)->Write_opera(xmlWriter);
         }
         xmlWriter.writeEndDocument();
        }
        file.close();
}

//rimuovere un opera dal database significa:
/*1) cercare l'opera nel database con quel id;
 * (utilizzare un opportuno metodo)
 * 2) rimuoverla dal mio contenitore di opere;
 * 3) aggiornare il database;
 * (metodo close aggiorna il database con le modifiche!)
*/

opera* database_utente_opere::trova_operadelutente(unsigned int id) const{
   if(vuoto()) return 0;

   contenitore<opera>::iteratore it;
   contenitore<opera>::iteratore risultato;
   bool trovato=false;
   it=dbopereutente.begin();
   while(it!=dbopereutente.end() && !trovato)
   {
       if((*it)->GetId()==id){ trovato=true;}
           risultato=it;
           it++;

   }
   if(trovato) return *risultato;
   return 0;
}
void database_utente_opere::remove_operadelutente(const int id) {
opera*tmp=trova_operadelutente(id);
if(tmp!=0){dbopereutente.remove_item(tmp);}
else std::cout<<"Errore opera non presente nel database";
}


bool database_utente_opere::vuoto() const {return dbopereutente.empty();}


void database_utente_opere::aggiungi_opera_utente(opera *o) {
    if(o!=0 && o->presente())
    {
        o->Presta_opera();
        dbopereutente.add_item(o);
    }
}

database_utente* database_utente_opere::Getutente() const {return utenti;}
