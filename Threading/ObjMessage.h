#pragma once

#include "Messaging.h"

class ObjMessage : Message
{
public:

	ObjMessage();

	std::string tPath;
	void QueuePop() override;

};

