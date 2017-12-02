#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include <QMenuBar>
#include<QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMainWindow>
#include<QProcess>
namespace Ui {
class frmMain;
}

class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btnMenu_Close_clicked();

    void on_btnMenu_Max_clicked();

    void on_btnMenu_Min_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void Ttftpopen();
    void Pingopen();
    void Rebootopen();
    void Aboutopen();

   void on_btnping_clicked();

private:
    Ui::frmMain *ui;

    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;
    QSerialPort *myCOM;
   QMenuBar * menuBar ;
    QMenu *Tool;
    QMenu *HELP;
    QAction* Ttftp;
    QAction* Ping;
    QAction* Reboot;
    QAction* About;
    QProcess *Process;


    void InitStyle();

};

#endif // FRMMAIN_H
