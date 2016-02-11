#include <qt/qapplication.h>
#include <QtGui/qwidget.h>
#include "MyGlWindow.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	LARGE_INTEGER clockFrequency;
	QueryPerformanceFrequency(&clockFrequency);


	QApplication application(argc, argv);
	MyGlWindow myGlWindow;
	myGlWindow.show();
	return application.exec();
}