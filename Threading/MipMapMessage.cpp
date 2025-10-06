#include "MipMapMessage.h"



MipMapMessage::MipMapMessage(const MipMapSettings& setting)
{
	this->m_setting = setting;
}

const MipMapSettings& MipMapMessage::GetSetting() const
{
	return this->m_setting;
}

void MipMapMessage::SetSetting(const MipMapSettings& setting)
{
	this->m_setting = setting;
}

void MipMapMessage::QueuePop()
{
}


