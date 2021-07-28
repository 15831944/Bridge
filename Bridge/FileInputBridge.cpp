#include <QFile>
#include <QCoreApplication>
#include "FileInputBridge.h"

bool FileInputBridge::open(json argPackage)
{
	try
	{
		filename = QString::fromStdString(argPackage["filename"]);
		return true;
	}
	catch (...)
	{
	}
	return false;
}

void FileInputBridge::close()
{
	filename.clear();
}

QByteArray FileInputBridge::read()
{
	if (filename.isEmpty())
		throw std::invalid_argument{ R"(Argurment "filename" is empty.)" };
	QFile file(filename);
	while (!file.exists() || !file.open(QFile::ReadOnly))
		QCoreApplication::processEvents();

	auto data = file.readAll();

	file.close();
	file.remove();

	return data;
}