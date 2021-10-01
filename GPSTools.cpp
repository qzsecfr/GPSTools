#include "GPSTools.h"

#include <QTabWidget>
#include <QHBoxLayout>

GPSTools::GPSTools(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QString::fromLocal8Bit("GPS¹¤¾ß"));
    _init();
}

void GPSTools::_init()
{
    m_tabWidget = new QTabWidget;
    // TODO
    // add widgets

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(m_tabWidget);
}
