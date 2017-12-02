#include "frmmain.h"
#include "ui_frmmain.h"
#include "iconhelper.h"
#include "myhelper.h"
#include <QTextCodec>
frmMain::frmMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    myHelper::FormInCenter(this);
    this->InitStyle();
}

frmMain::~frmMain()
{
    Process->close();
    delete ui;
}

void frmMain::InitStyle()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    location = this->geometry();
    max = false;
    mousePressed = false;
     Process =new QProcess;
    //安装事件监听器,让标题栏识别鼠标双击
    ui->lab_Title->installEventFilter(this);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
    myCOM = new QSerialPort();
    Tool=new QMenu("Tool");
    HELP=new QMenu("Help");
    menuBar = new QMenuBar(this);
    menuBar->addMenu(Tool);
    menuBar->addMenu(HELP);
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        myCOM->setPort(info);
        if(myCOM->open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(myCOM->portName());
               myCOM->close();

        }
   }
    Ttftp = Tool->addAction(tr("&Ttftp"));
    Ping = Tool->addAction(tr("&Ping"));
    Reboot = Tool->addAction(tr("&Reboot"));
    About = HELP->addAction(tr("&About"));
    ui->horizontalLayout_5->addWidget(menuBar);
    ui->groupBox->hide();

    connect(Ttftp, SIGNAL(triggered()), this, SLOT(Ttftpopen()));
    connect(Ping, SIGNAL(triggered()), this, SLOT(Pingopen()));
    connect(Reboot, SIGNAL(triggered()), this, SLOT(Rebootopen()));
    connect(About, SIGNAL(triggered()), this, SLOT(Aboutopen()));

}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void frmMain::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmMain::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmMain::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void frmMain::on_btnMenu_Close_clicked()
{
    qApp->exit();
}

void frmMain::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
        ui->btnMenu_Max->setToolTip("最大化");
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf079), 10);
        ui->btnMenu_Max->setToolTip("还原");
    }
    max = !max;
}

void frmMain::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void frmMain::on_pushButton_clicked()
{
    myHelper::ShowMessageBoxInfo("恭喜你获得我公司送出的1000万元大礼一份!");
}

void frmMain::on_pushButton_2_clicked()
{
    int result = myHelper::ShowMessageBoxQuesion("确定真的不要我了吗?");
    if (result == 1) {
        myHelper::ShowMessageBoxInfo("你好狠心啊!");
    } else {
        myHelper::ShowMessageBoxInfo("亲爱的,我就知道你不会离开我的!");
    }
}

void frmMain::on_pushButton_3_clicked()
{
    myHelper::ShowMessageBoxError("天空飘来五个字!");
}
void frmMain:: Ttftpopen(){

     Process->start("tftpd32.exe");


}
void frmMain::Aboutopen(){

    myHelper::ShowMessageBoxInfo("UART V 1.1.1");
}
void frmMain:: Pingopen(){

    ui->groupBox->show();
    QString strArg="ping 192.168.1.24 -n 1";
    QProcess Processping;
    Processping.start(strArg );
    Processping.waitForFinished(-1);
    QTextCodec *codec = QTextCodec::codecForName("GBK");
     qDebug()<<"dadadad=";
     QString  outstr=codec->toUnicode(Processping.readAll());
     if((-1 !=outstr.indexOf("往返行程的估计时间")))
           {
               qDebug("在线\n");
           }else
           {
               qDebug("离线\n");

           }


}

void frmMain:: Rebootopen(){


}


void frmMain::on_btnping_clicked()
{
    static int flag;
    if(flag == 0)
    {

        ui->btnping->setText("Stop");
       flag=1;

    }
    else
    {
        flag=0;
        ui->btnping->setText("Start");
        ui->groupBox->hide();
    }
}
