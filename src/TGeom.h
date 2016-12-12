#ifndef TGeom_H
#define TGeom_H
#define _CRT_SECURE_NO_DEPRECATE
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <GL/glew.h>
#define TEX_AMT 14
struct Sector {
	enum {
		T_BEDROCK, T_GRASS, T_GRAVEL, T_ICE, T_ICE_GRASS,
		T_JUNGLE, T_MUD, T_ROCK, T_ICE_ROCK, T_SAND,
		T_SCRUB, T_SNOW, T_TREE, T_UNDERGROUND
	};
	glm::vec3 position;
	int alt;
	float temp;
	bool discovered = false;
	glm::vec3 topRightNormal;
	glm::vec3 topLeftNormal;
	int texture;
	void setTexture();
};

class TGeom {
public:
	enum {
		T_BEDROCK, T_GRASS, T_GRAVEL, T_ICE, T_ICE_GRASS,
		T_JUNGLE, T_MUD, T_ROCK, T_ICE_ROCK, T_SAND,
		T_SCRUB, T_SNOW, T_TREE, T_UNDERGROUND
	};
	std::vector<glm::vec2> tex_coords = { glm::vec2(0, 0.666667), glm::vec2(0.2, 0.666667), glm::vec2(0.4, 0.666667), glm::vec2(0.6, 0.666667), glm::vec2(0.81, 0.666667),
		glm::vec2(0, 0.333333), glm::vec2(0.2, 0.333333), glm::vec2(0.4, 0.333333), glm::vec2(0.6, 0.333333), glm::vec2(0.8, 0.333333),
		glm::vec2(0, 0), glm::vec2(0.21, 0), glm::vec2(0.41, 0), glm::vec2(0.61, 0) };
	int current_dim = -1;
	int current_alt = -1;
	int current_den = -1;
	float min_alt = 10000.f;
	std::vector<std::vector<float>> tempData;
	std::vector<std::vector<float>> altData;
	std::vector<std::vector<Sector>> blocks;
	std::vector<std::vector<Sector>> smallBlocks;
	int tempMax = 100;
	float blockSize = 0.32f;
	TGeom();
	~TGeom();
	void generate_terrain(std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces,
		std::vector<float>& vtx_temp, std::vector<glm::vec2> &vtx_uv);
	void generate_noise(int dim, int altMax, int density);
	void generate_trimesh(std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp, std::vector<glm::vec2> &vtx_uv);
	void generate_water(std::vector<glm::vec4>& obj_vertices, std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, float t);
	void subDivide();
	Sector average(Sector original, Sector neighbor, char dir);
	Sector backPlant(Sector original, Sector neighbor, char dir);

private:
	void loadNewTexture(const char* imagepath);
	void perlin_field(glm::uvec2 ULCorner, glm::uvec2 URCorner, glm::uvec2 LLCorner, glm::uvec2 LRCorner,
		std::vector<std::vector<float>> &data, int recurse, int density);
	void generate_cube(glm::vec3 start_pos, float size, float temp, std::vector<glm::vec4>& obj_vertices,
		std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp,
		std::vector<glm::vec2> &vtx_uv, int texID);
	int faceCounter;

};

#endif