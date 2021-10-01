#pragma once

#include <QtWidgets/QWidget>

class QTabWidget;
class GPSTimeWidget;
class GPSCoordWidget;

class GPSTools : public QWidget
{
    Q_OBJECT

        QTabWidget* m_tabWidget = nullptr;
    GPSTimeWidget* m_gpsTimeWidget = nullptr;
    GPSCoordWidget* m_gpsCoordWidget = nullptr;

public:
    GPSTools(QWidget *parent = Q_NULLPTR);

private:
    void _init();
};
