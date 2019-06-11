#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialEarth final : public Material
{
public:
	MaterialEarth();

	virtual void Init();
	virtual void Deinit();

	virtual void SetMaterial(const Object * pObject);

private:
	Texture2D *	m_pTexture1;
	Texture2D *	m_pTexture2;

	TextureFilterMode m_filterMode1;
	TextureFilterMode m_filterMode2;
};


