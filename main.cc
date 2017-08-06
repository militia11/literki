#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationDisplayName ("Literki");
	MainWindow w;
	w.showFullScreen ();
	return a.exec();
}
