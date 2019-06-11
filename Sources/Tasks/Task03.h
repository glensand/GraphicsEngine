#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialUnlitSimple.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/FpsCounter.h"
#include "Tasks/ObjectRotator.h"

#include <iostream>

/**
* @brief Shows how to write text to the screen.
* Key code is situated in the classes FpsCounter, GUI, InternalGUI, DX9GUI, GL20GUI.
*/
class Task03: public Task
{

	FpsCounter* fpsCounter{};
public:
	virtual ~Task03() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();

		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform(Vector3(0, 3, -10), Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent(pCamera);

			scene.SetCamera(pCamera);
		}

		// FPS counter
		{
			Object * pObject = new Object();
			pObject->m_pTransform = new Transform();
			fpsCounter = new FpsCounter();
			pObject->AddComponent(fpsCounter);

			scene.AddObject(pObject);
		}

		//objects
		{
			for (size_t i = 0; i < 20; i++) {

				Object * pObject = new Object();
				pObject->m_pTransform = new Transform(Vector3(1 - 0.1 * i, 1 - 0.1 * i, 0), Vector3(0, 30, 0));
				pObject->m_pMesh = new MeshCube(10);
				pObject->m_pMaterial = new MaterialUnlitSimple("ShaderUnlitSimple", "ShaderUnlitSimple");

				scene.AddObject(pObject);
			}
		}
	}

	virtual void Update()
	{
		
	}
};
