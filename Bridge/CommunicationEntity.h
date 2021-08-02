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
	void newInputMessage(const std::shared_ptr<IBridgeInput>&, QByteArray)const;
	void bridgeInputError(const std::shared_ptr<IBridgeInput>&)const;
	void bridgeOutputError(const std::shared_ptr<IBridgeOutput>&, QByteArray)const;
protected:
	QList<std::shared_ptr<IBridgeInput>> inputs;
	QList<std::shared_ptr<IBridgeOutput>> outputs;
};
