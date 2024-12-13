#include "idatabase.h"
#include <QUuid>

void IDatabase::ininDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "D:/qtDocuments/project3/Lab4/lab4.db";
    database.setDatabaseName(aFile);
    if (!database.open()) {
        qDebug() << "failed";
    } else qDebug() << "open";
}

bool IDatabase::initPatientM0del()
{
    patienTabModel = new QSqlTableModel(this, database);
    patienTabModel->setTable("patient");
    patienTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patienTabModel->setSort(patienTabModel->fieldIndex("name"), Qt::AscendingOrder);
    if (!(patienTabModel->select()))
        return false;
    thePatientSelection = new QItemSelectionModel(patienTabModel);
    return true;
}

int IDatabase::addNewPatient()
{
    patienTabModel->insertRow(patienTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = patienTabModel->index(patienTabModel->rowCount() - 1, 1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = patienTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    patienTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patienTabModel->setFilter(filter);
    return patienTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patienTabModel->removeRow(curIndex.row());
    patienTabModel->submitAll();
    patienTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patienTabModel->submitAll();
}

bool IDatabase::revertPatientEdit()
{
    patienTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString passWord)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER", userName);
    query.exec();

    if (query.first() && query.value("username").isValid()) {
        QString passwd = query.value("password").toString();
        if (passwd == passWord) {
            qDebug() << "login ok";
            return "loginOk";
        } else {
            qDebug() << "wrong password";
            return "wrongPassword";
        }
    } else {
        qDebug() << "no such user";
        return "wrongUsername";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
