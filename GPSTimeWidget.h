#pragma once

#include <QWidget>

class QLineEdit;
class QDateTimeEdit;
class QPushButton;

class GPSTimeWidget : public QWidget
{
    Q_OBJECT

public:
    GPSTimeWidget(QWidget* parent = nullptr);
    ~GPSTimeWidget() = default;

private:
    void _init();

private slots:
    void _onBtnClicked();

private:
    QDateTimeEdit* m_utcEdit;
    QLineEdit* m_dayOfYearEdit;
    QLineEdit* m_gpsWeekEdit;
    QLineEdit* m_gpsSecondEdit;

    QPushButton* m_utc2gpsBtn;
    QPushButton* m_gps2utcBtn;
};