#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialRoad final : public Material
{
public:
	MaterialRoad(TextureFilterMode filterMode);

	virtual void Init();
	virtual void Deinit();

	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture1;
	Texture2D *	m_pTexture2;
	Texture2D *	m_pTexture3;

	TextureFilterMode m_filterMode1;
	TextureFilterMode m_filterMode2;
	TextureFilterMode m_filterMode3;
};


