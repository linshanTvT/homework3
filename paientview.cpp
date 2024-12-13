#include "paientview.h"
#include "ui_paientview.h"
#include "idatabase.h"
PaientView::PaientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PaientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &IDatabase = IDatabase::getInstance();
    if (IDatabase.initPatientM0del()) {
        ui->tableView->setModel(IDatabase.patienTabModel);
        ui->tableView->setSelectionModel(IDatabase.thePatientSelection);
    }
}

PaientView::~PaientView()
{
    delete ui;
}

void PaientView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(currow);
}


void PaientView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchPatient(filter);
}


void PaientView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();
}


void PaientView::on_btEdit_clicked()
{
    QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex();
    emit goPatientEditView(curIndex.row());
}

