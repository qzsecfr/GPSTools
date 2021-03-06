#include "GPSTools.h"
#include "GPSTimeWidget.h"
#include "GPSCoordWidget.h"

#include <QTabWidget>
#include <QHBoxLayout>

GPSTools::GPSTools(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QString::fromLocal8Bit("GPS工具"));
    _init();
}

void GPSTools::_init()
{
    m_tabWidget = new QTabWidget;
    m_gpsTimeWidget = new GPSTimeWidget(this);
    m_gpsCoordWidget = new GPSCoordWidget(this);
    m_tabWidget->addTab(m_gpsTimeWidget, QString::fromLocal8Bit("GPS时间转换"));
    m_tabWidget->addTab(m_gpsCoordWidget, QString::fromLocal8Bit("WGS-84坐标转换"));

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(m_tabWidget);
}
