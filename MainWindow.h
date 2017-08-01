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

		void checksound();
		void victory();
		void bujajBalonem();

		void on_labelBal3_clicked();
		void on_labelBal1_clicked();
		void on_labelBal2_clicked();

		void on_pushButton_2_clicked();

	private:
		int aktualnyTheme;
		void inicjalizujIkonyLabely();
		void ustawNastepneAuto();
		void ustawLiteryWPrzyciskach();
		int pobierzIdNastepnegoAuta();
		tryb aktualnyTryb;

		int kliknietoDobrze;
		int kliknietoZle;
		int kliknietoWin;

		QStringList themes;
		QList<QString>waveOk;
		QList<QString>waveWrong;
		QList<QString>waveWin;
		void ustawZdjecieVictoryLubBalonLeci();
		int trafionychLiter;
		QList<QString> literyMarki;
		QList<QLabel *> labelyWAucie;
		QHash<tryb, QString> slownikTrybow;
		QHash<QString, QIcon>ikony;

		QList<QPushButton *> przyciski;
		QPushButton *wynikpierwsza;
		QPushButton *wynikdruga;
		QPushButton *wyniktrzecia;
		QPushButton *wynikczwarta;

		void odkryjNaNowoPrzyciskiZPoszukiwanych();
		void uzupelnijPrzyciskiLiterami();
		void przeniesLitereDoZdjAuta(QPushButton *but);
		void aktualizujAktywnaLitere();

		void wyswietlLiteryDlaAudi();
		void wyswietlLiteryDlaFiat();
		void wyswietlLiteryDlaFord();
		void wyswietlLiteryDlaOpel();

		int wylosowaneLiczbyDoPrzyciskow[4];
		bool czyBylaWylosowana( int iLiczba, int tab[], int ile );
		int wylosuj(int zIlu);
		void wylosuj4Liczby();
		int victoryTimcounter;
		void resizeEvent(QResizeEvent *evt);
		void wlaczBujanieBalonem();
		void pokazBalon1();
		void pokazBalon2();
		void pokazBalon3();
		QSoundEffect *ef;
		QTimer *timerThemeSound;
		QTimer *timerVictory;
		QTimer *timerBalonowy;
		Ui::MainWindow *ui;
		int ktoryBalon;
};

#endif // MAINWINDOW_H
