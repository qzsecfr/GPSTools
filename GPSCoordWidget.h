#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;
class QRadioButton;

class GPSCoordWidget : public QWidget
{
    Q_OBJECT

public:
    GPSCoordWidget(QWidget* parent = nullptr);
    ~GPSCoordWidget() = default;

private:
    void _init();

private slots:
    void _onBtnClicked();

private:
    QLineEdit* m_latEdit;
    QLineEdit* m_lonEdit;
    QLineEdit* m_altEdit;
    QLineEdit* m_ecefXEdit;
    QLineEdit* m_ecefYEdit;
    QLineEdit* m_ecefZEdit;

    QRadioButton* m_dmsRBtn;
    QRadioButton* m_degreeRBtn;

    QPushButton* m_xyz2blhBtn;
    QPushButton* m_blh2xyzBtn;
    QPushButton* m_xyz2blhBatchBtn;
    QPushButton* m_blh2xyzBatchBtn;
};