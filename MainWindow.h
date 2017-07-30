#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QMap>
//#include"time.h"
#include <cstdlib>           //rand()

namespace Ui {
class MainWindow;
}
enum tryb {
	NONE,
	AUDI,
	FORD,
	FIAT,
};

class MainWindow : public QMainWindow{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_pushButtonStart_clicked();
		void bujajBalonem();

		void on_labelBal3_clicked();
		void on_labelBal1_clicked();
		void on_labelBal2_clicked();

	private:
		void motywAudi();

		QMap<QString, QIcon>ikony;
		QList<QPushButton *> przyciski;

		tryb aktualnyTryb;
		QPushButton *wynikpierwsza;
		QPushButton *wynikdruga;
		QPushButton *wyniktrzecia;
		QPushButton *wynikczwarta;
int wylosowane[4];
		bool czyBylaWylosowana( int iLiczba, int tab[], int ile );
		int wylosuj();
		void wylosuj4Liczby();
		void resizeEvent(QResizeEvent *evt);
		void wlaczBujanieBalonem();
		void pokazBalon1();
		void pokazBalon2();
		void pokazBalon3();
		QTimer *timerBalonowy;
		Ui::MainWindow *ui;
		int ktoryBalon;
};

#endif // MAINWINDOW_H
