#include "GL20TextureSampler.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineContext.h"


GL20TextureSampler::GL20TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
{
	SetFilterMode( filterMode );
	SetWrapMode  ( wrapMode );
}

GL20TextureSampler::~GL20TextureSampler()
{

}

void GL20TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	// http://www.learnopengles.com/android-lesson-six-an-introduction-to-texture-filtering/
	// https://www.opengl.org/wiki/Sampler_Object
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
	// http://opengl-master.ru/view_post.php?id=78
	// http://www.araku.ac.ir/~d_comp_engineering/88892/1323108/OpenGL%20Game%20Development.pdf

	if (filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		m_minFilterMode = GL_NEAREST;
		m_magFilterMode = GL_NEAREST;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		m_minFilterMode = GL_LINEAR;
		m_magFilterMode = GL_LINEAR;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		m_magFilterMode = GL_LINEAR_MIPMAP_NEAREST;
		m_minFilterMode = GL_LINEAR_MIPMAP_NEAREST;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		m_useAniso = true;
	}
}

void GL20TextureSampler::SetWrapMode(TextureWrapMode wrapMode)
{
	// http://gamedev.stackexchange.com/questions/62548/what-does-changing-gl-texture-wrap-s-t-do

	if (wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		m_wrapMode = GL_CLAMP;
	}
	else if (wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		m_wrapMode = GL_REPEAT;
	}
}

void GL20TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	

	// Set wrap mode (Clamp, Repeat).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
	// TODO: Task05_01
		
	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic).
	// TODO: Task05_01
	
	// Enable/disable anisotropic filter.
	if (m_useAniso)
	{
		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilterMode);
	}
}
