#pragma once

#include <QtWidgets/QWidget>

class QTabWidget;

class GPSTools : public QWidget
{
    Q_OBJECT

        QTabWidget* m_tabWidget = nullptr;
public:
    GPSTools(QWidget *parent = Q_NULLPTR);

private:
    void _init();
};
