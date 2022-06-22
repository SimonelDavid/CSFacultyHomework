//
// Created by david on 20.05.2022.
//

#include "Gui.h"

void Gui::init() {
    setLayout(mainL);
    mainL->addWidget(lst);

    mijloc->setLayout(mijlocL);
    mijlocL->addWidget(new QLabel("nume"));
    mijlocL->addWidget(numeTxt);
    mijlocL->addWidget(new QLabel("job"));
    mijlocL->addWidget(jobTxt);
    mijlocL->addWidget(new QLabel("status"));
    mijlocL->addWidget(candCombo);
    candCombo->addItem("hired");
    candCombo->addItem("rejected");
    candCombo->addItem("pending");
    mijlocL->addWidget(modBtn);

    mainL->addWidget(mijloc);


    dreapta->setLayout(dreaptaL);
    dreaptaL->addWidget(new QLabel("nume"));
    dreaptaL->addWidget(filterTxt);
    ///dreaptaL->addWidget(filterBtn);
    dreaptaL->addWidget(reloadBtn);

    mainL->addWidget(dreapta);

}

void Gui::conect() {
    QObject::connect(filterTxt, &QLineEdit::textChanged, [&]() {
        if (filterTxt->text().toStdString().empty()) {
            reload(srv.getAll());
            return;
        };
        //if(srv.filterNume(filterTxt->text().toStdString()).empty())reload(srv.getAll());
        reload(srv.filterNume(filterTxt->text().toStdString()));
    });

    QObject::connect(reloadBtn, &QPushButton::clicked, [&]() {
        reload(srv.getAll());
    });
    QObject::connect(filterBtn, &QPushButton::clicked, [&]() {
        if (filterTxt->text().isEmpty())return;
        reload(srv.filterNume(filterTxt->text().toStdString()));
    });
    QObject::connect(modBtn, &QPushButton::clicked, [&]() {
        if (jobTxt->text().isEmpty())return;
        if (numeTxt->text().isEmpty())return;
        if (lst->selectedItems().isEmpty())return;
        Candidat c = srv.find(lst->selectedItems()[0]->data(Qt::UserRole).toString().toStdString());
        c.setNume(numeTxt->text().toStdString());
        c.setJob(jobTxt->text().toStdString());
        c.setCandidatura(candCombo->itemText(candCombo->currentIndex()).toStdString());
        srv.mod(c.getId(), c.getNume(), c.getJob(), c.getCandidatura());
        reload(srv.getAll());
    });

    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        if (lst->selectedItems().isEmpty())return;
        Candidat c = srv.find(lst->selectedItems()[0]->data(Qt::UserRole).toString().toStdString());
        jobTxt->setText(QString::fromStdString(c.getJob()));
        numeTxt->setText(QString::fromStdString(c.getNume()));
        if (c.getCandidatura() == "hired") {
            candCombo->setCurrentIndex(0);
        }
        if (c.getCandidatura() == "pending") {
            candCombo->setCurrentIndex(2);
        }
        if (c.getCandidatura() == "rejected") {
            candCombo->setCurrentIndex(1);
        }
    });
}

void Gui::reload(const vector <Candidat> &list) {
    lst->clear();
    for (auto &c: list) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString::fromStdString(c.getNume() + " || " + c.getJob() + " || " + c.getCandidatura()));
        item->setData(Qt::UserRole, QString::fromStdString(c.getId()));
        lst->addItem(item);
        if (c.getCandidatura() == "hired") {
            candCombo->setCurrentIndex(0);
            item->setBackground(Qt::green);
        }
        if (c.getCandidatura() == "pending") {
            candCombo->setCurrentIndex(2);
            item->setBackground(Qt::yellow);
        }
        if (c.getCandidatura() == "rejected") {
            candCombo->setCurrentIndex(1);
            item->setBackground(Qt::red);
        }
    }
}
