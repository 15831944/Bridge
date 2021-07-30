#include <QFile>
#include <QCoreApplication>
#include "FileOutputBridgeImpl.h"

bool FileOutputBridgeImpl::init(json argPackage)
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

void FileOutputBridgeImpl::uninit()
{
	filename.clear();
}

void FileOutputBridgeImpl::setConfig(json setting)
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

IBridgeIO::json FileOutputBridgeImpl::config() const
{
	json j;
	switch (mode)
	{
	case OverWrite:
		j["mode"] = "overwrite";
		break;
	case Skip:
		j["mode"] = "skip";
		break;
	case Block:
	default:
		j["mode"] = "block";
		break;
	}
	return j;
}

void FileOutputBridgeImpl::write(QByteArray data)
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