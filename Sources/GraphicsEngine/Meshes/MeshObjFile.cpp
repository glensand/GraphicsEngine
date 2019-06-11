#include "MeshObjFile.h"
#include "GraphicsEngine/Application.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::ofstream out("out.txt");

MeshObjFile::MeshObjFile(const char * filepath)
{
	m_filepath = Application::Instance().GetDataDirectory() + "/" + filepath;

}

void MeshObjFile::Init()
{
	Mesh::Init();

	std::ifstream in(m_filepath);
	loadObj(in);
	in.close();
	out.close();
}

void MeshObjFile::Deinit()
{
	Mesh::Deinit();
}

void MeshObjFile::loadObj(std::istream& in)
{
	std::string empty;
	std::string type;

	while (in >> type) {

		if (type == "v") {
			loadVertice(in);
			continue;
		}
		
		if (type == "vn") {
			loadNormal(in);
			continue;
		}
		
		if (type == "vt") {
			loadUV(in);
			continue;
		}

		if (type == "f") {
			loadIndexes(in);
			continue;
		}

//		std::getline(in, empty);
	}

	meshImpl->SetVertices(vertices);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uvs);
	meshImpl->SetColors(colors);

	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_LIST);

	meshImpl->Apply();
}

inline void MeshObjFile::loadVertice(std::istream& in)
{
	float x{}, y{}, z{};
	in >> x >> y >> z;
	vertices.emplace_back(x, y, z);

	Vector3 v = vertices.back();
	out << "v " << v.x << " " << v.y << " " << v.z << std::endl;
}

inline void MeshObjFile::loadNormal(std::istream& in)
{
	float x{}, y{}, z{};
	in >> x >> y >> z;
	normals.emplace_back(x, y, z);
}

inline void MeshObjFile::loadUV(std::istream& in)
{
	float x{}, y{};
	in >> x >> y;

	uvs.emplace_back(x, y, 0.0f);

}

inline void MeshObjFile::loadIndexes(std::istream& in)
{
	int v{}, n{}, t{};
	char sl{};
	for (size_t i = 0; i < 3; i++) {
		in >> v >> sl >> t  >> sl >> n;
		indices.emplace_back(v - 1);

	}
}
