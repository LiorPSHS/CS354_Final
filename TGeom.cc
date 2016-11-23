#include "TGeom.h"

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

TGeom::TGeom()
{
	// Add additional initialization if you like
}

TGeom::~TGeom()
{
}

void
TGeom::set_nesting_level(int level)
{
	nesting_level_ = level;
	dirty_ = true;
}

bool
TGeom::is_dirty() const
{
	return dirty_;
}

void
TGeom::set_clean()
{
	dirty_ = false;
	faceCounter = 0;
}

// FIXME generate TGeom sponge geometry
void
TGeom::generate_terrain(std::vector<glm::vec4>& obj_vertices,
			  std::vector<glm::vec4>& vtx_normals,
                          std::vector<glm::uvec3>& obj_faces) 
{
	float cSize = 0.32;
	float offset = cSize / 2;
	for(int i = -50; i < 50; i++) 
		for(int j = -50; j < 50; j++)
			generate_cube(glm::vec3(i*offset, -1.0f, j*offset), cSize, obj_vertices, vtx_normals, obj_faces);
}

void TGeom::generate_cube(glm::vec3 start_pos, float size, std::vector<glm::vec4>& obj_vertices,
	std::vector<glm::vec4>& vtx_normals,
	std::vector<glm::uvec3>& obj_faces)  {

	float hSize = size / 2.0;

	//F1 T1
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	//F1 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	//F2 T1
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	//F2 T2
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	//F3 T1
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

	//F3 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

	//F4 T1
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	//F4 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));

	//F5 T1
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	//F5 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	//F6 T1
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));

	//F6 T2
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));

	obj_faces.push_back(glm::uvec3(faceCounter, faceCounter + 1, faceCounter + 2));
	obj_faces.push_back(glm::uvec3(faceCounter + 3, faceCounter + 4, faceCounter + 5));
	obj_faces.push_back(glm::uvec3(faceCounter + 6, faceCounter + 7, faceCounter + 8));
	obj_faces.push_back(glm::uvec3(faceCounter + 9, faceCounter + 10, faceCounter + 11));
	obj_faces.push_back(glm::uvec3(faceCounter + 12, faceCounter + 13, faceCounter + 14));
	obj_faces.push_back(glm::uvec3(faceCounter + 15, faceCounter + 16, faceCounter + 17));
	obj_faces.push_back(glm::uvec3(faceCounter + 18, faceCounter + 19, faceCounter + 20));
	obj_faces.push_back(glm::uvec3(faceCounter + 21, faceCounter + 22, faceCounter + 23));
	obj_faces.push_back(glm::uvec3(faceCounter + 24, faceCounter + 25, faceCounter + 26));
	obj_faces.push_back(glm::uvec3(faceCounter + 27, faceCounter + 28, faceCounter + 29));
	obj_faces.push_back(glm::uvec3(faceCounter + 30, faceCounter + 31, faceCounter + 32));
	obj_faces.push_back(glm::uvec3(faceCounter + 33, faceCounter + 34, faceCounter + 35));

	faceCounter += 36;		
}
