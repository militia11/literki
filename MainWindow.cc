#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		ktoryBalon(0) {
	ui->setupUi(this);
	srand(time(0));
	aktualnyTryb = NONE;
	QFont f( "Arial", 106, QFont::Bold);
	ui->label->setStyleSheet("QLabel {color : red; }");
	ui->label->setFont (f);
	ui->labelAuto->setVisible(false);
	ui->pushButton->setFocus ();
	ui->labelBal1->setVisible(false);
	ui->labelBal2->setVisible(false);
	ui->labelBal3->setVisible(false);
	timerBalonowy = new QTimer(this);
	connect(timerBalonowy, SIGNAL(timeout()), this, SLOT(bujajBalonem()));

	QIcon a("://zas/a_trans.png");
	QIcon u("://zas/U.png");
	QIcon d("://zas/D.png");
	QIcon i("://zas/i_trans.png");
	ikony["A"] = a;
	ikony.insert ("U", u);
	ikony["D"] = d;
	ikony.insert ("I", i );

	slownikTrybow[AUDI] = "audi";
	slownikTrybow[FORD] = "ford";
	slownikTrybow[FIAT] = "fiat";
	slownikTrybow[OPEL] = "opel";

	przyciski.append (ui->pushButton0);
	przyciski.append (ui->pushButton1);
	przyciski.append (ui->pushButton2);
	przyciski.append (ui->pushButton3);
	przyciski.append (ui->pushButton4);
	przyciski.append (ui->pushButton5);
	przyciski.append (ui->pushButton6);
	przyciski.append (ui->pushButton7);
	przyciski.append (ui->pushButton8);
	przyciski.append (ui->pushButton9);
	przyciski.append (ui->pushButton10);
	przyciski.append (ui->pushButton11);
	przyciski.append (ui->pushButton12);
	przyciski.append (ui->pushButton13);
	przyciski.append (ui->pushButton14);

	pobierzIdNastepnegoAuta ();
}

void MainWindow::trybAudi() {
	wylosuj4Liczby ();
	przyciski[wylosowaneLivzbyDoPrzyciskow[0]]->setIcon (ikony["A"]);
	przyciski[wylosowaneLivzbyDoPrzyciskow[1]]->setIcon (ikony["U"]);
	przyciski[wylosowaneLivzbyDoPrzyciskow[2]]->setIcon (ikony["D"]);
	przyciski[wylosowaneLivzbyDoPrzyciskow[3]]->setIcon (ikony["I"]);

	//	ui->pushButtonA->setIcon (ikony["A"]);
//	ui->pushButtonA->setToolTip ("A");

//	if (ui->pushButtonA->toolTip () == QString("A")) {
//		exit(1);
		//ui->pushButtonA->setToolTip ("");
//	}
}

int MainWindow::pobierzIdNastepnegoAuta() {
	int vtryb = 0;
	do {
		vtryb = wylosuj (4);
	} while (vtryb == static_cast<int>(aktualnyTryb));
	aktualnyTryb = static_cast<tryb>(vtryb);
	return wylosuj (4);
}

void MainWindow::on_pushButtonStart_clicked() {
	ui->pushButtonStart->hide ();
	ui->labelAuto->show ();
	wlaczBujanieBalonem();
	ustawNastepneAuto ();
}

void MainWindow::on_labelBal3_clicked() {
	exit(1);
}

void MainWindow::on_labelBal1_clicked()
{
	exit(1);
}

void MainWindow::on_labelBal2_clicked()
{
	exit(1);
}

void MainWindow::ustawNastepneAuto() {
	int id = pobierzIdNastepnegoAuta ();
	QString path = ":/auta/";
	path+= slownikTrybow[aktualnyTryb];
	qDebug() << aktualnyTryb << slownikTrybow[aktualnyTryb];
	path+=QString::number(id);
	path+=".jpg";
	ui->labelAuto->setPixmap(QPixmap(path));
	qDebug() << path;
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

MainWindow::~MainWindow() {
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

bool MainWindow::czyBylaWylosowana( int iLiczba, int tab[], int ile ) {
	if( ile <= 0 ) return false;
	int i = 0;

	do {
		if( tab[ i ] == iLiczba ) return true;
		i++;
	} while( i < ile );

	return false;
}

int MainWindow::wylosuj(int zIlu) {
	return( rand() % zIlu );
}

void MainWindow::wylosuj4Liczby() {
		int wylosowanych = 0;
	do {
		int liczba = wylosuj(15);
		if( czyBylaWylosowana( liczba, wylosowaneLivzbyDoPrzyciskow, wylosowanych ) == false )
		{
			wylosowaneLivzbyDoPrzyciskow[ wylosowanych ] = liczba;
			wylosowanych++;
		}
	} while( wylosowanych < 4);
}

void MainWindow::pokazBalon1() {
	ui->labelBal1->setVisible(true);
	ui->labelBal2->setVisible(false);
	ui->labelBal3->setVisible(false);
	ktoryBalon = 1;
}

void MainWindow::pokazBalon2() {
	ui->labelBal1->setVisible(false);
	ui->labelBal2->setVisible(true);
	ui->labelBal3->setVisible(false);
	ktoryBalon = 2;
}

void MainWindow::pokazBalon3() {
	ui->labelBal1->setVisible(false);
	ui->labelBal2->setVisible(false);
	ui->labelBal3->setVisible(true);
	ktoryBalon = 0;
}
