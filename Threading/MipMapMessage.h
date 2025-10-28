#pragma once
#include "../Threading/Messaging.h"
#include "HertzTexture.h"

class MipMapMessage : public Message
{
public:
	//currently not in use, consider for a ui queue/event system
	MipMapMessage(const MipMapSettings& setting);
	

	const MipMapSettings& GetSetting() const;
	void SetSetting(const MipMapSettings& setting);

private:

	void QueuePop() override;
	MipMapSettings m_setting;
	
};

