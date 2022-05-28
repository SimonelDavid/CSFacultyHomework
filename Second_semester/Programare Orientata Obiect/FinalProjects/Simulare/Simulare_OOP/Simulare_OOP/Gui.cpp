#include "Gui.h"

void Gui::init() {
    setLayout(mainL);
    mainL->addWidget(listaCandidati);

    mainL->addWidget(formDreapta);
    mainL->addWidget(status);


    formDreapta->setLayout(formDreaptaL);
    formDreaptaL->addWidget(new QLabel{"nume candidat: "});
    formDreaptaL->addWidget(nameCandidat);
    formDreaptaL->addWidget(new QLabel{"job candidat: "});
    formDreaptaL->addWidget(jobCandidat);
    formDreaptaL->addWidget(new QLabel{"status candidat:"});
    formDreaptaL->addWidget(statusCandidat);
    formDreaptaL->addWidget(addBtn);
}

void Gui::conec() {
    QObject::connect(addBtn, &QPushButton::clicked, [&](){
        if(statusCandidat->text().isEmpty()||nameCandidat->text().isEmpty()||jobCandidat->text().isEmpty())return;
        
        string satusCandidat = statusCandidat->text().toStdString();
        string nume = nameCandidat->text().toStdString();
        string job = jobCandidat->text().toStdString();
        string status = satusCandidat;
        service.addCandidat(nume, job, status);
        reloadListaCandidati(service.getCandidati());
        
    });
    QObject::connect(listaCandidati,&QListWidget::itemSelectionChanged,[&](){
                         if(listaCandidati->selectedItems().isEmpty())return;
                         string nameCandidat = listaCandidati->selectedItems()[0]->text().toStdString();
                         string jobCandidat = listaCandidati->selectedItems()[0]->text().toStdString();
                         string statusCandidat = listaCandidati->selectedItems()[0]->text().toStdString();
                     });
}

void Gui::reloadListaCandidati(vector<Candidat> lst) {
    listaCandidati->clear();
    for(auto& candidat : lst){
        listaCandidati->addItem(QString::fromStdString(candidat.getNume()));
    }
}