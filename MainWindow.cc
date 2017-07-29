#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		ktoryBalon(0) {
	ui->setupUi(this);
	ui->labelAuto->show ();
	ui->pushButton->setFocus ();
	ui->labelBal1->hide ();
	ui->labelBal2->hide ();
	ui->labelBal3->hide ();
	timerBalonowy = new QTimer(this);
	connect(timerBalonowy, SIGNAL(timeout()), this, SLOT(bujajBalonem()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *evt) {
	QPixmap bkgnd(":/auta/tlo.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	QMainWindow::resizeEvent(evt);
}

void MainWindow::on_pushButtonStart_clicked() {
	ui->pushButtonStart->hide ();
	ui->labelAuto->show ();
	wlaczBujanieBalonem();
}

void MainWindow::bujajBalonem() {
	switch (ktoryBalon) {
	case 0:
		pokazBalon1 ();
		break;
	case 1:
		pokazBalon2 ();
		break;
	case 2:
		pokazBalon3 ();
		break;
	}
}

void MainWindow::wlaczBujanieBalonem() {
	timerBalonowy->start(520);
}

void MainWindow::pokazBalon1() {
	ui->labelBal1->show ();
	ui->labelBal2->hide ();
	ui->labelBal3->hide ();
	ktoryBalon = 1;
}

void MainWindow::pokazBalon2() {
	ui->labelBal1->hide ();
	ui->labelBal2->show ();
	ui->labelBal3->hide ();
	ktoryBalon = 2;
}

void MainWindow::pokazBalon3() {
	ui->labelBal1->hide ();
	ui->labelBal2->hide ();
	ui->labelBal3->show ();
	ktoryBalon = 0;
}
