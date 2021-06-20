#include <QFile>
#include <QCoreApplication>
#include "FileOutputBridge.h"

bool FileOutputBridge::open(json argPackage)
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

void FileOutputBridge::close()
{
	filename.clear();
}

void FileOutputBridge::setConfig(json setting)
{
	if (setting["mode"] == "overwrite")
		mode = OverWrite;
	else if (setting["mode"] == "skip")
		mode = Skip;
	else if (setting["mode"] == "block")
		mode = Block;
	else
		mode = Block;
}

void FileOutputBridge::write(QByteArray data)
{
	QFile file(filename);
	switch (mode)
	{
	case OverWrite:
		file.open(QFile::WriteOnly);
		file.write(data);
		file.close();
		break;
	case Skip:
		if (file.exists())
			break;
		else
		{
			file.open(QFile::WriteOnly);
			file.write(data);
			file.close();
		}
		break;
	case Block:
		while (file.exists())
			QCoreApplication::processEvents();
		file.open(QFile::WriteOnly);
		file.write(data);
		file.close();
		break;
	}
}