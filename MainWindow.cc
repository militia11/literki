#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <ctime>
#include <QMovie>
#include <QThread>
MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		victoryTimcounter(0),
		ktoryBalon(0),
		trafionychLiter(0),
		kliknietoDobrze(0),
		kliknietoWin(0),
		kliknietoZle(0),
		aktualnyTheme(1),
		licznikWygranych(0),
		przybKacper(0),
		licznikKacprowy(0){
	themes.append ("://wave/theme0.wav");
	themes.append ("://wave/theme1.wav");
	themes.append ("://wave/theme2.wav");
	muzykaGlowneTheme =  new QSoundEffect();
	muzykaGlowneTheme->setSource (QUrl::fromLocalFile (themes[0]));
//	muzykaGlowneTheme->play ();
	ui->setupUi(this);
	ui->labelWin->hide ();
	srand(time(0));
	waveOk.append ("://wave/z0.wav");
	waveOk.append ("://wave/z1.wav");
	waveOk.append ("://wave/z2.wav");
	waveWrong.append ("://wave/zle0.wav");
	waveWrong.append ("://wave/zle1.wav");
	waveWrong.append ("://wave/zle2.wav");
	waveWin.append ("://wave/win0.wav");
	waveWin.append ("://wave/win1.wav");
	waveWin.append ("://wave/win2.wav");
	ui->labelWin->setAlignment (Qt::AlignCenter);
	aktualnyTryb = NONE;

	ui->layout_->addStretch (70);
	ui->layout->addStretch (100);

	ui->pushButton_2->setVisible (false);
	ui->pushButton->setFocus ();

	QFont f( "Arial", 126, QFont::Bold);
	ui->label->setStyleSheet("QLabel {color : red; }");
	ui->label->setFont (f);
	ui->label->setVisible (false);

	ui->labelAuto->setVisible(false);

	// balon:
	ui->label_2->hide ();
	ui->labelBal1->setVisible(false);
	ui->labelBal2->setVisible(false);
	ui->labelBal3->setVisible(false);

	// timery:
	timerKacprowy = new QTimer(this);
	connect(timerKacprowy,SIGNAL(timeout()),SLOT(przyblizenieKacpra()));

	timerKot = new QTimer(this);
	connect(timerKot,SIGNAL(timeout()),SLOT(ruchKota()));
	timerGornegoLotu = new QTimer(this);
	connect(timerGornegoLotu,SIGNAL(timeout()),SLOT(ruchGornyLot()));

	timerThemeSound= new QTimer(this);
	connect(timerThemeSound, SIGNAL(timeout()), this, SLOT(checksound()));
	timerThemeSound->start (1000);

	timerBalonowy = new QTimer(this);
	connect(timerBalonowy, SIGNAL(timeout()), this, SLOT(bujajBalonem()));

	timerVictory = new QTimer(this);
	connect(timerVictory, SIGNAL(timeout()), this, SLOT(victory()));

	// gify
	movieVictory = new QMovie();
	movieL = new QMovie(":/zas/giphy.gif");
//	connect(movie,SIGNAL(frameChanged(int)),this,SLOT(setButtonIcon(int)));
	inicjalizujIkonyLabely();

	//ui->labelBabcia->hide ();

	// przejsciowe !!!!!!!!!!!!!!!!!!!
//	ui->pushButtonStart->hide ();
//	ActivateGame ();
}

void MainWindow::uzupelnijPrzyciskiLiterami() {
	for(int i=0; i<4;i++) {
			przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->
				setIcon(ikony[literyMarki.at (i)]);
			przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->
				setToolTip (literyMarki.at (i));
			przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->setVisible (true);
	}
	aktualizujAktywnaLitere();
}

void MainWindow::ustawZdjecieVictoryLubBalonLeci() {
	qDebug() <<licznikWygranych;
	licznikWygranych++;
	if(licznikWygranych==8){
		//balon
	} else if(licznikWygranych==12) {
		//nietoperz
	} else {
		RozszerzLabelAuto ();
		ui->labelAuto->show ();
		timerVictory->start(800);
	}
}

void MainWindow::victory() {
	foreach (QLabel *l, labelyWAucie) {
		l->setVisible (!l->isVisible ());
	}
	timerBalonowy->stop ();
	visibleBaloonAndFrameLetter (false);
	ui->labelWin->setVisible(!ui->labelWin->isVisible ());
	victoryTimcounter++;
	if (victoryTimcounter == 6) {
		przywrocAuta();
		ui->labelWin->hide ();
	}

//	if(licznikWygranych==6) {
//		timerGornegoLotu->start (75);
//		victoryTimcounter++;
//		if (victoryTimcounter == 4) {
//			przywrocAuta();
//			return;
//		}
//	}
}

void MainWindow::przywrocAuta() {
	timerBalonowy->start();
	timerVictory->stop ();
	ZmniejszLabelAuto ();
	victoryTimcounter =0;
	ui->labelAuto->setVisible (true);
	visibleBaloonAndFrameLetter (true);
	foreach (QLabel*l, labelyWAucie) {
		l->setVisible (true);
		l->clear ();
	}
	odkryjNaNowoPrzyciskiZPoszukiwanych();
	ustawNastepneAuto ();
}

void MainWindow::sprawdzLitereNaPrzycisku() {
	QPushButton *but = qobject_cast<QPushButton *>(QObject::sender());
	if (but->toolTip () == ui->label->text ()) {

		przeniesLitereDoZdjAuta (but);
		but->hide ();
		trafionychLiter++;

		if (trafionychLiter == 4) {
			QSound::play (waveWin[kliknietoWin]);
			kliknietoWin++;
			if(kliknietoWin == 3) {
				kliknietoWin = 0;
			}
			ui->labelAuto->hide ();
			ustawZdjecieVictoryLubBalonLeci();
			trafionychLiter = 0;
		} else {
			QSound::play (waveOk[kliknietoDobrze]);
			kliknietoDobrze++;
			if(kliknietoDobrze == 3) {
				kliknietoDobrze=0;
			}
			aktualizujAktywnaLitere();
		}
	} else if (but->toolTip () == "") {}
		else {
		QSound::play (waveWrong[kliknietoZle]);
		kliknietoZle++;
		if(kliknietoZle == 3) {
			kliknietoZle =0;
		}
	}
}

void MainWindow::checksound() {
	if(!muzykaGlowneTheme->isPlaying ()) {
		muzykaGlowneTheme->setSource (QUrl::fromLocalFile (themes[aktualnyTheme]));
		muzykaGlowneTheme->play ();
		aktualnyTheme++;
		if  (aktualnyTheme==3) {
			aktualnyTheme=0;
		}
	}
}

void MainWindow::przeniesLitereDoZdjAuta(QPushButton *but) {
	labelyWAucie[trafionychLiter]->
		setPixmap (ikony[but->toolTip ()].pixmap (QSize(132, 132)));
}

void MainWindow::ustawLiteryWPrzyciskach() {
	wylosuj4Liczby ();
	switch (aktualnyTryb) {
		case AUDI:
			wyswietlLiteryDlaAudi();
			break;
		case FIAT:
			wyswietlLiteryDlaFiat ();
			break;
		case FORD:
			wyswietlLiteryDlaFord ();
			break;
		case OPEL:
			wyswietlLiteryDlaOpel ();
			break;
		case NONE:
			break;
	}
}

void MainWindow::aktualizujAktywnaLitere() {
	QString letter = literyMarki.at (trafionychLiter);
	ui->label->setText (letter);
}

int MainWindow::pobierzIdNastepnegoAuta() {
	int vtryb = 0;
	do {
		vtryb = wylosuj (4);
	} while (vtryb == static_cast<int>(aktualnyTryb));
	aktualnyTryb = static_cast<tryb>(vtryb);
	return wylosuj (4);
}


void MainWindow::odkryjNaNowoPrzyciskiZPoszukiwanych() {
	for (int i=0; i<4;i++) {
		przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->setVisible (true);
	}
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

void MainWindow::inicjalizujIkonyLabely() {
	labelyWAucie.append (ui->label1);
	labelyWAucie.append (ui->label2);
	labelyWAucie.append (ui->label3);
	labelyWAucie.append (ui->label4);
	QIcon a("://zas/a_trans.png");
	QIcon u("://zas/U.png");
	QIcon d("://zas/D.png");
	QIcon i("://zas/i_trans.png");
	ikony["A"] = a;
	ikony.insert ("U", u);
	ikony["D"] = d;
	ikony.insert ("I", i );

	QIcon ff("://zas/F.png");
	QIcon o("://zas/Oo.png");
	QIcon r("://zas/R.png");
	ikony.insert ("F", ff);
	ikony["O"] = o;
	ikony.insert ("R", r );

	QIcon p("://zas/p_trans.png");
	ikony.insert ("P", p);
	QIcon e("://zas/EE.png");
	ikony["E"] = e;
	QIcon ll("://zas/giphy.gif");
	ikony["L"]= ll;
	QIcon t("://zas/t.png");
	ikony["T"] = t;
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

	for (int i = 0; i < 15;i++) {
		connect(
			przyciski.at (i),
			SIGNAL(clicked()),
			SLOT(sprawdzLitereNaPrzycisku()));
	}
}

void MainWindow::ustawNastepneAuto() {
	int id = pobierzIdNastepnegoAuta ();
	QString path = ":/auta/";
	path+= slownikTrybow[aktualnyTryb];
	ustawLiteryWPrzyciskach();
	path+=QString::number(id);
	path+=".jpg";
	ui->labelAuto->setPixmap(QPixmap(path));
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

void MainWindow::setButtonIcon(int a) {
	//przyciski[wylosowaneLiczbyDoPrzyciskow[yy]]->setIcon(QIcon(movie->currentPixmap()));
}

void MainWindow::wlaczBujanieBalonem() {
	timerBalonowy->start(520);
}

MainWindow::~MainWindow() {
	delete muzykaGlowneTheme;
	delete timerKot;
	delete timerGornegoLotu;
	delete movieL;
	delete movieVictory;
	delete timerThemeSound;
	delete timerVictory;
	delete timerBalonowy;
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
		if( czyBylaWylosowana( liczba, wylosowaneLiczbyDoPrzyciskow, wylosowanych ) == false )
		{
			wylosowaneLiczbyDoPrzyciskow[ wylosowanych ] = liczba;
			wylosowanych++;
		}
	} while( wylosowanych < 4);
}

void MainWindow::wyswietlLiteryDlaAudi() {
	literyMarki.clear ();
	literyMarki.append ("A");
	literyMarki.append ("U");
	literyMarki.append ("D");
	literyMarki.append ("I");
	uzupelnijPrzyciskiLiterami ();
}

void MainWindow::wyswietlLiteryDlaFiat() {
	literyMarki.clear ();
	literyMarki.append ("F");
	literyMarki.append ("I");
	literyMarki.append ("A");
	literyMarki.append ("T");
	uzupelnijPrzyciskiLiterami ();
}

void MainWindow::wyswietlLiteryDlaFord() {
	literyMarki.clear ();
	literyMarki.append ("F");
	literyMarki.append ("O");
	literyMarki.append ("R");
	literyMarki.append ("D");
	uzupelnijPrzyciskiLiterami ();
}

void MainWindow::wyswietlLiteryDlaOpel() {
	literyMarki.clear ();
	literyMarki.append ("O");
	literyMarki.append ("P");
	literyMarki.append ("E");
	literyMarki.append ("L");
	uzupelnijPrzyciskiLiterami ();
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

void MainWindow::on_pushButton_2_clicked()
{
	muzykaGlowneTheme->setSource (QUrl::fromLocalFile (themes[aktualnyTheme]));
	muzykaGlowneTheme->play ();
	aktualnyTheme++;
	if  (aktualnyTheme==3) {
		aktualnyTheme=0;
	}
}

void MainWindow::ActivateGame(){
	ui->pushButtonStart->hide ();
	ui->labelAuto->show ();
	ui->label->setVisible (true);
	ui->pushButton_2->setVisible (true);
	wlaczBujanieBalonem();
	ustawNastepneAuto ();
}

void MainWindow::Fajerwerki() {
	RozszerzLabelAuto ();
	movieVictory->setFileName ("://zas/fireworks.gif");
	ui->pushButtonStart->hide ();
	ui->labelAuto->setMovie(movieVictory);
	ui->labelAuto->show ();
	movieVictory->start ();
	QTimer::singleShot(1900, this, SLOT(koniecfajerwerka()));
}

void MainWindow::koniecfajerwerka() {
	movieVictory->stop ();
	ZmniejszLabelAuto ();
	ActivateGame ();
}

void MainWindow::ruchKota() {
	ui->layout_->setStretch(0, ui->layout_->stretch(0) + 1);
	ui->layout_->setStretch(1, ui->layout_->stretch(1) - 1);
	if(ui->layout_->stretch(0) == 88){
		// kacper
		ui->pushButtonStart->setGeometry (0, 0 , 1361, 768);
		ui->pushButtonStart->setIcon (QIcon("://zas/2.png"));
		ui->pushButtonStart->show ();
		ui->pushButtonStart->setStyleSheet ("QPushButton{background: transparent;}");
		timerKacprowy->start (40);
		timerKot->stop();
		ui->cat->hide ();
	}
	//	if(ui->layout_->stretch(0) == 130){
	//		movieVictory->stop ();
	//		ui->labelBabcia->hide ();
}

void MainWindow::ruchGornyLot() {
	ui->label_2->show ();
	ui->layout->setStretch(0, ui->layout->stretch(0) + 1);
	ui->layout->setStretch(1, ui->layout->stretch(1) - 1);
	if(ui->layout->stretch(0) == 120){
		  timerGornegoLotu->stop();
		  ui->label_2->hide ();
	}
}

void MainWindow::przyblizenieKacpra() {
	przybKacper +=15;
	qDebug() << przybKacper;
	ui->pushButtonStart->setIconSize (QSize(przybKacper, przybKacper));
	if (przybKacper > 900) {
		if (przybKacper%10) {
			licznikKacprowy++;
		}
		ui->pushButtonStart->setVisible(!ui->pushButtonStart->isVisible ());
		if (licznikKacprowy == 25) {
			timerKacprowy->stop ();
			Fajerwerki();
		}
	}
}

void MainWindow::on_pushButton_3_clicked() {
	movieVictory->setFileName ("://zas/kotka.gif");//://zas/babcia.gif
	ui->labelAuto->hide ();
	ui->labelBabcia->setMovie(movieVictory);
	movieVictory->start ();
	timerKot->start (70);
	ui->pushButtonStart->show ();
	//timerGornegoLotu->start (170);

}

void MainWindow::on_pushButtonStart_clicked() {
	Fajerwerki ();
//	timerKot->start (70);
}

void MainWindow::on_pushButton_4_clicked() {
	//ui->labelAuto->setScaledContents (false);
	//ui->labelAuto->setAlignment(Qt::AlignCenter);

//	ui->labelAuto->setPixmap (QPixmap("://zas/2.png"));
//	ui->labelAuto->setScaledContents (false);
//	ui->labelAuto->setAlignment(Qt::AlignCenter);
	//	ui->labelBabcia->hide ();
}

void MainWindow::visibleBaloonAndFrameLetter(bool visible) {
	ui->labelBal1->setVisible (visible);
	ui->labelBal2->setVisible (visible);
	ui->labelBal3->setVisible (visible);
	ui->label->setVisible (visible);
}

void MainWindow::RozszerzLabelAuto() {
	ui->labelAuto->setGeometry (0, 0 , 1361, 768);
	ui->labelAuto->setFrameStyle (0);
}

void MainWindow::ZmniejszLabelAuto() {
	ui->labelAuto->setGeometry (230, 70 , 841, 461);
	ui->labelAuto->setFrameStyle (33);
}
