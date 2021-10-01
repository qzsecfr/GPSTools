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
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

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
        m_latEdit->setValidator(new QDoubleValidator(-90, 90, 12));
        auto* lonLabel = new QLabel(QString::fromLocal8Bit("经度"));
        m_lonEdit = new QLineEdit;
        m_lonEdit->setValidator(new QDoubleValidator(-180, 180, 12));
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

double GPSCoordWidget::_transToDegree(double currentValue)
{
    if (m_degreeRBtn->isChecked())
    {
        return currentValue;
    }
    int D = static_cast<int>(currentValue);
    int M = static_cast<int>((currentValue - D) * 100.0);
    double S = ((currentValue - D) * 100.0 - M) * 100.0;
    return D + M / 60.0 + S / 3600.0;
}

double GPSCoordWidget::_transFromDegree(double degree)
{
    if (m_degreeRBtn->isChecked())
    {
        return degree;
    }
    int D = static_cast<int>(degree);
    int M = static_cast<int>((degree - D) * 60.0);
    double S = (degree - D - M / 60.0) * 3600.0;
    return D + M / 100.0 + S / 10000.0;
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
        double X = m_ecefXEdit->text().toDouble();
        double Y = m_ecefYEdit->text().toDouble();
        double Z = m_ecefZEdit->text().toDouble();
        BLH blh = XYZ2BLH(XYZ(X, Y, Z));
        m_latEdit->setText(QString::number(_transFromDegree(blh.lat), 'f', 9));
        m_lonEdit->setText(QString::number(_transFromDegree(blh.lon), 'f', 9));
        m_altEdit->setText(QString::number(blh.alt, 'f', 3));
    }
    else if (btn == m_blh2xyzBtn)
    {
        double lat = _transToDegree(m_latEdit->text().toDouble());
        double lon = _transToDegree(m_lonEdit->text().toDouble());
        double alt = m_altEdit->text().toDouble();
        XYZ xyz = BLH2XYZ(BLH(lat, lon, alt));
        m_ecefXEdit->setText(QString::number(xyz.X, 'f', 3));
        m_ecefYEdit->setText(QString::number(xyz.Y, 'f', 3));
        m_ecefZEdit->setText(QString::number(xyz.Z, 'f', 3));
    }
    else if (btn == m_xyz2blhBatchBtn)
    {
        QString xyzFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择要转换的XYZ文件。"), "", "*.txt;;*.*");
        if (xyzFileName.isEmpty())
        {
            return;
        }
        QString blhFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("选择要保存的BLH文件。"), "", "*.txt;;*.*");
        if (blhFileName.isEmpty())
        {
            return;
        }
        QFile xyzFile(xyzFileName);
        if (!xyzFile.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("无法打开所选的XYZ文件。"));
            return;
        }
        QFile blhFile(blhFileName);
        if (!blhFile.open(QIODevice::Text | QIODevice::WriteOnly))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("无法写入所选的BLH文件。"));
            return;
        }
        while (!xyzFile.atEnd())
        {
            QString line = QString::fromLocal8Bit(xyzFile.readLine());
            QStringList lineList = line.split(",");
            if (lineList.size() < 3)
            {
                continue;
            }
            double X = lineList[0].trimmed().toDouble();
            double Y = lineList[1].trimmed().toDouble();
            double Z = lineList[2].trimmed().toDouble();
            BLH blh = XYZ2BLH(XYZ(X, Y, Z));
            QString writeLine;
            writeLine += QString::number(_transFromDegree(blh.lat), 'f', 9) + ",";
            writeLine += QString::number(_transFromDegree(blh.lon), 'f', 9) + ",";
            writeLine += QString::number(blh.alt, 'f', 3) + "\n";
            blhFile.write(writeLine.toLocal8Bit());
        }
        xyzFile.close();
        blhFile.flush();
        blhFile.close();
        QMessageBox::information(this, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("XYZ文件转BLH已完成。"));
    }
    else if (btn == m_blh2xyzBatchBtn)
    {
        QString blhFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择要转换的BLH文件。"), "", "*.txt;;*.*");
        if (blhFileName.isEmpty())
        {
            return;
        }
        QString xyzFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("选择要保存的XYZ文件。"), "", "*.txt;;*.*");
        if (xyzFileName.isEmpty())
        {
            return;
        }
        QFile blhFile(blhFileName);
        if (!blhFile.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("无法打开所选的BLH文件。"));
            return;
        }
        QFile xyzFile(xyzFileName);
        if (!xyzFile.open(QIODevice::Text | QIODevice::WriteOnly))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("无法写入所选的XYZ文件。"));
            return;
        }
        while (!blhFile.atEnd())
        {
            QString line = QString::fromLocal8Bit(blhFile.readLine());
            QStringList lineList = line.split(",");
            if (lineList.size() < 3)
            {
                continue;
            }
            double lat = _transToDegree(lineList[0].trimmed().toDouble());
            double lon = _transToDegree(lineList[1].trimmed().toDouble());
            double alt = lineList[2].trimmed().toDouble();
            XYZ xyz = BLH2XYZ(BLH(lat, lon, alt));
            QString writeLine;
            writeLine += QString::number(xyz.X, 'f', 3) + ",";
            writeLine += QString::number(xyz.Y, 'f', 3) + ",";
            writeLine += QString::number(xyz.Z, 'f', 3) + "\n";
            xyzFile.write(writeLine.toLocal8Bit());
        }
        blhFile.close();
        xyzFile.flush();
        xyzFile.close();
        QMessageBox::information(this, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("BLH文件转XYZ已完成。"));
    }
}