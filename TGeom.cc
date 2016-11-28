#include "TGeom.h"

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

TGeom::TGeom()
{
	faceCounter = 0;
}

TGeom::~TGeom()
{
}

void
TGeom::generate_terrain(std::vector<Sector>& mapData, std::vector<glm::vec4>& obj_vertices,
			  std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces,
			  std::vector<float>& vtx_temp) 
{
	int map_size = mapData.size();
	for(int i = 0; i < map_size; i++)
		generate_cube(mapData[i].position, blockSize, mapData[i].temp, obj_vertices, 
			vtx_normals, obj_faces, vtx_temp);
}

void TGeom::generate_cube(glm::vec3 start_pos, float size, float temp, std::vector<glm::vec4>& obj_vertices,
	std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp)  {

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

	for (int i = 0; i < 144; i++)
		vtx_temp.push_back(temp);
}

void TGeom::generateField(int ULCorner, int URCorner, int LLCorner, int LRCorner, std::vector<Sector> &blocks, int dim) {
	// Variables to hold indices of specific blocks, done for readability

	int l_mid;
	int r_mid;
	int t_mid;
	int b_mid;
	int c_point;
	if (dim > 1) {
		// Create the Left mid-point
		blocks.push_back(Sector());
		blocks.back().position = (blocks[ULCorner].position + blocks[LLCorner].position) / 2.0f;
		blocks.back().temp = (blocks[ULCorner].temp + blocks[LLCorner].temp) / 2.0f;
		blocks.back().alt = ceil((blocks[ULCorner].alt + blocks[LLCorner].alt) / 2.0f);
		blocks.back().id = blocks.size() - 1;
		l_mid = blocks.back().id;


		// Create the right mid-point
		blocks.push_back(Sector());
		blocks.back().position = (blocks[URCorner].position + blocks[LRCorner].position) / 2.0f;
		blocks.back().temp = (blocks[URCorner].temp + blocks[LRCorner].temp) / 2.0f;
		blocks.back().alt = ceil((blocks[URCorner].alt + blocks[LRCorner].alt) / 2.0f);
		blocks.back().id = blocks.size() - 1;
		r_mid = blocks.back().id;

		// Create the top mid-point
		blocks.push_back(Sector());
		blocks.back().position = (blocks[ULCorner].position + blocks[URCorner].position) / 2.0f;
		blocks.back().temp = (blocks[ULCorner].temp + blocks[URCorner].temp) / 2.0f;
		blocks.back().alt = ceil((blocks[ULCorner].alt + blocks[URCorner].alt) / 2.0f);
		blocks.back().id = blocks.size() - 1;
		t_mid = blocks.back().id;

		// Create the bottom mid-point
		blocks.push_back(Sector());
		blocks.back().position = (blocks[LLCorner].position + blocks[LRCorner].position) / 2.0f;
		blocks.back().temp = (blocks[LLCorner].temp + blocks[LRCorner].temp) / 2.0f;
		blocks.back().alt = ceil((blocks[LLCorner].alt + blocks[LRCorner].alt) / 2.0f);
		blocks.back().id = blocks.size() - 1;
		b_mid = blocks.back().id;

		// Create the center point
		blocks.push_back(Sector());
		blocks.back().position = (blocks[LLCorner].position + blocks[URCorner].position) / 2.0f;
		blocks.back().temp = (blocks[LLCorner].temp + blocks[URCorner].temp) / 2.0f;
		blocks.back().alt = ceil((blocks[LLCorner].alt + blocks[URCorner].alt) / 2.0f);
		blocks.back().id = blocks.size() - 1;
		c_point = blocks.back().id;

		// Now repeat recursively
		generateField(ULCorner, t_mid, l_mid, c_point, blocks, dim - 1);
		generateField(t_mid, URCorner, c_point, r_mid, blocks, dim - 1);
		generateField(l_mid, c_point, LLCorner, b_mid, blocks, dim - 1);
		generateField(c_point, r_mid, b_mid, LRCorner, blocks, dim - 1);
	}
}
