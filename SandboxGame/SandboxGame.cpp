#include <qt/qapplication.h>
#include <QtGui/qwidget.h>
#include "MyGlWindow.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	MyGlWindow myGlWindow;
	myGlWindow.show();
	return application.exec();
}