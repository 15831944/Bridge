#pragma once
#include <QThread>
#include "IBridgeInput.h"
#include "IBridgeOutput.h"
class CommunicationEntity :
	public QThread
{
	Q_OBJECT
public:
	CommunicationEntity();
	void run() override;

signals:
	void newInputMessage(const std::unique_ptr<IBridgeInput>&, QByteArray)const;
	void bridgeInputError(const std::unique_ptr<IBridgeInput>&)const;
	void bridgeOutputError(const std::unique_ptr<IBridgeOutput>&, QByteArray)const;
protected:
	QList<std::unique_ptr<IBridgeInput>> inputs;
	QList<std::unique_ptr<IBridgeOutput>> outputs;
};
