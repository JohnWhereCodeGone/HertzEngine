#pragma once
#include "../glm/glm.hpp"


struct KahanDvec3
{

	glm::dvec3 m_val	= glm::dvec3(0.0);
	glm::dvec3 m_error	= glm::dvec3(0.0);


	void AddTo(const glm::dvec3& offset)
	{
		if (glm::any(glm::isnan(offset)) || glm::any(glm::isinf(offset))) {
			return;
		}
		glm::dvec3 y = offset - m_error; //where error is corrected



		glm::dvec3 t = m_val + y; //where error is created

		m_error = (t - m_val) - y; //where error is recovered

		m_val = t;
	};

	void Reset()
	{

		m_val	= glm::dvec3(0.0);
		m_error = glm::dvec3(0.0);

	}


};


class KahanSummarization
{
};

