#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VTKPolyData.h"

#include <QVTKOpenGLNativeWidget.h>

class VTKPolyData : public QMainWindow
{
    Q_OBJECT

public:
    VTKPolyData(QWidget *parent = nullptr);
    ~VTKPolyData();

private:
    Ui::VTKPolyDataClass ui;

    QVTKOpenGLNativeWidget* _pVTKWidget = nullptr;
};
