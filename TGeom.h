#ifndef TGeom_H
#define TGeom_H
#define _CRT_SECURE_NO_DEPRECATE
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
struct Sector {
	glm::vec3 position;
	float size;
	float temp;
};

class TGeom {
public:
	TGeom();
	~TGeom();
	void generate_terrain(std::vector<Sector>& mapData, std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces,
		std::vector<float>& vtx_temp);

	void TGeom::generate_cube(glm::vec3 start_pos, float size, float temp, std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp);
private:
	int faceCounter;
};

#endif
