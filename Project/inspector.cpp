#include "inspector.h"
#include "ui_inspector.h"

inspector::inspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inspector)
{
    ui->setupUi(this);
}

inspector::~inspector()
{
    delete ui;
}
