#pragma once
#include "../Threading/Messaging.h"
#include "HertzTexture.h"

class MipMapMessage : public Message
{
public:

	MipMapMessage(const MipMapSettings& setting);
	

	const MipMapSettings& GetSetting() const;
	void SetSetting(const MipMapSettings& setting);

private:

	void QueuePop() override;
	MipMapSettings m_setting;
	
};

