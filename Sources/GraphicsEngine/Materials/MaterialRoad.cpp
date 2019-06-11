#include "MaterialRoad.h"

#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

MaterialRoad::MaterialRoad(TextureFilterMode filterMode)
{
	m_vsFileName = "road";
	m_psFileName = "road";

	m_pTexture1 = NULL;
	m_filterMode1 = filterMode;

}

void MaterialRoad::Init()
{
	Material::Init();

	m_pTexture1 = new Texture2D("road_1.jpg");
	m_pTexture2 = new Texture2D("road_2.jpg");
	m_pTexture3 = new Texture2D("road_3.jpg");

	m_pTexture1->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
	m_pTexture2->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
	m_pTexture3->SetFilterMode(TEXTURE_FILTER_MODE_POINT);

}

void MaterialRoad::Deinit()
{
	delete m_pTexture1;
	m_pTexture1 = NULL;

	Material::Deinit();
}

void MaterialRoad::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));

		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderTexture2d("texture2", m_pTexture2);		
		SetPixelShaderTexture2d("texture3", m_pTexture3);

		SetPixelShaderEnd();
	}
	SetMaterialEnd();

}
