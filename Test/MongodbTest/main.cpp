#include <QtCore/QCoreApplication>
#include <QDebug>
#include <mongocxx/client.hpp>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "Hello...";

	return a.exec();
}
