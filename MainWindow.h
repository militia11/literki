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

class MainWindow : public QMainWindow{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_pushButtonStart_clicked();
		void sprawdzLitereNaPrzycisku();

		void ruchKota();
		void ruchGornyLot();
		void przyblizenieKacpra();
		void koniecfajerwerka();

		void setButtonIcon(int a);
		void checksound();
		void victory();
		void bujajBalonem();

		void on_labelBal3_clicked();
		void on_labelBal1_clicked();
		void on_labelBal2_clicked();

		void on_pushButton_2_clicked();
		void on_pushButton_3_clicked();

		void on_pushButton_4_clicked();

	private:
		void visibleBaloonAndFrameLetter(bool visible);
		void inicjalizujIkonyLabely();
		void ustawNastepneAuto();
		void ustawLiteryWPrzyciskach();
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
		int victoryTimcounter;
		int ktoryBalon;
		int trafionychLiter;
		tryb aktualnyTryb;
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
		void ustawZdjecieVictoryLubBalonLeci();
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

		QSoundEffect *muzykaGlowneTheme;
		QTimer *timerKot;
		QTimer *timerGornegoLotu;
		QTimer *timerThemeSound;
		QTimer *timerVictory;
		QTimer *timerBalonowy;
		QTimer *timerKacprowy;
};

#endif // MAINWINDOW_H
