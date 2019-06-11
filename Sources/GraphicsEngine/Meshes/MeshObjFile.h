#pragma once
#include "Mesh.h"
#include <vector>
#include "GraphicsEngine/Vector3.h"
#include <iostream>

class MeshObjFile : public Mesh
{
public:
	MeshObjFile(const char * filepath);

	virtual void Init();
	virtual void Deinit();

private:

	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector4> colors;
	std::vector<Vector3> uvs;
	std::vector<int> indices;

	std::string m_filepath;

	void loadObj(std::istream& in);

	inline void loadVertice(std::istream& in);
	inline void loadNormal(std::istream& in);
	inline void loadUV(std::istream& in);
	inline void loadIndexes(std::istream& in);
};
