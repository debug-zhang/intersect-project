#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../src/core/container.h"
#include "../../src/core/IOHandler.h"
#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QColor>
#include <set>
#include <sstream>
#include <iostream>
#include <string>
#include <QStringListModel>
#include <list>
#include <QDir>
#include <QFileDialog>
#include <fstream>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
       void on_addGraph_clicked();

       void on_delGraph_clicked();

       void on_openFile_clicked();

private:
    Ui::MainWindow *ui;
    Container *container;
    IOHandler *io;
    QImage image;
    void updateList();
    void updateGraph();
    void paintEvent(QPaintEvent *event);
    void drawLine(QPainter *painter,double x1,double y1,double x2,double y2);
    void drawRadial(QPainter *painter,double x1,double y1,double x2,double y2);
    void drawSegment(QPainter *painter,double x1,double y1,double x2,double y2);
    void drawDot(QPainter *painter,double x,double y);
    void updateIntersect();

    int readInt(stringstream *buf);
    int readNum(stringstream *buf);
    int readLine(stringstream *buf);
    char readGraphType(stringstream *buf);
};
#endif // MAINWINDOW_H
