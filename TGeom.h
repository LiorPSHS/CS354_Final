#ifndef TGeom_H
#define TGeom_H
#define _CRT_SECURE_NO_DEPRECATE
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>

struct Sector {
	glm::vec3 position;
	int alt;
	float temp;
	bool discovered = false;
	glm::vec3 topRightNormal;
	glm::vec3 topLeftNormal;
};

class TGeom {
public:
	int current_dim = -1;
	int current_alt = -1;
	int current_den = -1;
	float min_alt = 10000.f;
	std::vector<std::vector<float>> tempData;
	std::vector<std::vector<float>> altData;
	std::vector<std::vector<Sector>> blocks;
	int tempMax = 100;
	float blockSize = 0.16f;
	TGeom();
	~TGeom();
	void generate_terrain(std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces,
		std::vector<float>& vtx_temp);
	void TGeom::generate_noise(int dim, int altMax, int density);
	void generate_trimesh(std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp);
	void generate_water(std::vector<glm::vec4>& obj_vertices, std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, float t);


private:
	void TGeom::perlin_field(glm::uvec2 ULCorner, glm::uvec2 URCorner, glm::uvec2 LLCorner, glm::uvec2 LRCorner, 
							std::vector<std::vector<float>> &data, int recurse, int density);
	void generate_cube(glm::vec3 start_pos, float size, float temp, std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp);
	int faceCounter;

};

#endif
