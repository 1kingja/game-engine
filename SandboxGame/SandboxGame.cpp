#include <qt/qapplication.h>
#include <QtGui/qwidget.h>
#include "MyGlWindow.h"
#include <Windows.h>
#include <Qt\qdebug.h>

int main(int argc, char* argv[])
{
	LARGE_INTEGER clockFrequency;
	QueryPerformanceFrequency(&clockFrequency);


	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	QueryPerformanceCounter(&startTime);
	qDebug() << "Hello";
	QueryPerformanceCounter(&endTime);

	LARGE_INTEGER delta;
	delta.QuadPart = endTime.QuadPart - startTime.QuadPart;

	float deltaSeconds = ((float)delta.QuadPart) / clockFrequency.QuadPart;

	QApplication application(argc, argv);
	MyGlWindow myGlWindow;
	myGlWindow.show();
	return application.exec();
}