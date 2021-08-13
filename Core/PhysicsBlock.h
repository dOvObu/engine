#ifndef INCLUDED_PHYSICS_BLOCK_H
#define INCLUDED_PHYSICS_BLOCK_H
#include <vector>

namespace Core {


struct Transform {
	float PositionX{ 0.f };
	float PositionY{ 0.f };
	float HalfWidth { 10.f };
	float HalfHeight{ 10.f };
	float VelocityDx{ 0.f };
	float VelocityDy{ 0.f };
	float Mass{ 5.f };
	float Elasticity{ 1.f };

	float MaxX() const { return PositionX + HalfWidth ; }
	float MinX() const { return PositionX - HalfWidth ; }
	float MaxY() const { return PositionY + HalfHeight; }
	float MinY() const { return PositionY - HalfHeight; }

	float ImpulsX() const { return Mass * VelocityDx; }
	float ImpulsY() const { return Mass * VelocityDy; }
	
	bool Intersects(Transform* b);

	bool _xIntersects{ false }, _yIntersects{ false };
};

class Physics {
private:
	static std::vector<Transform*> _rigidPhysics;
	static float _g;
public:
	static void Update();
	static void Add(Transform* newTransform);
};

}

#endif // ! INCLUDED_PHYSICS_BLOCK_H
