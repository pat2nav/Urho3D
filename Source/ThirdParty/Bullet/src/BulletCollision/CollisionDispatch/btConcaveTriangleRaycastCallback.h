/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2013 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/**
 * @mainpage Bullet Documentation
 *
 * @section intro_sec Introduction
 * Bullet is a Collision Detection and Rigid Body Dynamics Library. The Library is Open Source and free for commercial use, under the ZLib license ( http://opensource.org/licenses/zlib-license.php ).
 *
 * The main documentation is Bullet_User_Manual.pdf, included in the source code distribution.
 * There is the Physics Forum for feedback and general Collision Detection and Physics discussions.
 * Please visit http://www.bulletphysics.org
 *
 * @section install_sec Installation
 *
 * @subsection step1 Step 1: Download
 * You can download the Bullet Physics Library from the github repository: https://github.com/bulletphysics/bullet3/releases 
 *
 * @subsection step2 Step 2: Building
 * Bullet has multiple build systems, including premake, cmake and autotools. Premake and cmake support all platforms.
 * Premake is included in the Bullet/build folder for Windows, Mac OSX and Linux. 
 * Under Windows you can click on Bullet/build/vs2010.bat to create Microsoft Visual Studio projects. 
 * On Mac OSX and Linux you can open a terminal and generate Makefile, codeblocks or Xcode4 projects:
 * cd Bullet/build
 * ./premake4_osx gmake or ./premake4_linux gmake or ./premake4_linux64 gmake or (for Mac) ./premake4_osx xcode4
 * cd Bullet/build/gmake
 * make
 * 
 * An alternative to premake is cmake. You can download cmake from http://www.cmake.org
 * cmake can autogenerate projectfiles for Microsoft Visual Studio, Apple Xcode, KDevelop and Unix Makefiles.
 * The easiest is to run the CMake cmake-gui graphical user interface and choose the options and generate projectfiles.
 * You can also use cmake in the command-line. Here are some examples for various platforms:
 * cmake . -G "Visual Studio 9 2008"
 * cmake . -G Xcode
 * cmake . -G "Unix Makefiles"
 * Although cmake is recommended, you can also use autotools for UNIX: ./autogen.sh ./configure to create a Makefile and then run make.
 * 
 * @subsection step3 Step 3: Testing demos
 * Try to run and experiment with BasicDemo executable as a starting point.
 * Bullet can be used in several ways, as Full Rigid Body simulation, as Collision Detector Library or Low Level / Snippets like the GJK Closest Point calculation.
 * The Dependencies can be seen in this documentation under Directories
 * 
 * @subsection step4 Step 4: Integrating in your application, full Rigid Body and Soft Body simulation
 * Check out BasicDemo how to create a btDynamicsWorld, btRigidBody and btCollisionShape, Stepping the simulation and synchronizing your graphics object transform.
 * Check out SoftDemo how to use soft body dynamics, using btSoftRigidDynamicsWorld.
 * @subsection step5 Step 5 : Integrate the Collision Detection Library (without Dynamics and other Extras)
 * Bullet Collision Detection can also be used without the Dynamics/Extras.
 * Check out btCollisionWorld and btCollisionObject, and the CollisionInterfaceDemo.
 * @subsection step6 Step 6 : Use Snippets like the GJK Closest Point calculation.
 * Bullet has been designed in a modular way keeping dependencies to a minimum. The ConvexHullDistance demo demonstrates direct use of btGjkPairDetector.
 *
 * @section copyright Copyright
 * For up-to-data information and copyright and contributors list check out the Bullet_User_Manual.pdf
 * 
 */

/*
#ifndef BT_COLLISION_WORLD_H
#define BT_COLLISION_WORLD_H

class btCollisionShape;
class btConvexShape;
class btBroadphaseInterface;
class btSerializer;

#include "LinearMath/btVector3.h"
#include "LinearMath/btTransform.h"
#include "btCollisionObject.h"
#include "btCollisionDispatcher.h"
#include "BulletCollision/BroadphaseCollision/btOverlappingPairCache.h"
#include "LinearMath/btAlignedObjectArray.h"

*/

#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#include "btCollisionWorld.h"
#include "BulletCollision/CollisionShapes/btConcaveShape.h"



#pragma once


//ConvexCast::CastResult
struct btConcaveTriangleRaycastCallback : public btTriangleRaycastCallback
{
	btCollisionWorld::RayResultCallback* m_resultCallback;
	const btCollisionObject* m_collisionObject;
	const btConcaveShape* m_triangleMesh;
	btTransform m_colObjWorldTransform;
	bool m_hitFound = false;

	btConcaveTriangleRaycastCallback(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback* resultCallback, const btCollisionObject* collisionObject, const btConcaveShape* triangleMesh, const btTransform& colObjWorldTransform) :
		btTriangleRaycastCallback(from, to, resultCallback->m_flags),
		m_resultCallback(resultCallback),
		m_collisionObject(collisionObject),
		m_triangleMesh(triangleMesh),
		m_colObjWorldTransform(colObjWorldTransform)
	{
	}

	virtual btScalar reportHit(const btVector3& hitNormalLocal, btScalar hitFraction, int partId, int triangleIndex)
	{
		btCollisionWorld::LocalShapeInfo shapeInfo;
		shapeInfo.m_shapePart = partId;
		shapeInfo.m_triangleIndex = triangleIndex;

		btVector3 hitNormalWorld = m_colObjWorldTransform.getBasis() * hitNormalLocal;

		btCollisionWorld::LocalRayResult rayResult(m_collisionObject,
													&shapeInfo,
													hitNormalWorld,
													hitFraction);

		bool normalInWorldSpace = true;
		m_hitFound = true;
		return m_resultCallback->addSingleResult(rayResult, normalInWorldSpace);
	}
};



