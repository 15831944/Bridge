#include "CommunicationEntity.h"

CommunicationEntity::CommunicationEntity()
{
	connect(this, &CommunicationEntity::newInputMessage, [=](QByteArray message)
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
					auto message = input->read();
					emit newInputMessage(input, message);
				}
				catch (...)
				{
					emit bridgeInputError(input);
				}
			}
		}
	}
}