#pragma once


#include "BulletCollision//CollisionShapes/btConcaveShape.h"


ATTRIBUTE_ALIGNED16(class)
	btVoxelTerrainShape : public btConcaveShape
{
public:
		
	BT_DECLARE_ALIGNED_ALLOCATOR();


	//
	// Constructor
	//

	btVoxelTerrainShape();

	virtual ~btVoxelTerrainShape();
	virtual void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const = 0;
	virtual void processAllTriangles(btTriangleCallback * callback, const btVector3& aabbMin, const btVector3& aabbMax) const = 0;
	virtual void performRaycast(btTriangleCallback * callback, const btVector3& raySource, const btVector3& rayTarget) const = 0;

	//debugging
	virtual const char* getName() const { return "HEIGHTFIELD"; }


protected:

	//
	// Helpers
	//

	void initialize();


	//
	// Properties
	//

	int m_Size;
	btVector3 m_localScaling;
};
