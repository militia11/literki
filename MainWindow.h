#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QMap>
#include <QHash>
#include <cstdlib>           //rand()
#include <QLabel>
#include <QSound>
#include <QSoundEffect>

namespace Ui {
class MainWindow;
}
enum tryb {
	NONE = -1,
	AUDI,
	FORD,
	FIAT,
	OPEL
};

 enum podpowiadacz {
	 NO,
	 BALOON,
	 BAT,
	 HELI,
 };

class MainWindow : public QMainWindow{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void koniecZolwia();
		void final();
		void batWprzyciskachMovie(int x);
		void heliWprzyciskachMovie(int x);
		void on_pushButtonStart_clicked();
		void sprawdzLitereNaPrzycisku();

		void ruchDolny();
		void ruchGornyLot();
		void przyblizenieKacpra();
		void koniecfajerwerka();
		void koniecfajerwerkaK();
		void koniecfajerwerka2();
		void koniecEfektuZamazywaniaEkranu();

		void setButtonIcon(int a);
		void checksound();
		void victory();
		void bujajBalonem();
		void koniecBatD();

		void on_pushButton_2_clicked();
		void yy();

	public:
		void keyPressEvent(QKeyEvent *aEvent);

	private:
		void visibilityLiteryWAucie(bool v);
		QPushButton*bal3;
		void czyscLitereL();
		void ustawLiteryWPrzyciskach();

		void visibilityBallonButtons(bool a);
		void visibleFrameLetterButtonsLetter(bool visible);
		void inicjalizujIkonyLabely();
		void ustawNastepneAuto();
		int pobierzIdNastepnegoAuta();
		void przywrocAuta();
		void ActivateGame();

		void Fajerwerki();
		void odkryjNaNowoPrzyciskiZPoszukiwanych();
		void uzupelnijPrzyciskiLiterami();

		void przeniesLitereDoZdjAuta(QPushButton *but);
		void aktualizujAktywnaLitere();

		void RozszerzLabelAuto();
		void ZmniejszLabelAuto();

		void wyswietlLiteryDlaAudi();
		void wyswietlLiteryDlaFiat();
		void wyswietlLiteryDlaFord();
		void wyswietlLiteryDlaOpel();

		int wylosowaneLiczbyDoPrzyciskow[4];
		bool czyBylaWylosowana( int iLiczba, int tab[], int ile );
		int wylosuj(int zIlu);
		void wylosuj4Liczby();

		void resizeEvent(QResizeEvent *evt);

		void wlaczBujanieBalonem();
		void pokazBalon1();
		void pokazBalon2();
		void pokazBalon3();

		Ui::MainWindow *ui;
		QPushButton *labelBal1;
		QPushButton *labelBal2;
		QPushButton *labelBal3;
		QPushButton *butL;
		bool winMonkeyNeeded;
		bool finall;
		bool terazKot;
		bool czybylKacper;
		int victoryTimcounter;
		int ktoryBalon;
		int trafionychLiter;
		tryb aktualnyTryb;
		podpowiadacz aktualnyPodpowiadacz;

		int kliknietoDobrze;
		int kliknietoWin;
		int kliknietoZle;
		int aktualnyTheme;
		int licznikWygranych;
		int przybKacper;
		int licznikKacprowy;
		QStringList themes;
		QList<QString>waveOk;
		QList<QString>waveWrong;
		QList<QString>waveWin;
		void ustawZdjecieVictoryLubBalonLeci(bool zLotow, bool play);
		QList<QString> literyMarki;
		QList<QLabel *> labelyWAucie;
		QHash<tryb, QString> slownikTrybow;
		QHash<QString, QIcon>ikony;

		QList<QPushButton *> przyciski;
		QPushButton *wynikpierwsza;
		QPushButton *wynikdruga;
		QPushButton *wyniktrzecia;
		QPushButton *wynikczwarta;

		QMovie *movieL;
		QMovie *movieVictory;
		QMovie *movieVictory2;
		QMovie *movieBat;
		QMovie *movieHeli;
		QMovie *movieBatDuzo;

		QSoundEffect *muzykaGlowneTheme;
		QTimer *timerDolnyRuch;
		QTimer *timerGornegoLotu;
		QTimer *timerThemeSound;
		QTimer *timerVictory;
		QTimer *timerBalonowy;
		QTimer *timerKacprowy;
};

#endif // MAINWINDOW_H
