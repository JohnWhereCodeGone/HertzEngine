#include "Lightmanager.h"





std::shared_ptr<Light> Lightmanager::CreateLight(const LightType& type)
{
	LightPtr toAdd;
	switch (type)
	{
		case(Pointlighter):
			toAdd = std::make_shared<PointLight>();
			break;

		case(Spotlighter):
			toAdd = std::make_shared<Spotlight>();
			break;

		case(DiffuseLighter):

			
			if (!m_lightlist.empty())
			{
				for (auto& light : m_lightlist)
				{
					if (light->GetLightType() == DiffuseLighter)
					{
						std::cout << "[Lightmanager]: There is already a diffuse light. Only one allowed per scene";
						break;
					}
					else
					{
						toAdd = std::make_shared<DiffuseLight>();
						break;
					}
				}

			}

	}

	if (toAdd)
	{
		toAdd->m_ID = std::to_string(reinterpret_cast<uintptr_t>(toAdd.get())).c_str();
		m_lightlist.push_back(toAdd);
		std::cout << "[Lightmanager]: Added Light of type" << toAdd->GetLightType() << std::endl;
		return toAdd;
	}


}

void Lightmanager::DeleteLight(LightPtr toDelete)
{
	auto it = std::find(m_lightlist.begin(), m_lightlist.end(), toDelete);

	if (*it)
	{
		m_lightlist.erase(it);
	}

}

void Lightmanager::ApplyLights(std::shared_ptr<Shader> shad)
{
	int spotlightIndex	= 0;
	int pointlightIndex	= 0;

	for (auto& light : m_lightlist)
	{
		switch (light->GetLightType())
		{
		case(DiffuseLighter):
			light->UpdateTargetShader(shad, -1);
			break;

		case(Spotlighter):
			light->UpdateTargetShader(shad, spotlightIndex);
			spotlightIndex++;
			break;

		case(Pointlighter):
			light->UpdateTargetShader(shad, pointlightIndex);
			pointlightIndex++;
			break;
		}


		
	}


}

//Note. This code doesn't check if when adding/applying, there are less than 8, or less than 25. 


//max spotlight 8
//max pointlight 25
//max diffuse light 1