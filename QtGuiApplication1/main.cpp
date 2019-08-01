#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv); //QApplication是Qt的标准应用程序类，定义一个该类的实例a,就是应用程序对象
	QtGuiApplication1 w; //定义一个QtGuiApplication1 类的变量，QtGuiApplication1是本实例设计的窗口的类名
	w.show();//定义窗口以后，显示窗口
	return a.exec();//启动应用程序，开始应用程序的消息循环和事件处理
}
