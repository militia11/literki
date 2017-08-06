#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <ctime>
#include <QMovie>
#include <QThread>
#include <QKeyEvent>
#include <QMessageBox>

//#include "windows.h"

//DEVMODE *dm=new DEVMODE();
//EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,dm);
//dm->dmPelsWidth=(unsigned long)800;
//dm->dmPelsHeight=(unsigned long)600;
//ChangeDisplaySettings(dm,CDS_FULLSCREEN);

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		butL(0),
		winMonkeyNeeded(false),
		terazKot(true),
		czybylKacper(false),
		victoryTimcounter(0),
		ktoryBalon(0),
		trafionychLiter(0),
		kliknietoDobrze(0),
		kliknietoWin(0),
		kliknietoZle(0),
		aktualnyTheme(1),
		licznikWygranych(0),
		przybKacper(0),
		licznikKacprowy(0) {
	themes.append ("://wave/theme0.wav");
	themes.append ("://wave/theme1.wav");
	themes.append ("://wave/theme2.wav");
	themes.append ("://wave/theme3.wav");
	muzykaGlowneTheme =  new QSoundEffect();
	muzykaGlowneTheme->setSource (QUrl::fromLocalFile (themes[0]));
	muzykaGlowneTheme->play ();
	ui->setupUi(this);

	labelBal1= new QPushButton(this);
	labelBal1->setIcon (QIcon("://zas/bal.png"));
	labelBal1->setGeometry (1100, 10,221,291);

	labelBal2= new QPushButton(this);
	labelBal2->setIcon (QIcon("://zas/bal15.png"));
	labelBal2->setGeometry (1100, -10,221,291);

	labelBal3= new QPushButton(this);
	labelBal3->setIcon (QIcon("://zas/bal2.png"));
	labelBal3->setGeometry (1120, 10,221,291);

	connect (labelBal1, SIGNAL(clicked(bool)), this, SLOT(yy()));
	connect (labelBal2, SIGNAL(clicked(bool)), this, SLOT(yy()));
	connect (labelBal3, SIGNAL(clicked(bool)), this, SLOT(yy()));
	labelBal1->setIconSize (QSize(200,200));
	labelBal2->setIconSize (QSize(200,200));
	labelBal3->setIconSize (QSize(200,200));
	movieVictory = new QMovie();
	movieVictory->setFileName ("://zas/win.gif");
	movieVictory->start ();
	ui->pushButtonStart->hide ();
	ui->pushButtonStart->hide ();
	ui->as->setGeometry (0, 0 , 1361, 768);
	ui->as->setMovie(movieVictory);
	ui->as->show ();
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
	aktualnyTryb = NONE;
	aktualnyPodpowiadacz = BALOON;


	ui->layout_->addStretch (70);
	ui->layout->addStretch (100);

	ui->pushButton_2->setVisible (false);

	QFont f( "Arial", 126, QFont::Bold);
	ui->label->setStyleSheet("QLabel {color : red; }");
	ui->label->setFont (f);
	ui->label->setVisible (false);
	// balon:
	ui->label_2->hide ();
	labelBal1->setVisible(false);
	labelBal2->setVisible(false);
	labelBal3->setVisible(false);

	// timery:
	timerKacprowy = new QTimer(this);
	connect(timerKacprowy,SIGNAL(timeout()),SLOT(przyblizenieKacpra()));

	timerDolnyRuch = new QTimer(this);
	connect(timerDolnyRuch,SIGNAL(timeout()),SLOT(ruchDolny()));

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
	movieL = new QMovie(":/zas/giphy.gif");
	connect(movieL,SIGNAL(frameChanged(int)),this,SLOT(setButtonIcon(int)));
	movieL->start ();

	inicjalizujIkonyLabely();
	movieBat = new QMovie("://zas/bat.gif");
	connect(movieBat,SIGNAL(frameChanged(int)),this,SLOT(batWprzyciskachMovie(int)));
	movieBatDuzo = new QMovie("://zas/batDuzo.gif");
	movieHeli = new QMovie("://zas/helicopter.gif");
	connect(movieHeli,SIGNAL(frameChanged(int)),this,SLOT(heliWprzyciskachMovie(int)));
	movieVictory2 = new QMovie("://zas/kotka.gif");
	ui->labelAuto->setPixmap (QPixmap("://zas/end.jpg"));
	RozszerzLabelAuto ();
	ui->pushButtonStart->hide ();
	QTimer::singleShot (4500, this, SLOT(koniecZolwia()) );
}

void MainWindow::koniecZolwia() {
	ui->pushButtonStart->show ();
	ui->labelAuto->setVisible(false);
	movieVictory->stop ();
	ui->as->setGeometry (0, 0 , 1, 1);
	ZmniejszLabelAuto ();
}

void MainWindow::uzupelnijPrzyciskiLiterami() {
	for(int i=0; i<4;i++) {
		przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->
		setToolTip (literyMarki.at (i));
		przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->setVisible (true);
		przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->
			setIcon(ikony[literyMarki.at (i)]);

		if(przyciski[wylosowaneLiczbyDoPrzyciskow[i]]->toolTip () == "L") {
			butL = przyciski[wylosowaneLiczbyDoPrzyciskow[i]];
		}
	}
	aktualizujAktywnaLitere();
}

void MainWindow::ustawZdjecieVictoryLubBalonLeci(bool zLotow, bool play) {
	visibleFrameLetterButtonsLetter (false);
	if(licznikWygranych == 2 && !zLotow){
		timerDolnyRuch->start (60);
	} else if(licznikWygranych==3 && !zLotow) {
		timerDolnyRuch->start (70);
	} else {
		if(play) {
			QSound::play (waveWin[kliknietoWin]);
			kliknietoWin++;
			if(kliknietoWin == 3) {
				kliknietoWin = 0;
			}
		}
		visibilityBallonButtons (false);
		RozszerzLabelAuto ();
		ui->labelAuto->show ();
		ui->label_2->hide ();
		timerVictory->start(800);
	}

	if(!zLotow) licznikWygranych++;
}

void MainWindow::victory() {
	timerBalonowy->stop ();
	visibilityBallonButtons (false);
	foreach (QLabel *l, labelyWAucie) {
		l->setVisible (!l->isVisible ());
	}
	if(winMonkeyNeeded) {
		ui->labelWin->setPixmap (QPixmap("://zas/3.png"));
	} else {
		ui->labelWin->setPixmap (QPixmap("://zas/0.png"));
	}

	ui->labelWin->setVisible(!ui->labelWin->isVisible ());
	victoryTimcounter++;
	if (victoryTimcounter == 6) {
		if(winMonkeyNeeded) {
			winMonkeyNeeded = false;
		} else {
			winMonkeyNeeded = true;
		}
		przywrocAuta();
	}
}

void MainWindow::przywrocAuta() {
	movieVictory->setFileName ("://zas/aa.gif");
	movieVictory->start ();
	RozszerzLabelAuto ();
	ui->pushButtonStart->hide ();
	ui->as->setGeometry (0, 0 , 1361, 768);
	ui->as->setMovie(movieVictory);
	ui->as->show ();
	QTimer::singleShot (1700, this, SLOT(koniecEfektuZamazywaniaEkranu()));
}

void MainWindow::sprawdzLitereNaPrzycisku() {
	QPushButton *but = qobject_cast<QPushButton *>(QObject::sender());
	if (but->toolTip () == ui->label->text ()) {

		przeniesLitereDoZdjAuta (but);
		but->hide ();
		trafionychLiter++;

		if (trafionychLiter == 4) {
			timerBalonowy->stop ();
			visibilityBallonButtons (false);

			ui->labelAuto->hide ();
			ustawZdjecieVictoryLubBalonLeci(false, true);
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
		if  (aktualnyTheme==4) {
			aktualnyTheme=0;
		}
	}
}

void MainWindow::przeniesLitereDoZdjAuta(QPushButton *but) {
	labelyWAucie[trafionychLiter]->
		setPixmap (ikony[but->toolTip ()].pixmap (QSize(132, 132)));
	if(but->toolTip () == "L") {
		but->setIcon (QIcon());
		but->setToolTip ("");
		butL = 0;
	}
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

void MainWindow::koniecBatD() {
	ustawZdjecieVictoryLubBalonLeci(true, false);
	visibleFrameLetterButtonsLetter(false);
	QSound::play (waveWin[kliknietoWin]);
	kliknietoWin++;
	if(kliknietoWin == 3) {
		kliknietoWin = 0;
	}
	trafionychLiter = 0;
	timerGornegoLotu->stop();
	movieVictory->stop ();
	ui->label_2->hide ();
	ui->layout->setStretch (0,0);
	ui->layout->setStretch (1,70);
	aktualnyPodpowiadacz = HELI;
	labelBal1->setIconSize (QSize(400, 400));
	labelBal3->setIconSize (QSize(400, 400));
	labelBal2->setIconSize (QSize(400, 400));
	movieBat->stop ();
	czyscLitereL ();
	ui->label_2->setMovie (movieHeli);
	movieHeli->start ();
	movieBatDuzo->stop ();
	ui->as->setGeometry (0,0, 1,1);
	ui->as->hide ();
}

void MainWindow::setButtonIcon(int a) {
	Q_UNUSED(a);
	if(butL != 0) {
		butL->setIcon(QIcon(movieL->currentPixmap()));
	}
}

void MainWindow::wlaczBujanieBalonem() {
	if(!finall){
	timerBalonowy->start(520);
	}
}

MainWindow::~MainWindow() {
	delete labelBal1;
	delete labelBal2;
	delete labelBal3;
	delete muzykaGlowneTheme;
	delete timerDolnyRuch;
	delete timerGornegoLotu;
	delete movieL;
	delete movieVictory;
	delete timerThemeSound;
	delete timerVictory;
	delete timerBalonowy;
	delete ui;
}

void MainWindow::final() {
	movieVictory2->stop ();
}

void MainWindow::batWprzyciskachMovie(int x) {
	Q_UNUSED(x);
	labelBal1->setIcon(QIcon(movieBat->currentPixmap()));
	labelBal2->setIcon(QIcon(movieBat->currentPixmap()));
	labelBal3->setIcon(QIcon(movieBat->currentPixmap()));
}

void MainWindow::heliWprzyciskachMovie(int x) {
	Q_UNUSED(x);
	labelBal1->setIcon(QIcon(movieHeli->currentPixmap()));
	labelBal2->setIcon(QIcon(movieHeli->currentPixmap()));
	labelBal3->setIcon(QIcon(movieHeli->currentPixmap()));
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
	labelBal1->setVisible(true);
	labelBal2->setVisible(false);
	labelBal3->setVisible(false);
	ktoryBalon = 1;
}

void MainWindow::pokazBalon2() {
	labelBal1->setVisible(false);
	labelBal2->setVisible(true);
	labelBal3->setVisible(false);
	ktoryBalon = 2;
}

void MainWindow::pokazBalon3() {
	labelBal1->setVisible(false);
	labelBal2->setVisible(false);
	labelBal3->setVisible(true);
	ktoryBalon = 0;
}

void MainWindow::on_pushButton_2_clicked() {
	muzykaGlowneTheme->setSource (QUrl::fromLocalFile (themes[aktualnyTheme]));
	muzykaGlowneTheme->play ();
	aktualnyTheme++;
	if  (aktualnyTheme==3) {
		aktualnyTheme=0;
	}
}

void MainWindow::yy()
{
	timerBalonowy->stop ();
	visibilityBallonButtons (false);
	timerGornegoLotu->start (60);
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
	ui->pushButtonStart->hide ();
	ui->labelAuto->setMovie(movieVictory);
	ui->labelAuto->show ();
	movieVictory->start ();
}


void MainWindow::koniecfajerwerka2() {
	movieVictory->stop ();
	ZmniejszLabelAuto ();
	ui->labelBabcia->hide ();ui->cat->hide ();
	ActivateGame ();
}

void MainWindow::koniecfajerwerka() {
	movieVictory->stop ();
	ZmniejszLabelAuto ();
	ActivateGame ();
}

void MainWindow::koniecfajerwerkaK() {
	visibilityBallonButtons (true);
	movieVictory->stop ();
	ZmniejszLabelAuto ();
	ActivateGame ();
}

void MainWindow::koniecEfektuZamazywaniaEkranu() {
	movieVictory->stop ();
	timerVictory->stop ();
	ui->labelWin->hide ();
	wlaczBujanieBalonem ();
	ZmniejszLabelAuto ();
	victoryTimcounter = 0;
	ui->as->setGeometry (0,0, 1,1);
	ui->as->hide ();
	ui->labelAuto->setVisible (true);
	visibleFrameLetterButtonsLetter (true);
	foreach (QLabel*l, labelyWAucie) {
		l->setVisible (true);
		l->clear ();
	}
	odkryjNaNowoPrzyciskiZPoszukiwanych();
	ustawNastepneAuto ();
}

void MainWindow::ruchDolny() {
	if (terazKot) {
		if(!czybylKacper) {
			// kot
			ui->layout_->setStretch(0, ui->layout_->stretch(0) + 1);
			ui->layout_->setStretch(1, ui->layout_->stretch(1) - 1);
			if(ui->layout_->stretch(0) == 88){
				// kacper
				ui->pushButtonStart->setGeometry (0, 0 , 1361, 768);
				ui->pushButtonStart->setIcon (QIcon("://zas/2.png"));
				ui->pushButtonStart->show ();
				ui->pushButtonStart->setStyleSheet ("QPushButton{background: transparent;}");
				timerKacprowy->start (40);
				timerDolnyRuch->stop();
				ui->cat->hide ();
				terazKot = false;
				ui->layout_->setStretch (0,0);
				ui->layout_->setStretch (1,70);
				ui->cat->setPixmap (QPixmap("://zas/4.png"));
				ui->cat->setScaledContents (false);
				czybylKacper = true;
				foreach (QPushButton*b, przyciski) {
					b->setEnabled (true);
				}
			}
		} else {
				// kot finał KOTKA
				ui->layout_->setStretch(0, ui->layout_->stretch(0) + 1);
				ui->layout_->setStretch(1, ui->layout_->stretch(1) - 1);
				if(ui->layout_->stretch(0) == 2) {
					timerBalonowy->stop ();
					movieVictory->setFileName ("://zas/giphy2.gif");
					RozszerzLabelAuto ();
					ui->labelAuto->setMovie (movieVictory);
					ui->labelAuto->show ();
					movieVictory->start ();
					visibleFrameLetterButtonsLetter(false);
					visibilityBallonButtons (false);
					ui->labelBabcia->setMovie(movieVictory2);
					movieVictory2->start ();
					ui->label1->setPixmap (QPixmap());
					ui->label2->setPixmap (QPixmap());
					ui->label3->setPixmap (QPixmap());
					ui->label4->setPixmap (QPixmap());
					QTimer::singleShot(8500, this, SLOT(final()));
				}
				if(ui->layout_->stretch(0) == 118) {
					timerDolnyRuch->stop();
					movieVictory->stop ();
					movieVictory->setFileName ("://zas/kromki.gif");
					movieVictory->start ();
					ui->labelAuto->setMovie (movieVictory);

					QTimer::singleShot(3000, this, SLOT(koniecfajerwerka2()));
					wlaczBujanieBalonem ();
				}
		}
	} else {
			// hamster
		visibilityLiteryWAucie(false);
			ui->layout_->setStretch(0, ui->layout_->stretch(0) + 1);
			ui->layout_->setStretch(1, ui->layout_->stretch(1) - 1);
			if(ui->layout_->stretch(0) == 4 ) {
				visibleFrameLetterButtonsLetter(false);
				RozszerzLabelAuto ();
				ui->labelAuto->setMovie (movieVictory);
				movieVictory->setFileName ("://zas/win.gif");
				movieVictory->start ();
				ui->labelAuto->show ();
				timerBalonowy->stop ();
				visibilityBallonButtons (false);
				QTimer::singleShot(6270, this, SLOT(koniecfajerwerka()));
			}
			if(ui->layout_->stretch(0) == 30) {
				ui->cat->show ();
			}
			if(ui->layout_->stretch(0) == 108) {
				ui->layout_->setStretch (0,0);
				ui->layout_->setStretch (1,100);
				terazKot = true;
				ui->cat->setPixmap (QPixmap("://zas/cat.ico"));
				timerDolnyRuch->stop();
				visibilityLiteryWAucie(true);
				ui->label1->setPixmap (QPixmap());
				ui->label2->setPixmap (QPixmap());
				ui->label3->setPixmap (QPixmap());
				ui->label4->setPixmap (QPixmap());
				wlaczBujanieBalonem ();
			}
	}
}

void MainWindow::ruchGornyLot() {
	ui->label_2->show ();
	switch (aktualnyPodpowiadacz) {
	case BALOON: {
		ui->layout->setStretch(0, ui->layout->stretch(0) + 2);
		ui->layout->setStretch(1,ui->layout->stretch(1) - 2);
		if(ui->layout->stretch(0) == 48){
			labelyWAucie[3]->setPixmap (ikony[literyMarki.at (3)].pixmap (QSize(132, 132)));
		} else if (ui->layout->stretch (0) == 68) {
			labelyWAucie[2]->setPixmap (ikony[literyMarki.at (2)].pixmap (QSize(132, 132)));
		} else if (ui->layout->stretch (0) == 88) {
			labelyWAucie[1]->setPixmap (ikony[literyMarki.at (1)].pixmap (QSize(132, 132)));
		}
		else if (ui->layout->stretch (0) == 98) {
			labelyWAucie[0]->setPixmap (ikony[literyMarki.at (0)].pixmap (QSize(132, 132)));
		} else if(ui->layout->stretch(0) == 146){
			ui->label_2->hide ();
			ustawZdjecieVictoryLubBalonLeci(true, false);
			visibleFrameLetterButtonsLetter(false);
			QSound::play (waveWin[kliknietoWin]);
			kliknietoWin++;
			if(kliknietoWin == 3) {
				kliknietoWin = 0;
			}
			trafionychLiter = 0;
				  timerGornegoLotu->stop();
				  aktualnyPodpowiadacz = BAT;
				  ui->layout->setStretch (0,0);
				  ui->layout->setStretch (1,70);
				  ui->label_2->setMovie (movieBat);
				czyscLitereL ();
				movieBat->start ();
			}
	}
		break;
	case BAT: {
		ui->layout->setStretch(0, ui->layout->stretch(0) + 1);
		ui->layout->setStretch(1, ui->layout->stretch(1) - 1);
		if(ui->layout->stretch(0) == 38){
			labelyWAucie[3]->setPixmap (ikony[literyMarki.at (3)].pixmap (QSize(132, 132)));
		} else if (ui->layout->stretch (0) == 51) {
			labelyWAucie[2]->setPixmap (ikony[literyMarki.at (2)].pixmap (QSize(132, 132)));
		} else if (ui->layout->stretch (0) == 62) {
			labelyWAucie[1]->setPixmap (ikony[literyMarki.at (1)].pixmap (QSize(132, 132)));
		} else if (ui->layout->stretch (0) == 76) {
			labelyWAucie[0]->setPixmap (ikony[literyMarki.at (0)].pixmap (QSize(132, 132)));
		}else if(ui->layout->stretch(0) == 98) {
			ui->label_2->hide ();
			ui->as->setGeometry (0, 0 , 1361, 768);
			ui->as->setMovie(movieBatDuzo);
			ui->as->show ();
			movieBatDuzo->start ();
			QTimer::singleShot (2400, this, SLOT(koniecBatD()));
		}
	}
		break;
	case HELI:
	{
		visibilityBallonButtons (false);
		QSound::play ("://wave/heli.wav");
		timerBalonowy->stop ();
		ui->layout->setStretch(0, ui->layout->stretch(0) + 1);
		ui->layout->setStretch(1, ui->layout->stretch(1) - 1);
		if(ui->layout->stretch(0) == 38){
			labelyWAucie[3]->setPixmap (ikony[literyMarki.at (3)].pixmap (QSize(132, 132)));
		} else if (ui->layout->stretch (0) == 51) {
			labelyWAucie[2]->setPixmap (ikony[literyMarki.at (2)].pixmap (QSize(132, 132)));
		} else if (ui->layout->stretch (0) == 62) {
			labelyWAucie[1]->setPixmap (ikony[literyMarki.at (1)].pixmap (QSize(132, 132)));

		} else if (ui->layout->stretch (0) == 76) {
			labelyWAucie[0]->setPixmap (ikony[literyMarki.at (0)].pixmap (QSize(132, 132)));
		}else if(ui->layout->stretch(0) == 98) {
			ui->label_2->hide ();
			ustawZdjecieVictoryLubBalonLeci (true, false);
			visibleFrameLetterButtonsLetter(false);
			QSound::play (waveWin[kliknietoWin]);
			kliknietoWin++;
			if(kliknietoWin == 3) {
				kliknietoWin = 0;
			}
			trafionychLiter = 0;
			timerGornegoLotu->stop();
			aktualnyPodpowiadacz = NO;
			movieHeli->stop ();
			finall =true;
			czyscLitereL ();
		}
	}
		break;
	case NO:
		ui->label_2->hide ();
		break;
	}
}

void MainWindow::keyPressEvent(QKeyEvent *aEvent) {
	if(aEvent->key() == Qt::Key_Escape) {
		if(QMessageBox::question(this, tr("Literki"),
			tr("Czy chcesz opuścić aplikację?"),
				QMessageBox::Yes |QMessageBox::No) == QMessageBox::Yes) {
			exit (1);
		}
	}
}

void MainWindow::visibilityLiteryWAucie(bool v)
{
	foreach (QLabel*l, labelyWAucie) {
		l->setVisible (v);
	}
}

void MainWindow::czyscLitereL() {
	foreach (QPushButton *but, przyciski) {
		if(but->toolTip ()== "L") {
			if(but->toolTip () == "L") {
				but->setIcon (QIcon());
				but->setToolTip ("");
				butL = 0;
			}
		}
	}
}

void MainWindow::przyblizenieKacpra() {
	przybKacper +=15;
	ui->pushButtonStart->setIconSize (QSize(przybKacper, przybKacper));
	if (przybKacper > 900) {
		if (przybKacper%10) {
			licznikKacprowy++;
		}
		ui->pushButtonStart->setVisible(!ui->pushButtonStart->isVisible ());
		if (licznikKacprowy == 25) {
			timerKacprowy->stop ();
			movieVictory->setFileName ("://zas/fireworks.gif");
			Fajerwerki();
			QTimer::singleShot(1900, this, SLOT(koniecfajerwerkaK()));
		}
	}
}

void MainWindow::on_pushButtonStart_clicked() {
	QSound::play ("://wave/start.wav");
	timerDolnyRuch->start (60);
}

void MainWindow::visibilityBallonButtons(bool a) {
	labelBal1->setVisible (a);
	labelBal2->setVisible (a);
	labelBal3->setVisible (a);
}

void MainWindow::visibleFrameLetterButtonsLetter(bool visible) {
	ui->label->setVisible (visible);
	ui->pushButton_2->setVisible (visible);
	foreach (QPushButton*b, przyciski) {
		b->setVisible (visible);
	}
}

void MainWindow::RozszerzLabelAuto() {
	ui->labelAuto->setGeometry (0, 0 , 1361, 768);
	ui->labelAuto->setFrameStyle (0);
}

void MainWindow::ZmniejszLabelAuto() {
	ui->labelAuto->setGeometry (230, 70 , 841, 461);
	ui->labelAuto->setFrameStyle (33);
}
