#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>

class IDatabase : public QObject
{
    Q_OBJECT
public:
    static IDatabase &getInstance()
    {
        static IDatabase instance;
        return instance;
    }

    QString userLogin(QString userName, QString passWord);

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &)             = delete;
    void operator=(IDatabase const &) = delete;
    QSqlDatabase database;
    void ininDatabase();

signals:

public:
    bool initPatientM0del();
    int addNewPatient();
    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    bool revertPatientEdit();
    QSqlTableModel *patienTabModel;
    QItemSelectionModel *thePatientSelection;
};

#endif // IDATABASE_H
