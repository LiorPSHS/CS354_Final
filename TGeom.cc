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
TGeom::generate_terrain(std::vector<glm::vec4>& obj_vertices,
			  std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces,
			  std::vector<float>& vtx_temp) 
{
	for(int i = 0; i < blocks.size(); i++)
		for(int j = 0; j < blocks[i].size(); j++)
				generate_cube(blocks[i][j].position, blockSize, blocks[i][j].temp, obj_vertices,
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

void TGeom::perlin_field(glm::uvec2 ULCorner, glm::uvec2 URCorner, glm::uvec2 LLCorner, glm::uvec2 LRCorner, std::vector<std::vector<float>> &data, int recurse, int density) {
	if (recurse > 0) {
		srand(time(0));
		// Create variables for readability
		glm::uvec2 l_mid;
		glm::uvec2 r_mid;
		glm::uvec2 t_mid;
		glm::uvec2 b_mid;
		glm::uvec2 c_pnt;

		// create the left midpoint
		l_mid = glm::uvec2(nearbyint((ULCorner.x + LLCorner.x) / 2.0f), ULCorner.y);
		if (data[l_mid.x][l_mid.y] < 0.0) {
			if (density > 0) {
				data[l_mid.x][l_mid.y] = rand() / (float)RAND_MAX;
			}
			else {
				data[l_mid.x][l_mid.y] = (data[ULCorner.x][ULCorner.y] + data[LLCorner.x][LLCorner.y]) / 2.0f;
			}
		}

		// create the right midpoint
		r_mid = glm::uvec2(nearbyint((URCorner.x + LRCorner.x) / 2.0f), URCorner.y);
		if (data[r_mid.x][r_mid.y] < 0.0) {

			if (density > 0) {
				data[r_mid.x][r_mid.y] = rand() / (float)RAND_MAX;
			}
			else {
				data[r_mid.x][r_mid.y] = (data[URCorner.x][URCorner.y] + data[LRCorner.x][LRCorner.y]) / 2.0f;
			}
		}

		// create the top midpoint
		t_mid = glm::uvec2(ULCorner.x, nearbyint((ULCorner.y + URCorner.y) / 2.0f));
		if (data[t_mid.x][t_mid.y] < 0.0) {
			if (density > 0) {
				data[t_mid.x][t_mid.y] = rand() / (float)RAND_MAX;
			}
			else {
				data[t_mid.x][t_mid.y] = (data[ULCorner.x][ULCorner.y] + data[URCorner.x][URCorner.y]) / 2.0f;
			}
		}

		// create the bottom midpoint
		b_mid = glm::uvec2(LLCorner.x, nearbyint((LLCorner.y + LRCorner.y) / 2.0f));
		if (data[b_mid.x][b_mid.y] < 0.0) {
			if (density > 0) {
				data[b_mid.x][b_mid.y] = rand() / (float)RAND_MAX;
			}
			else {
				data[b_mid.x][b_mid.y] = (data[LLCorner.x][LLCorner.y] + data[LRCorner.x][LRCorner.y]) / 2.0f;
			}

		}

		// create the center point
		c_pnt = glm::uvec2(nearbyint((URCorner.x + LRCorner.x) / 2.0f), nearbyint((LLCorner.y + LRCorner.y) / 2.0f));
		if (data[c_pnt.x][c_pnt.y] < 0.0) {
			if (density > 0) {
				data[c_pnt.x][c_pnt.y] = rand() / (float)RAND_MAX;
			}
			else {
				data[c_pnt.x][c_pnt.y] = (data[LLCorner.x][LLCorner.y] + data[LRCorner.x][LRCorner.y] +
					data[URCorner.x][URCorner.y] + data[ULCorner.x][ULCorner.y]) / 4.0f;
			}
		}

		// Repeate function recursively
		perlin_field(ULCorner, t_mid, l_mid, c_pnt, data, recurse - 1, density - 1);
		perlin_field(t_mid, URCorner, c_pnt, r_mid, data, recurse - 1, density - 1);
		perlin_field(l_mid, c_pnt, LLCorner, b_mid, data, recurse - 1, density - 1);
		perlin_field(c_pnt, r_mid, b_mid, LRCorner, data, recurse - 1, density - 1);
	}
}

void TGeom::generate_noise(int dim, int altMax, int density) {
	current_alt = altMax;
	current_dim = dim;
	current_den = density;
	srand(time(0));
	// create some variables for readability
	glm::uvec2 ULCorner = glm::uvec2(0, 0);
	glm::uvec2 URCorner = glm::uvec2(0, dim-1);
	glm::uvec2 LLCorner = glm::uvec2(dim-1, 0);
	glm::uvec2 LRCorner = glm::uvec2(dim-1, dim-1);

	// Initalize arrays
	for (int i = 0; i < dim; i++) {
		tempData.push_back(std::vector<float>(dim));
		altData.push_back(std::vector<float>(dim));
		blocks.push_back(std::vector<Sector>(dim));
	}

	// fill tempdata and altdata with sentinal values
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			tempData[i][j] = -1.0f;
			altData[i][j] = -1.0f;
		}
	}

	// generate corner points for temperature & Altitude arrays
	for (int i = 0; i < dim; i += (dim - 1)) {
		for (int j = 0; j < dim; j += (dim - 1)) {
			altData[i][j] = rand() / (float)RAND_MAX;
			tempData[i][j] = rand() / (float)RAND_MAX;
		}
	}

	// fill temperature & altitude array with perlin function
	perlin_field(ULCorner, URCorner, LLCorner, LRCorner, tempData, dim >> 1, density);
	perlin_field(ULCorner, URCorner, LLCorner, LRCorner, altData, dim >> 1, density);
	
	// fill blocks array using calculated temperatures and altitudes
	int halfDim = dim >> 1;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			blocks[i][j].alt = ceil(altData[i][j] * (altMax << 1) - altMax);
			blocks[i][j].position = glm::vec3((j - halfDim)*blockSize, blocks[i][j].alt*blockSize, (i - halfDim)*blockSize);
			blocks[i][j].temp = tempData[i][j] * tempMax - fabs(blocks[i][j].alt * 2.5);
		}
	}
}