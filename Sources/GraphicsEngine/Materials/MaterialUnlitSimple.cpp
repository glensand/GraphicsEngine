#include "MaterialUnlitSimple.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include <cmath>
#include <ctime>
#include <chrono>
#include <iostream>

#include "GraphicsEngine/Time.h"

MaterialUnlitSimple::MaterialUnlitSimple(const std::string& vShader, const std::string& fShader)
{
	m_vsFileName = vShader;
	m_psFileName = fShader;
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialUnlitSimple::Init()
{
	Material::Init();
	
	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialUnlitSimple::Deinit()
{
	Material::Deinit();
}

void MaterialUnlitSimple::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		
		auto time = Time::GetTime();
		//time = 
		//std::time_t time = static_cast<float>(std::chrono::system_clock::to_time_t(rTime));
		std::cout << time << std::endl;
		SetVertexShaderVector4("time", Vector4(std::sin(time), 0, 0, 0));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
