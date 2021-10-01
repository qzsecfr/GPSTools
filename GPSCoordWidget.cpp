#include "GPSCoordWidget.h"
#include "GPSAlgorithm.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

GPSCoordWidget::GPSCoordWidget(QWidget* parent)
    : QWidget(parent)
{
    _init();
}

void GPSCoordWidget::_init()
{
    auto* latLonFormatGroup = new QGroupBox;
    {
        auto* latLonFormatLabel = new QLabel(QString::fromLocal8Bit("经纬度格式"));
        m_dmsRBtn = new QRadioButton(QString::fromLocal8Bit("度分秒(dd.mmsssss)"));
        m_degreeRBtn = new QRadioButton(QString::fromLocal8Bit("度(dd.ddddddd)"));
        m_dmsRBtn->setChecked(true);

        auto* latLonFormatLayout = new QHBoxLayout(latLonFormatGroup);
        latLonFormatLayout->addWidget(latLonFormatLabel, 0, Qt::AlignRight);
        latLonFormatLayout->addSpacing(20);
        latLonFormatLayout->addWidget(m_dmsRBtn, 1);
        latLonFormatLayout->addSpacing(10);
        latLonFormatLayout->addWidget(m_degreeRBtn, 1);
        latLonFormatLayout->addSpacing(10);
    }
    
    auto* ecefGroup = new QGroupBox(QString::fromLocal8Bit("WGS-84 空间坐标"));
    {
        auto* ecefXLabel = new QLabel(QString::fromLocal8Bit("X"));
        m_ecefXEdit = new QLineEdit;
        m_ecefXEdit->setValidator(new QDoubleValidator);
        auto* ecefYLabel = new QLabel(QString::fromLocal8Bit("Y"));
        m_ecefYEdit = new QLineEdit;
        m_ecefYEdit->setValidator(new QDoubleValidator);
        auto* ecefZLabel = new QLabel(QString::fromLocal8Bit("Z"));
        m_ecefZEdit = new QLineEdit;
        m_ecefZEdit->setValidator(new QDoubleValidator);

        auto* ecefLayout = new QGridLayout(ecefGroup);
        ecefLayout->addWidget(ecefXLabel, 0, 0, Qt::AlignRight);
        ecefLayout->addWidget(m_ecefXEdit, 0, 1);
        ecefLayout->addWidget(ecefYLabel, 1, 0, Qt::AlignRight);
        ecefLayout->addWidget(m_ecefYEdit, 1, 1);
        ecefLayout->addWidget(ecefZLabel, 2, 0, Qt::AlignRight);
        ecefLayout->addWidget(m_ecefZEdit, 2, 1);
    }

    auto* blhGroup = new QGroupBox(QString::fromLocal8Bit("WGS-84 大地坐标"));
    {
        auto* latLabel = new QLabel(QString::fromLocal8Bit("纬度"));
        m_latEdit = new QLineEdit;
        m_latEdit->setValidator(new QDoubleValidator);
        auto* lonLabel = new QLabel(QString::fromLocal8Bit("经度"));
        m_lonEdit = new QLineEdit;
        m_lonEdit->setValidator(new QDoubleValidator);
        auto* altLabel = new QLabel(QString::fromLocal8Bit("大地高"));
        m_altEdit = new QLineEdit;
        m_altEdit->setValidator(new QDoubleValidator);

        auto* blhLayout = new QGridLayout(blhGroup);
        blhLayout->addWidget(latLabel, 0, 0, Qt::AlignRight);
        blhLayout->addWidget(m_latEdit, 0, 1);
        blhLayout->addWidget(lonLabel, 1, 0, Qt::AlignRight);
        blhLayout->addWidget(m_lonEdit, 1, 1);
        blhLayout->addWidget(altLabel, 2, 0, Qt::AlignRight);
        blhLayout->addWidget(m_altEdit, 2, 1);
    }

    auto* btnLayout = new QVBoxLayout;
    {
        m_xyz2blhBtn = new QPushButton(QString::fromLocal8Bit("-->"));
        m_blh2xyzBtn = new QPushButton(QString::fromLocal8Bit("<--"));
        connect(m_xyz2blhBtn, SIGNAL(clicked()), SLOT(_onBtnClicked()));
        connect(m_blh2xyzBtn, SIGNAL(clicked()), SLOT(_onBtnClicked()));

        btnLayout->addStretch();
        btnLayout->addWidget(m_xyz2blhBtn);
        btnLayout->addSpacing(10);
        btnLayout->addWidget(m_blh2xyzBtn);
        btnLayout->addStretch();
    }

    auto* batchBtnLayout = new QHBoxLayout;
    {
        m_xyz2blhBatchBtn = new QPushButton(QString::fromLocal8Bit("批量XYZ转BLH"));
        m_blh2xyzBatchBtn = new QPushButton(QString::fromLocal8Bit("批量BLH转XYZ"));
        connect(m_xyz2blhBatchBtn, SIGNAL(clicked()), SLOT(_onBtnClicked()));
        connect(m_blh2xyzBatchBtn, SIGNAL(clicked()), SLOT(_onBtnClicked()));

        batchBtnLayout->addWidget(m_xyz2blhBatchBtn);
        batchBtnLayout->addSpacing(10);
        batchBtnLayout->addWidget(m_blh2xyzBatchBtn);
        batchBtnLayout->setContentsMargins(5, 2, 5, 2);
    }

    auto* mainLayout = new QVBoxLayout(this);
    {
        auto* middleLayout = new QHBoxLayout;
        middleLayout->addWidget(ecefGroup, 1);
        middleLayout->addLayout(btnLayout);
        middleLayout->addWidget(blhGroup, 1);

        mainLayout->addWidget(latLonFormatGroup);
        mainLayout->addLayout(middleLayout, 1);
        mainLayout->addLayout(batchBtnLayout);
    }
}

void GPSCoordWidget::_onBtnClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == nullptr)
    {
        return;
    }
    else if (btn == m_xyz2blhBtn)
    {
        // TODO
    }
    else if (btn == m_blh2xyzBtn)
    {
        // TODO
    }
    else if (btn == m_xyz2blhBatchBtn)
    {
        // TODO
    }
    else if (btn == m_blh2xyzBatchBtn)
    {
        // TODO
    }
}