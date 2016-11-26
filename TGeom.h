#ifndef TGeom_H
#define TGeom_H
#define _CRT_SECURE_NO_DEPRECATE
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
struct Sector {
	glm::vec3 position;
	int id;
	float temp;
};

class TGeom {
public:
	TGeom();
	~TGeom();
	void generate_terrain(std::vector<Sector>& mapData, std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces,
		std::vector<float>& vtx_temp);

	void generate_cube(glm::vec3 start_pos, float size, float temp, std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp);

	void generateField(int ULCorner, int URCorner, int LLCorner, int LRCorner, std::vector<Sector> &blocks, int dim);
private:
	int faceCounter;
	float blockSize = 0.16;
};

#endif
