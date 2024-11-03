#pragma once

#include <image.h>
#include <QMainWindow>

class Viewer : public QMainWindow {
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
};
