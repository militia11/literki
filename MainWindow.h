#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_pushButtonStart_clicked();
		void bujajBalonem();

	private:
		void wlaczBujanieBalonem();
		void pokazBalon1();
		void pokazBalon2();
		void pokazBalon3();
		void resizeEvent(QResizeEvent *evt);

		QTimer *timerBalonowy;
		Ui::MainWindow *ui;
		int ktoryBalon;
};

#endif // MAINWINDOW_H
