#pragma once

#include "../Entity/Entity.h"


struct AstronomicalData
{

    static constexpr double G = 6.67430e-11;

    StellarType     m_ownerType;
    std::string     m_name;

    bool m_hasParent = false;

    const glm::dvec3* m_livePosition = nullptr;
    const glm::dvec3* m_liveVelocity = nullptr;
    const glm::dvec3* m_parentPosition = nullptr;
    const glm::dvec3* m_parentVelocity = nullptr;
    const RotationState* m_liveRotation = nullptr;

     double* m_liveMass = nullptr;
    const double* m_parentMass = nullptr;



    double m_distanceFromParent = 0.0;
    double m_relativeSpeed = 0.0;
    double m_specificEnergy = 0.0;
    double m_orbitalPeriodDays = 0.0;
    double m_dayLengthHours = 0.0;

    AstronomicalData(std::shared_ptr<Entity> self, std::shared_ptr<Entity> parent = nullptr)
    {
        if (self)
        {
            std::shared_ptr<Transform> transform = self->GetTransform();
            m_ownerType = transform->m_stellartype;
            m_livePosition = &transform->m_localPos;

            std::shared_ptr<SphereCollider> col = std::static_pointer_cast<SphereCollider>(self->GetCollider());
            if (col) {
                m_liveVelocity = &col->m_velocity;
                m_liveMass = &col->m_mass;
                m_liveRotation = &col->m_rotationState;
                m_name = *self->GetName();
            }
        }

        if (parent)
        {
            m_hasParent = true;
            std::shared_ptr<Transform> parentTransform = parent->GetTransform();
            m_parentPosition = &parentTransform->m_localPos;

            std::shared_ptr<SphereCollider> parentCol = std::static_pointer_cast<SphereCollider>(parent->GetCollider());
            if (parentCol)
            {
                m_parentVelocity = &parentCol->m_velocity;
                m_parentMass = &parentCol->m_mass;
            }
        }

    }



    void UpdateData()
    {
        if (m_liveRotation->angularSpeed > 0.0)
        {
            m_dayLengthHours = (glm::two_pi<double>() / m_liveRotation->angularSpeed / 3600.0); // 2*pi / aV;
        }
        else
        {
            m_dayLengthHours = 0.0;
        }

        if (m_ownerType == STAR || !m_hasParent)
        {
            double m_distanceFromParent = 0.0;
            double m_relativeSpeed = 0.0;
            double m_specificEnergy = 0.0;
            double m_orbitalPeriodDays = 0.0;
            double m_dayLengthHours = 0.0;

            return;
        }



        glm::dvec3 relPos = *m_livePosition - *m_parentPosition;
        glm::dvec3 relVelocity = *m_liveVelocity - *m_parentVelocity;

        m_distanceFromParent = glm::length(relPos);
        m_relativeSpeed = glm::length(relVelocity);

        // Pkinetic = 0.5 * mv^2 + Ppotential = mu/r -- Vis-viva equation for specific orbital energy; 

        double mu = G * (*m_parentMass + *m_liveMass);


        m_specificEnergy = 0.5 * (glm::dot(relVelocity, relVelocity)) - (mu / m_distanceFromParent);

        //calculating orbital period based on specific orbital energy. Energy -> Major Axis -> Kepler's third law.

        if (m_specificEnergy < 0.0)
        {
            double MajorAxis = -mu / (2.0 * m_specificEnergy);
            double orbTimeSeconds = glm::two_pi<double>() * std::sqrt((MajorAxis * MajorAxis * MajorAxis) / mu);
            m_orbitalPeriodDays = orbTimeSeconds / 86400.0;

        }
        else
        {
            m_orbitalPeriodDays = -1.0;
        }




    }

};