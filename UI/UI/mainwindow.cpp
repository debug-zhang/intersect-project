#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../src/core/container.h"
#include <QMessageBox>
#include <string>

using namespace std;
#define SIZE 600

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    container =new Container;
    image = QImage(SIZE+5,SIZE+5,QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));
    updateList();
    updateGraph();
    updateIntersect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateList(){
        QStringList list;
        vector<Graph*>* graphs=container-> GetGraphs();
        //list<<QString("L 0 0 1 1")<<QString("R 0 3 1 2")<<QString("S 0 1 2 4")<<QString("S -3 0 -4 2");
        for(Graph *g:*graphs){
            list<<QString::fromStdString(g->ToString());
        }
        QStringListModel *model = new QStringListModel(list);
        ui->list->setModel(model);
}

void MainWindow::updateIntersect(){
    int size=container->Size();
    ui->intersect->setText(QString::number(size));
}

void MainWindow::updateGraph(){
    QPainter painter(&image);
    // 画框
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(0, SIZE/2,SIZE+10,SIZE/2);
    painter.drawLine(SIZE/2, 0,SIZE/2,SIZE+10);
    // 画图
    vector<Graph *>* graphs=container->GetGraphs();
    for (Graph* g : *graphs) {
            if (g->type=='L') {
                double a = g->GetA();
                double b = g->GetB();
                double c = g->GetC();
                if (b == 0) {
                    drawLine(&painter,-c/a,SIZE,-c/a,-SIZE);
                } else {
                    drawLine(&painter,-SIZE, (c - a * SIZE) / -b,SIZE, (c + a * SIZE) / -b);
                }
            } else if (g->type=='R') {
                double endx=g->x1;
                double endy=g->y1;
                double crossx=g->x2;
                double crossy=g->y2;
                while(crossx<SIZE&&crossy<SIZE){
                    crossx=2*crossx-endx;
                    crossy=2*crossy-endy;
                }
                drawLine(&painter,endx,endy,crossx,crossy);
            } else if (g->type=='S') {
                drawLine(&painter,g->x1,g->y1,g->x2,g->y2);
            }
    //画点
    set<pair<double,double>>* dots=container->GetDots();
    for (pair<double,double> d:*dots){
        drawDot(&painter, d.first,d.second);
    }
    update();
    }
}

void MainWindow::on_addGraph_clicked()
{
    stringstream buf(ui->addText->text().append('\n').toStdString());
    ui->delText->clear();
    ui->addText->clear();
    try{
    char type=readGraphType(&buf);
    int x1=readNum(&buf);
    int y1=readNum(&buf);
    int x2=readNum(&buf);
    int y2=readNum(&buf);
    container->AddGraph(type,x1,y1,x2,y2);
    updateList();
    updateGraph();
    updateIntersect();
    }catch (exception &e){
        QMessageBox::information(NULL, "出现异常", e.what());
        return ;
    }
}

void MainWindow::on_delGraph_clicked()
{
    stringstream buf(ui->delText->text().append('\n').toStdString());
    ui->addText->clear();
    ui->delText->clear();
    try{
    char type=readGraphType(&buf);
    int x1=readNum(&buf);
    int y1=readNum(&buf);
    int x2=readNum(&buf);
    int y2=readNum(&buf);
    container->DeleteGraph(type,x1,y1,x2,y2);
    updateList();
    updateGraph();
    updateIntersect();
    }catch (exception &e){
        QMessageBox::information(NULL, "出现异常", e.what());
        return ;
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0,0,image);
}

void MainWindow::drawLine(QPainter *painter,double x1,double y1,double x2,double y2){
    painter->drawLine(x1+SIZE/2,SIZE/2-y1,x2+SIZE/2,SIZE/2-y2);
}
void MainWindow::drawDot(QPainter *painter,double x,double y){
    QRectF rectangle1(x+SIZE/2, SIZE/2-y, 5.0, 5.0);
    painter->drawEllipse(rectangle1);
}

void MainWindow::on_openFile_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, QString("choose a file"), ".");
    if (fileName.isEmpty())
        return;
    io=new IOHandler(fileName.toStdString(),"output.txt");
    int line=io->readLine();
    for (int i = 0; i < line; i++) {
            char type = io->readGraphType();
            int x1 = io->readNum();
            int y1 = io->readNum();
            int x2 = io->readNum();
            int y2 = io->readNum();
            container->AddGraph(type, x1, y1, x2, y2);
        }
    updateList();
    updateGraph();
    updateIntersect();
}

int MainWindow::readInt(stringstream *buf){
    int res;
    *buf >> res;
    if (buf->peek() != ' ' && buf->peek() != '\n') {
        buf->clear();
        throw not_integer_exception();
    }
    return res;
}
int MainWindow::readNum(stringstream *buf){
    int res = readInt(buf);
    if (res >= RANGE || res <= -RANGE) {
        throw over_range_exception();
    }
    return res;
}
int MainWindow::readLine(stringstream *buf){
    int res = readInt(buf);
    if (res < 1) {
        throw not_valid_integer_exception();
    }
    return res;
}
char MainWindow::readGraphType(stringstream *buf){
    char res;
    *buf >> res;
    if (res != 'L' && res != 'R' && res != 'S' && res != 'C') {
        throw undefined_graph_exception();
    }
    return res;
}
