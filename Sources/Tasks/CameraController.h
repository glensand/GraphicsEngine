#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include <cmath>

#include <iostream>

class CameraController : public Component
{
	Vector3 mousePos = Input::GetMousePosition();;
	Vector3 mousePosPrev;

	float yaw{ -90.0f };
	float pitch{ 0.0f };

public:
	CameraController()
	{
		mousePos		= Vector3::Zero();
		mousePosPrev	= Vector3::Zero();
	}

	virtual ~CameraController() {}

	virtual void Update() 
	{
		Transform * pTransform = m_pObject->m_pTransform;
		
		pitch = pTransform->GetEulerAngles().x;
		yaw = pTransform->GetEulerAngles().y;
		// Camera Translation
		{
			Vector3 forward	= pTransform->GetForward();
			Vector3 right	= pTransform->GetRight();
			double dt = Time::GetDeltaTime();

			const double speed = 1.0;
			Vector3 direction;

			if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
			{
				direction += forward;
			}
			
			if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
			{
				direction -= forward;
			}
			
			if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
			{
				direction -= right;
			}

			if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
			{
				direction += right;
			}

			pTransform->Translate( speed * dt * direction );
		}

		// Camera Rotation
		{
			mousePos = Input::GetMousePosition();

			// TODO : Task08
			float xoffset = mousePos.x - mousePosPrev.x;
			float yoffset = mousePos.y - mousePosPrev.y;
			mousePosPrev = mousePos;

			float sensitivity = 0.1;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			Vector3 front;

			/*float pi = 3.14;
			float prad = pitch / 180 * pi;
			float yrad = yaw / 180 * pi;
			*/
			/*
			front.x = std::cos(yrad) * cos(prad);
			front.y = std::sin(prad);
			front.z = std::sin(yrad) * cos(prad);
*/
			front.x = pitch;
			front.y = yaw;
			front.z = 0.0f;

			pTransform->SetEulerAngles(front);
		}
	}
};
