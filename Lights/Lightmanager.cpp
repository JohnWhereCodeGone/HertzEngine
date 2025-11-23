#include "Lightmanager.h"
#include "../Lights/DiffuseLight.h"
#include "../Lights/PointLight.h"
#include "../Lights/Spotlight.h"



std::shared_ptr<Light> Lightmanager::CreateLight(const LightType& type)
{
	LightPtr toAdd;
	std::string name;
	bool isAlreadyDiffuseLight = false;

	switch (type)
	{
		case(Pointlighter):
			toAdd = std::make_shared<PointLight>();
			break;

		case(Spotlighter):
			toAdd = std::make_shared<Spotlight>();
			break;

		case(DiffuseLighter):

			if (m_lightlist.empty())
			{
				toAdd = std::make_shared<DiffuseLight>();
				name = "Diffuse ";
			}
			else
			{
				for (auto& light : m_lightlist)
				{
					if (light->GetLightType() == DiffuseLighter)
					{
						isAlreadyDiffuseLight = true;
					}
				}

				if (!isAlreadyDiffuseLight)
				{
					toAdd = std::make_shared<DiffuseLight>();
					name = "Diffuse ";
					break;
				}

			}
			break;
					


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

const std::vector<std::shared_ptr<Light>>& Lightmanager::GetLights()
{
	return this->m_lightlist;
}

//Note. This code doesn't check if when adding/applying, there are less than 8, or less than 25. 


//max spotlight 8
//max pointlight 25
//max diffuse light 1