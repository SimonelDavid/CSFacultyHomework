//
// Created by david on 17.05.2022.
//

#include "Gui.h"

void Gui::init() {
    setLayout(mainL);
    mainL->addWidget(procesoareList);
    mainL->addWidget(placiList);

    mainL->addWidget(formDreapta);
    mainL->addWidget(pret);


    formDreapta->setLayout(formDreaptaL);
    formDreaptaL->addWidget(new QLabel{"nume placa: "});
    formDreaptaL->addWidget(namePlaca);
    formDreaptaL->addWidget(new QLabel{"soclu placa: "});
    formDreaptaL->addWidget(socluPlaca);
    formDreaptaL->addWidget(new QLabel{"pret placa:"});
    formDreaptaL->addWidget(pretPlaca);
    formDreaptaL->addWidget(addBtn);
}

void Gui::conec() {
    QObject::connect(addBtn, &QPushButton::clicked, [&](){
        if(pretPlaca->text().isEmpty()||
        namePlaca->text().isEmpty()||
        socluPlaca->text().isEmpty())return;
        try{
            string pretStr = pretPlaca->text().toStdString();
            string nume = namePlaca->text().toStdString();
            string soclu = socluPlaca->text().toStdString();
            int pret = stoi(pretStr);
            service.addPlaca(nume, soclu, pret);
            reloadPlaciList(service.getPlaciDeBaza());
        }catch(std::invalid_argument&){
            QMessageBox::warning(this,
                              "warning",
                              "trebuie intodus un numar");
        }
    });
    QObject::connect(procesoareList,
                     &QListWidget::itemSelectionChanged,
                     [&](){
            if(procesoareList->selectedItems().isEmpty())return;
            reloadPlaciList(service.filterBySoclu(procesoareList->selectedItems()[0]->data(Qt::UserRole).toString().toStdString()));
    });
    QObject::connect(placiList,
                     &QListWidget::itemSelectionChanged,
                     [&](){
                         if(procesoareList->selectedItems().isEmpty())return;
                         if(placiList->selectedItems().isEmpty())return;
                         string nameProcesor = procesoareList->selectedItems()[0]
                                 ->data(Qt::UserRole).
                                 toString().
                                 toStdString();
                         string namePlaca = placiList
                                 ->selectedItems()[0]
                                 ->text()
                                 .toStdString();
                         pret->setText(QString::fromStdString(
                                 "preț: " + std::to_string(
                                         service.pret(nameProcesor,
                                                      namePlaca)
                                         )
                                 ));
                     });
}

void Gui::reloadPlaciList(vector<PlacaDeBaza> lst) {
    placiList->clear();
    for(auto& placa : lst){
        placiList->addItem(QString::fromStdString(placa.getNume()));
    }
}

void Gui::reloadProcesoareList(vector<Procesor> lst) {
    procesoareList->clear();
    for(auto& procesor: lst){
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(procesor.getNume() +
                                                     " - " +
                                                     std::to_string(procesor.getNrThreaduri())));
        item->setData(Qt::UserRole, QString::fromStdString(procesor.getNume()));
        procesoareList->addItem(item);
    }
}
