#ifndef PAIENTVIEW_H
#define PAIENTVIEW_H

#include <QWidget>

namespace Ui {
class PaientView;
}

class PaientView : public QWidget
{
    Q_OBJECT

public:
    explicit PaientView(QWidget *parent = nullptr);
    ~PaientView();

private slots:
    void on_btAdd_clicked();

    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

signals:
    void goPatientEditView(int idx);

private:
    Ui::PaientView *ui;
};

#endif // PAIENTVIEW_H
