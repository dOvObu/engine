#include "PhysicsBlock.h"
#include "Time.h"
#include <iostream>
using namespace Core;


std::vector<Transform*> Physics::_rigidPhysics;
float Physics::_g{ 800.f };


bool Transform::Intersects(Core::Transform* b)
{
	return (MinX() <= b->MaxX() && MaxX() >= b->MinX()) &&
		   (MinY() <= b->MaxY() && MaxY() >= b->MinY()) ;
}


void Core::Physics::Update()
{
	auto size = _rigidPhysics.size();
	for (size_t idx = 0; idx < size; ++idx)
	{
		auto rigidA = _rigidPhysics[idx];
		rigidA->VelocityDy += _g * Time::DeltaTime;
		rigidA->PositionX += rigidA->VelocityDx * Time::DeltaTime;
		rigidA->PositionY += rigidA->VelocityDy * Time::DeltaTime;
		
		//*
		for (size_t jdx = idx + 1; jdx < size; ++jdx)
		{
			auto rigidB = _rigidPhysics[jdx];

			if (rigidA->Intersects(rigidB))
			{
				auto&& MassSum = rigidA->Mass + rigidB->Mass;
				{
					auto&& impSumX = rigidA->ImpulsX() + rigidB->ImpulsX();
					auto&& symA = 0.f < rigidA->VelocityDx ? -1.f : 1.f;
					auto&& symB = 0.f < rigidB->VelocityDx ? -1.f : 1.f;
					rigidB->VelocityDx = rigidA->VelocityDx = impSumX / MassSum;
					rigidA->VelocityDx *= symA * rigidA->Elasticity;
					rigidB->VelocityDx *= symB * rigidB->Elasticity;
				}
				{
					auto&& impSumY = rigidA->ImpulsY() + rigidB->ImpulsY();
					auto&& symA = 0.f < rigidA->VelocityDy ? -1.f : 1.f;
					auto&& symB = 0.f < rigidB->VelocityDy ? -1.f : 1.f;
					rigidB->VelocityDy = rigidA->VelocityDy = impSumY / MassSum;
					rigidA->VelocityDy *= symA *(rigidA->Mass/MassSum)* rigidA->Elasticity;
					rigidB->VelocityDy *= symB *(rigidB->Mass/MassSum)* rigidB->Elasticity;

				}
			}
		}
		//*/
	}
}

void Core::Physics::Add(Transform* newTransform)
{
	_rigidPhysics.push_back(newTransform);
}
