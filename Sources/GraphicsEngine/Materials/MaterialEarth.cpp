#include "MaterialEarth.h"

#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include "GraphicsEngine/Light.h"

MaterialEarth::MaterialEarth()
{
	m_vsFileName = "ShaderEarth2";
	m_psFileName = "ShaderEarth2";

	m_pTexture1 = NULL;
}

void MaterialEarth::Init()
{
	Material::Init();

	m_pTexture1 = new Texture2D("Earth_Albedo.jpg");
	m_pTexture2 = new Texture2D("Earth_NormalMap.jpg");

	m_pTexture1->SetWrapMode(TEXTURE_WRAP_MODE_CLAMP);
	m_pTexture1->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
	//m_pTexture2->SetFilterMode(TEXTURE_FILTER_MODE_POINT);
}

void MaterialEarth::Deinit()
{
	delete m_pTexture1;
	m_pTexture1 = NULL;

	Material::Deinit();
}

void MaterialEarth::SetMaterial(const Object * pObject)
{
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const Matrix4x4 matWorldT = matWorld.Transpose();
	const Matrix4x4 matWorldNormal = matWorld.Inverse();


	// Получили список всех источников света в сцене
	std::list<const Light *> lights = SceneUtils::GetLights();
	//std::cout << lights.size() << std::endl;
	const size_t count = lights.size() < 3 ? lights.size() : 3;

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderEnd();

		SetPixelShaderBegin();

		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderTexture2d("texture2", m_pTexture2);

		SetPixelShaderMatrix4x4("matWorldNormal", matWorldNormal);
		SetPixelShaderMatrix4x4("matWorldT", matWorldT);
		SetPixelShaderVector4("materialColor", Vector4(1, 1, 1, 1));
		SetPixelShaderVector4("lightsCount", Vector4(count, 1, 1, 1));
		SetPixelShaderVector4("cameraPos", Vector4(SceneUtils::GetEyePosition(), 1.0));

		// Передаём параметры каждого источника света
		int i = 0;
		std::list<const Light *>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); ++iter, ++i)
		{
			const Light * pLight = *iter;
			const Vector4 lightType = pLight->GetType();
			const Vector4 lightPosition = Vector4(pLight->GetPosition(), 1);
			const Vector4 lightDirection = Vector4(pLight->GetDirection(), 0);
			const Vector4 lightColor = pLight->GetColor();

			// "lights[i]"
			std::string lightStr = "lights[" + std::to_string(static_cast<long long>(i)) + "]";

			// "lights[i].type", "lights[i].position", "lights[i].direction", "lights[i].color"
			SetPixelShaderVector4((lightStr + ".type").c_str(), lightType);
			SetPixelShaderVector4((lightStr + ".position").c_str(), lightPosition);
			SetPixelShaderVector4((lightStr + ".direction").c_str(), lightDirection);
			SetPixelShaderVector4((lightStr + ".color").c_str(), lightColor);
		}

		SetPixelShaderEnd();

	}
	SetMaterialEnd();
}
