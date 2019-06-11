#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MaterialDiffuse.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"


/**
* @brief Shows how to write lightning materials.
* Key code is situated in the classes MaterialDiffuse, Light.
*/
class Task04 : public Task
{
public:
	virtual ~Task04() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();

		// FPS counter
		{
			Object * pObject = new Object();
			pObject->m_pTransform = new Transform();
			pObject->AddComponent(new FpsCounter());

			scene.AddObject(pObject);
		}

		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform(Vector3(0.0f, 0.0f, -7.0f), Vector3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent(pCamera);

			scene.SetCamera(pCamera);
		}

		// Object - Sphere

		Object * pObject1 = new Object();

		pObject1->m_pTransform = new Transform(0, 0, 0, 0, 0, 0, 3, 3, 3);
		pObject1->m_pMesh = new MeshSphere(5);
		pObject1->m_pMaterial = new MaterialDiffuse();
		pObject1->AddComponent(new ObjectRotator(0, 50, 0));

		scene.AddObject(pObject1);

		Object * pObject2 = new Object();

		pObject2->m_pTransform = new Transform(2, 0, 0, 0, 0, 0, 1, 1, 1);
		//pObject2->m_pMesh = new MeshSphere(20);
		//pObject2->m_pMaterial = new MaterialDiffuse();
		pObject2->AddComponent(new ObjectRotator(0, 30, 0));

		scene.AddObject(pObject2);


		// Ligth source #1 - Directional
		{
			Light * pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(1, 1, 0);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(1, 0, 0, 0, 90, 0, 1, 1, 1);
			//pLightObject->AddComponent(new ObjectRotator(0, 10, 0));
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}

		// Ligth source #2 - Point
		{
			Light * pLight = new Light(LIGHT_POINT);
			pLight->SetColor(1, 1, 1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pMesh = new MeshSphere(20);

			pLightObject->m_pMaterial = new MaterialDiffuse();

			pLightObject->m_pTransform = new Transform(1, 0, 0, 0, 90, 0, 0.1, 0.1, 0.1);
			pLightObject->AddComponent(new ObjectRotator(0, 10, 0));

			pLightObject->m_pTransform->SetParent(pObject2->m_pTransform);

			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}

		// Ligth source #3 - Spot Light
		{
			Light * pLight = new Light(LIGHT_SPOT);
			pLight->SetColor(1, 0.05, 1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();

			pLightObject->m_pMesh = new MeshSphere(20);
			pLightObject->m_pMaterial = new MaterialDiffuse();

			pLightObject->m_pTransform = new Transform(0.0f, 0.0f, -0.7f, 0.0f, 0.0f, 0.0f, 0.1, 0.1, 0.1);
			pLightObject->AddComponent(pLight);
			
			pLightObject->m_pTransform->SetParent(pObject1->m_pTransform);
	//		pLightObject->AddComponent(new ObjectRotator(0, 300, 0));

			scene.AddLight(pLight);
		}
	}

	virtual void Update()
	{

	}
};
