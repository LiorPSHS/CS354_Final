#ifndef TGeom_H
#define TGeom_H
#define _CRT_SECURE_NO_DEPRECATE
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class TGeom {
public:
	TGeom();
	~TGeom();
	void set_nesting_level(int);
	bool is_dirty() const;
	void set_clean();
	void generate_terrain(std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals,
		std::vector<glm::uvec3>& obj_faces);

	void TGeom::generate_cube(glm::vec3 start_pos, float size, std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals,
		std::vector<glm::uvec3>& obj_faces);
private:
	int nesting_level_ = 0;
	int faceCounter = 0;
	bool dirty_ = false;
};

#endif
