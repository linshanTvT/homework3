#include "masterview.h"
#include "ui_masterview.h"
#include "idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    goLoginView();
    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    loginView = new LoginView(this);
    pushWidget(loginView);

    connect(loginView, SIGNAL(loginSuccess()), this, SLOT(goWelcomeView()));
}

void MasterView::goWelcomeView()
{
    welcomeView = new WelcomeView(this);
    pushWidget(welcomeView);
    connect(welcomeView, SIGNAL(goDepartmentView()), this, SLOT(goDepartmentView()));
    connect(welcomeView, SIGNAL(goDoctorView()), this, SLOT(goDoctorView()));
    connect(welcomeView, SIGNAL(goPatientView()), this, SLOT(goPatientView()));
}

void MasterView::goDoctorView()
{
    doctorView = new DoctorView(this);
    pushWidget(doctorView);
}

void MasterView::goDepartmentView()
{
    departmentView = new DepartmentView(this);
    pushWidget(departmentView);
}

void MasterView::goPatientEditView(int rowNo)
{
    patientEditView = new PatientEditView(this, rowNo);
    pushWidget(patientEditView);
    connect(patientEditView, SIGNAL(goPreviousView()), this, SLOT(goPreviousView()));
}

void MasterView::goPatientView()
{
    patientView = new PaientView(this);
    pushWidget(patientView);
    connect(patientView, SIGNAL(goPatientEditView(int)), this, SLOT(goPatientEditView(int)));
}

void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();
    if (count > 1) {
        ui->stackedWidget->setCurrentIndex(count - 2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(count - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::pushWidget(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->labelTitle->setText(widget->windowTitle());
}

void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();

    // 根据栈式控件的数量决定是否启用返回按钮
    if (count > 1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);


    // 获取当前窗口的标题，并根据标题启用/禁用相应的按钮
    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if (title == "欢迎") {
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    } else {
        ui->btLogout->setEnabled(false);
    }
    if (title == "登录") {
        ui->btLogout->setEnabled(false);
        ui->btBack->setEnabled(false);
    }

    if (!ui->btBack->isEnabled()) {
        ui->btBack->setStyleSheet("background-color: lightgray; color: gray;");
    } else {
        ui->btBack->setStyleSheet("");
    }
    if (!ui->btLogout->isEnabled()) {
        ui->btLogout->setStyleSheet("background-color: lightgray; color: gray;");
    } else {
        ui->btLogout->setStyleSheet("");
    }
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

