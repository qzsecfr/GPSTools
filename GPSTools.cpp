#include "GPSTools.h"
#include "GPSTimeWidget.h"
#include "GPSCoordWidget.h"

#include <QTabWidget>
#include <QHBoxLayout>

GPSTools::GPSTools(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QString::fromLocal8Bit("GPS����"));
    _init();
}

void GPSTools::_init()
{
    m_tabWidget = new QTabWidget;
    m_gpsTimeWidget = new GPSTimeWidget(this);
    m_gpsCoordWidget = new GPSCoordWidget(this);
    m_tabWidget->addTab(m_gpsTimeWidget, QString::fromLocal8Bit("GPSʱ��ת��"));
    m_tabWidget->addTab(m_gpsCoordWidget, QString::fromLocal8Bit("WGS-84����ת��"));

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(m_tabWidget);
}
