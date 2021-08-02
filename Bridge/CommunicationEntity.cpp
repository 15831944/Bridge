#include "CommunicationEntity.h"

CommunicationEntity::CommunicationEntity()
{
	connect(this, &CommunicationEntity::newInputMessage, [=](const std::shared_ptr<IBridgeInput>&, QByteArray message)
		{
			for (auto& output : outputs)
			{
				try
				{
					output->write(message);
				}
				catch (...)
				{
					emit bridgeOutputError(output, message);
				}
			}
		});
}

void CommunicationEntity::run()
{
	while (!inputs.isEmpty() && !outputs.isEmpty())
	{
		for (auto& input : inputs)
		{
			if (input->canRead())
			{
				try
				{
					emit newInputMessage(input, input->read());
				}
				catch (...)
				{
					emit bridgeInputError(input);
				}
			}
		}
	}
}