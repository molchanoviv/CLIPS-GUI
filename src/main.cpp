#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QTranslator qtTranslator;
	qtTranslator.load(QLibraryInfo::location (QLibraryInfo::TranslationsPath) + "/qt_" + QLocale::system().name());
	app.installTranslator(&qtTranslator);
	QTranslator myappTranslator;
	myappTranslator.load(":/translations/CLIPS-GUI_" + QLocale::system().name());
	qDebug()<<QLocale::system().name();
	app.installTranslator(&myappTranslator);
	MainWindow w;
	w.show();
	return app.exec();
}
