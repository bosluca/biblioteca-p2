#include"listautenti.h"

listautenti::listautenti(database* db,database_utente* udb): Widget_Padre(db,udb){
    table=new QTableWidget();

  //inserisco la tabella nel layout del widget
    layout_table=new QVBoxLayout();
    layout_table->addWidget(table);
    set_style();
    setLayout(layout_table);

    costruisci_contenuto();

    connect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doppio_click(int)));     //doppio click
    connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(click_singolo(int)));          //click singolo

}

void listautenti::costruisci_contenuto(){ aggiorna_vista(); }

void listautenti::aggiorna_vista(){

    int row=0;
        database_utente* ciao=get_modelutenti();
        if(!((get_modelutenti())->vuoto()))
        {
             int id;
             QString i;
             contenitore<utente>::iteratore it;
             for(it=(get_modelutenti())->dbutenti_begin(); it!=(get_modelutenti())->dbutenti_end(); it++)
             {
                table->setRowCount(row+1);
                id=(*it)->GetID();
                i.setNum(id);

                QTableWidgetItem *ID = new QTableWidgetItem(i);
                QTableWidgetItem *nome = new QTableWidgetItem((*it)->GetNome());
                QTableWidgetItem *cognome = new QTableWidgetItem((*it)->GetCognome());

                table->setItem(row,0,ID);
                table->setItem(row,1,nome);
                table->setItem(row,2,cognome);
                row++;
             }
        }
        else{
                table->setRowCount(row);
                emit tabella_vuota();
            }
}

void listautenti::set_style(){
    Widget_Padre::set_style();
  //set numero righe e colonne della tabella
    table->setColumnCount(3);
    table->setRowCount(0);

  //set dimensioni tabella
    table->setMinimumWidth(700);
    table->setColumnWidth(0,50);
    table->setColumnWidth(1,505);
    table->setColumnWidth(2,100);
    table->setMaximumWidth(700);
    table->setMinimumHeight(300);
    table->setMaximumHeight(600);

    //intestazione tabella
    QStringList tabHeader;
    tabHeader<<"ID"<<"Nome"<<"Cognome";
    table->setHorizontalHeaderLabels(tabHeader);

    //comportamento nel momento in cui si seleziona un item
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void listautenti::build_Nuova(const contenitore<utente>& lista){
    int row=0;
    if(!(lista.empty()))
    {
         int id;
         QString i;
         contenitore<utente>::iteratore it;

         for(it=lista.begin(); it!=lista.end(); it++)
         {
            table->setRowCount(row+1);
            id=(*it)->GetID();
            i.setNum(id);

            QTableWidgetItem *ID = new QTableWidgetItem(i);
            QTableWidgetItem *nome = new QTableWidgetItem((*it)->GetNome());
            QTableWidgetItem *cognome = new QTableWidgetItem((*it)->GetCognome());

            table->setItem(row,0,ID);
            table->setItem(row,1,nome);
            table->setItem(row,2,cognome);
            row++;
         }
    }
    else{
            table->setRowCount(row);
            emit tabella_vuota();
        }
}


void listautenti::doppio_click(int r){
    select_utente=table->item(r,0)->text().toInt();
    emit richiesta_info(select_utente);
}

void listautenti::click_singolo(int r){
    select_utente=table->item(r,0)->text().toInt();
    emit selezione(select_utente);
}

listautenti::~listautenti(){
    delete table;
    delete layout_table;
}

void listautenti::abilita_doppio_click(){
    connect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doppio_click(int)));
    emit abilita_funzioni();
}

void listautenti::disabilita_doppio_click(){
    disconnect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doppio_click(int)));
    emit disabilita_funzioni();
}
