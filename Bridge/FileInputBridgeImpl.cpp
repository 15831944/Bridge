#include <QFile>
#include <QCoreApplication>
#include "FileInputBridgeImpl.h"

bool FileInputBridgeImpl::init(json argPackage)
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

void FileInputBridgeImpl::uninit()
{
	filename.clear();
}

bool FileInputBridgeImpl::canRead()
{
	return QFile::exists(filename);
}

QByteArray FileInputBridgeImpl::read()
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