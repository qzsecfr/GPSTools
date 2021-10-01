#include "GPSTimeWidget.h"
#include "GPSAlgorithm.h"

#include <QDateTimeEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

GPSTimeWidget::GPSTimeWidget(QWidget* parent)
    : QWidget(parent)
{
    _init();
}

void GPSTimeWidget::_init()
{
    QLabel* utcLabel = new QLabel(QString::fromLocal8Bit("UTC时间"));
    m_utcEdit = new QDateTimeEdit;
    m_utcEdit->setDateTime(QDateTime::currentDateTimeUtc());
    m_utcEdit->setCalendarPopup(true);
    m_utcEdit->setDisplayFormat("yyyy/MM/dd hh:mm:ss");

    QLabel* dayOfYearLabel = new QLabel(QString::fromLocal8Bit("年积日"));
    m_dayOfYearEdit = new QLineEdit;
    m_dayOfYearEdit->setValidator(new QIntValidator(1, 366));

    QLabel* gpsWeekLabel = new QLabel(QString::fromLocal8Bit("GPS周"));
    m_gpsWeekEdit = new QLineEdit;
    m_gpsWeekEdit->setValidator(new QIntValidator(1, 9999));

    QLabel* gpsSecLabel = new QLabel(QString::fromLocal8Bit("周内秒"));
    m_gpsSecondEdit = new QLineEdit;
    m_gpsSecondEdit->setValidator(new QDoubleValidator(0, 604800, 6));

    m_utc2gpsBtn = new QPushButton(QString::fromLocal8Bit("-->"));
    m_gps2utcBtn = new QPushButton(QString::fromLocal8Bit("<--"));

    connect(m_utc2gpsBtn, SIGNAL(clicked(bool)), SLOT(_onBtnClicked()));
    connect(m_gps2utcBtn, SIGNAL(clicked(bool)), SLOT(_onBtnClicked()));
    connect(m_utcEdit, SIGNAL(dateChanged(QDate)), SLOT(_onDateChanged()));

    QGroupBox* utcBox = new QGroupBox(QString::fromLocal8Bit("UTC时间"));
    {
        QGridLayout* utcLayout = new QGridLayout(utcBox);
        utcLayout->addWidget(utcLabel, 0, 0);
        utcLayout->addWidget(m_utcEdit, 0, 1);
        utcLayout->addWidget(dayOfYearLabel, 1, 0);
        utcLayout->addWidget(m_dayOfYearEdit, 1, 1);
    }
    QGroupBox* gpsBox = new QGroupBox(QString::fromLocal8Bit("GPS时间"));
    {
        QGridLayout* gpsLayout = new QGridLayout(gpsBox);
        gpsLayout->addWidget(gpsWeekLabel, 0, 0);
        gpsLayout->addWidget(m_gpsWeekEdit, 0, 1);
        gpsLayout->addWidget(gpsSecLabel, 1, 0);
        gpsLayout->addWidget(m_gpsSecondEdit, 1, 1);
    }
    QVBoxLayout* btnLayout = new QVBoxLayout;
    {
        btnLayout->addStretch();
        btnLayout->addWidget(m_utc2gpsBtn);
        btnLayout->addSpacing(10);
        btnLayout->addWidget(m_gps2utcBtn);
        btnLayout->addStretch();
    }
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(utcBox);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(gpsBox);

    // 初始化DOY
    _onDateChanged();
}

void GPSTimeWidget::_onBtnClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == nullptr)
    {
        return;
    }
    else if (btn == m_gps2utcBtn)
    {
        int gpsWeek = m_gpsWeekEdit->text().toInt();
        double gpsSecond = m_gpsSecondEdit->text().toDouble();
        UTCT utct = GPST2UTCT(GPST(gpsWeek, gpsSecond));
        m_utcEdit->setDateTime(utct.getDateTime());
        _onDateChanged();
    }
    else if (btn == m_utc2gpsBtn)
    {
        GPST gpst = UTCT2GPST(UTCT(m_utcEdit->dateTime()));
        m_gpsWeekEdit->setText(QString::number(gpst.week));
        m_gpsSecondEdit->setText(QString::number(gpst.second, 'f', 3));
    }
}

void GPSTimeWidget::_onDateChanged()
{
    UTCT utct(m_utcEdit->dateTime());
    int dayOfYear = UTCT2DOY(utct);
    if (dayOfYear)
    {
        m_dayOfYearEdit->setText(QString::number(dayOfYear));
    }
}