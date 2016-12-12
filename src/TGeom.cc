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
	std::vector<float>& vtx_temp, std::vector<glm::vec2> &vtx_uv)
{
	for (unsigned i = 0; i < blocks.size(); i++)
		for (unsigned j = 0; j < blocks[i].size(); j++) {
			generate_cube(blocks[i][j].position, blockSize, blocks[i][j].temp, obj_vertices,
				vtx_normals, obj_faces, vtx_temp, vtx_uv, blocks[i][j].texture);
			//std::cout << blocks[i][j].position.x << "\t" << blocks[i][j].position.y << "\t" << blocks[i][j].position.z << "\n";
		}
}

void TGeom::generate_cube(glm::vec3 start_pos, float size, float temp, std::vector<glm::vec4>& obj_vertices,
	std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp,
	std::vector<glm::vec2> &vtx_uv, int texID) {

	float hSize = size / 2.0;
	float minU = tex_coords[texID].x;
	float minV = tex_coords[texID].y;
	float maxU = minU + 0.19;
	float maxV = minV + 0.32333;

	//F1 T1 (wall orthogonal to z-axis @ z = -1)
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F1 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, maxV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F2 T1 (wall orthogonal to z-axis @ z = 1)
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F2 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, maxV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F3 T1
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F3 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, maxV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F4 T1
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F4 T2
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, maxV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F5 T1
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F5 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, maxV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F6 T1
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

	//F6 T2
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	obj_vertices.push_back(glm::vec4(-hSize + start_pos.x, -hSize + start_pos.y, hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(maxU, maxV));
	obj_vertices.push_back(glm::vec4(hSize + start_pos.x, -hSize + start_pos.y, -hSize + start_pos.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vtx_uv.push_back(glm::vec2(minU, maxV));

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

	for (int i = 0; i < 36; i++)
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
	glm::uvec2 URCorner = glm::uvec2(0, dim - 1);
	glm::uvec2 LLCorner = glm::uvec2(dim - 1, 0);
	glm::uvec2 LRCorner = glm::uvec2(dim - 1, dim - 1);

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
	perlin_field(ULCorner, URCorner, LLCorner, LRCorner, tempData, dim >> 1, glm::clamp(density - 2, 0, 100));
	perlin_field(ULCorner, URCorner, LLCorner, LRCorner, altData, dim >> 1, density);

	// Load in texture map 
	loadNewTexture("../../textures/texmap.bmp");

	// fill blocks array using calculated temperatures and altitudes
	int halfDim = dim >> 1;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			blocks[i][j].alt = ceil(altData[i][j] * (altMax << 1) - altMax);
			blocks[i][j].position = glm::vec3((j - halfDim)*blockSize, blocks[i][j].alt*blockSize, (i - halfDim)*blockSize);
			blocks[i][j].temp = tempData[i][j] * tempMax;
			blocks[i][j].temp -= fabs(blocks[i][j].alt * 2.5);
			blocks[i][j].setTexture();
		}
	}
}

void TGeom::generate_trimesh(std::vector<glm::vec4>& obj_vertices,
	std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp, std::vector<glm::vec2> &vtx_uv) {
	int numblocks = blocks[0].size();
	int numVisited = numblocks + 2;
	std::vector<std::vector<bool>> visited(numVisited, std::vector<bool>(numVisited, false));

	for (int i = 0; i < numVisited; ++i)
	{
		visited[0][i] = true;
		visited[i][0] = true;
		visited[numblocks + 1][i] = true;
		visited[i][numblocks + 1] = true;
	}

	for (int r = 0; r < numblocks; ++r)
	{
		for (int c = 0; c < numblocks; ++c)
		{
			glm::vec3 upperRight = blocks[r][c].position;
			upperRight.x = upperRight.x + blockSize / 2;
			upperRight.y = upperRight.y + blockSize / 2;
			upperRight.z = upperRight.z - blockSize / 2;

			glm::vec3 upperLeft = blocks[r][c].position;
			upperLeft.x = upperLeft.x - blockSize / 2;
			upperLeft.y = upperLeft.y + blockSize / 2;
			upperLeft.z = upperLeft.z - blockSize / 2;

			glm::vec3 bottomRight = blocks[r][c].position;
			bottomRight.x = bottomRight.x + blockSize / 2;
			bottomRight.y = bottomRight.y + blockSize / 2;
			bottomRight.z = bottomRight.z + blockSize / 2;

			glm::vec3 bottomLeft = blocks[r][c].position;
			bottomLeft.x = bottomLeft.x - blockSize / 2;
			bottomLeft.y = bottomLeft.y + blockSize / 2;
			bottomLeft.z = bottomLeft.z + blockSize / 2;

			float leftCubeY;
			if (!visited[r + 1][c]) leftCubeY = blocks[r][c - 1].position.y + blockSize / 2;
			else leftCubeY = upperLeft.y;

			float upCubeY;
			if (!visited[r][c + 1]) upCubeY = blocks[r - 1][c].position.y + blockSize / 2;
			else upCubeY = upperRight.y;

			float downCubeY;
			if (!visited[r + 2][c + 1]) downCubeY = blocks[r + 1][c].position.y + blockSize / 2;
			else downCubeY = bottomRight.y;

			float upLeftCubeY;
			if (!visited[r][c]) upLeftCubeY = blocks[r - 1][c - 1].position.y + blockSize / 2;
			else upLeftCubeY = upperLeft.y;

			float upRightCubeY;
			if (!visited[r][c + 2]) upRightCubeY = blocks[r - 1][c + 1].position.y + blockSize / 2;
			else upRightCubeY = upperRight.y;

			float downLeftCubeY;
			if (!visited[r + 2][c]) downLeftCubeY = blocks[r + 1][c - 1].position.y + blockSize / 2;
			else downLeftCubeY = bottomLeft.y;

			float downRightCubeY;
			if (!visited[r + 2][c + 2]) downRightCubeY = blocks[r + 1][c + 1].position.y + blockSize / 2;
			else downRightCubeY = bottomRight.y;

			float rightCubeY;
			if (!visited[r + 1][c + 2]) rightCubeY = blocks[r][c + 1].position.y + blockSize / 2;
			else rightCubeY = upperRight.y;

			upperRight.y = std::max(upperRight.y, std::max(upCubeY, std::max(upRightCubeY, rightCubeY)));

			upperLeft.y = std::max(upperLeft.y, std::max(leftCubeY, std::max(upLeftCubeY, upCubeY)));

			bottomRight.y = std::max(bottomRight.y, std::max(downCubeY, std::max(downRightCubeY, rightCubeY)));

			bottomLeft.y = std::max(bottomLeft.y, std::max(leftCubeY, std::max(downLeftCubeY, downCubeY)));

			if (upperRight.y == upperLeft.y && upperLeft.y == bottomRight.y && bottomRight.y == bottomLeft.y)
				blocks[r][c].position.y = upperLeft.y - blockSize / 2;

			//left triangle of top face
			obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
			obj_vertices.push_back(glm::vec4(bottomLeft, 1.0f));
			obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
			//right triangle of top face
			obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
			obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
			obj_vertices.push_back(glm::vec4(upperRight, 1.0f));

			float minU = tex_coords[blocks[r][c].texture].x;
			float minV = tex_coords[blocks[r][c].texture].y;
			float maxU = minU + 0.19;
			float maxV = minV + 0.32;
			vtx_uv.push_back(glm::vec2(maxU, minV));
			vtx_uv.push_back(glm::vec2(minU, minV));
			vtx_uv.push_back(glm::vec2(minU, maxV));
			vtx_uv.push_back(glm::vec2(maxU, minV));
			vtx_uv.push_back(glm::vec2(minU, maxV));
			vtx_uv.push_back(glm::vec2(maxU, maxV));


			//average the normals of all triangles that share a vertex in order to obtain the normal at that vertex
			glm::vec3 U = (bottomLeft - bottomRight);
			glm::vec3 V = (upperLeft - bottomRight);
			glm::vec3 normal;
			normal.x = (U.y * V.z) - (U.z * V.z);
			normal.y = (U.z * V.x) - (U.x * V.z);
			normal.z = (U.x * V.y) - (U.y * V.x);
			blocks[r][c].topLeftNormal = glm::normalize(normal);

			U = (upperLeft - bottomRight);
			V = (upperRight - bottomRight);
			normal.x = (U.y * V.z) - (U.z * V.z);
			normal.y = (U.z * V.x) - (U.x * V.z);
			normal.z = (U.x * V.y) - (U.y * V.x);
			blocks[r][c].topRightNormal = glm::normalize(normal);

			obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
			obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));

			if (r == 0) {
				obj_vertices.push_back(glm::vec4(glm::vec3(upperLeft.x, min_alt, upperLeft.z), 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(upperRight.x, min_alt, upperRight.z), 1.0f));
				obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(upperRight.x, min_alt, upperRight.z), 1.0f));
				obj_vertices.push_back(glm::vec4(upperRight, 1.0f));
				obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
				minU = tex_coords[T_UNDERGROUND].x;
				minV = tex_coords[T_UNDERGROUND].y;
				maxU = minU + 0.19;
				maxV = minV + 0.32;
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, maxV));
			}
			if (c == 0) {
				obj_vertices.push_back(glm::vec4(glm::vec3(bottomLeft.x, min_alt, bottomLeft.z), 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(upperLeft.x, min_alt, upperLeft.z), 1.0f));
				obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
				obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
				obj_vertices.push_back(glm::vec4(bottomLeft, 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(bottomLeft.x, min_alt, bottomLeft.z), 1.0f));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
				minU = tex_coords[T_UNDERGROUND].x;
				minV = tex_coords[T_UNDERGROUND].y;
				maxU = minU + 0.19;
				maxV = minV + 0.32;
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, maxV));
			}
			if (r == numblocks - 1) {
				obj_vertices.push_back(glm::vec4(glm::vec3(bottomRight.x, min_alt, bottomRight.z), 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(bottomLeft.x, min_alt, bottomLeft.z), 1.0f));
				obj_vertices.push_back(glm::vec4(bottomLeft, 1.0f));
				obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(bottomRight.x, min_alt, bottomRight.z), 1.0f));
				obj_vertices.push_back(glm::vec4(bottomLeft, 1.0f));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
				minU = tex_coords[T_UNDERGROUND].x;
				minV = tex_coords[T_UNDERGROUND].y;
				maxU = minU + 0.19;
				maxV = minV + 0.32;
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, maxV));
			}
			if (c == numblocks - 1) {
				obj_vertices.push_back(glm::vec4(glm::vec3(upperRight.x, min_alt, upperRight.z), 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(bottomRight.x, min_alt, bottomRight.z), 1.0f));
				obj_vertices.push_back(glm::vec4(upperRight, 1.0f));
				obj_vertices.push_back(glm::vec4(glm::vec3(bottomRight.x, min_alt, bottomRight.z), 1.0f));
				obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
				obj_vertices.push_back(glm::vec4(upperRight, 1.0f));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
				obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
				minU = tex_coords[T_UNDERGROUND].x;
				minV = tex_coords[T_UNDERGROUND].y;
				maxU = minU + 0.19;
				maxV = minV + 0.32;
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, minV));
				vtx_uv.push_back(glm::vec2(minU, maxV));
				vtx_uv.push_back(glm::vec2(maxU, maxV));
			}
		}
	}

	for (int r = 0; r < numblocks; r++)
	{
		for (int c = 0; c < numblocks; c++)
		{
			glm::vec3 bln = blocks[r][c].topLeftNormal;
			glm::vec3 brn = blocks[r][c].topLeftNormal + blocks[r][c].topRightNormal;
			glm::vec3 uln = blocks[r][c].topLeftNormal + blocks[r][c].topRightNormal;
			glm::vec3 urn = blocks[r][c].topRightNormal;
			float upLeftTemp = blocks[r][c].temp;
			float upRightTemp = blocks[r][c].temp;
			float bottomLeftTemp = blocks[r][c].temp;
			float bottomRightTemp = blocks[r][c].temp;
			int ulc = 1;
			int urc = 1;
			int blc = 1;
			int brc = 1;

			if (!visited[r + 1][c]) {
				bln = bln + blocks[r][c - 1].topLeftNormal + blocks[r][c - 1].topRightNormal;
				uln = uln + blocks[r][c - 1].topRightNormal;
				upLeftTemp = upLeftTemp + blocks[r][c - 1].temp;
				bottomLeftTemp = bottomLeftTemp + blocks[r][c - 1].temp;
				++blc;
				++ulc;
			}
			if (!visited[r][c + 1]) {
				urn = urn + blocks[r - 1][c].topLeftNormal + blocks[r - 1][c].topRightNormal;
				uln = uln + blocks[r - 1][c].topLeftNormal;
				upRightTemp = upRightTemp + blocks[r - 1][c].temp;
				upLeftTemp = upLeftTemp + blocks[r - 1][c].temp;
				++urc;
				++ulc;
			}

			if (!visited[r + 2][c + 1]) {
				bln = bln + blocks[r + 1][c].topLeftNormal + blocks[r + 1][c].topRightNormal;
				brn = brn + blocks[r + 1][c].topRightNormal;
				bottomLeftTemp = bottomLeftTemp + blocks[r + 1][c].temp;
				bottomRightTemp = bottomRightTemp + blocks[r + 1][c].temp;
				++blc;
				++brc;
			}

			if (!visited[r][c]) {
				uln = uln + blocks[r - 1][c - 1].topRightNormal + blocks[r - 1][c - 1].topLeftNormal;
				upLeftTemp = upLeftTemp + blocks[r - 1][c - 1].temp;
				++ulc;
			}

			if (!visited[r][c + 2]) {
				urn = urn + blocks[r - 1][c + 1].topLeftNormal;
				upRightTemp = upRightTemp + blocks[r - 1][c + 1].temp;
				++urc;
			}

			if (!visited[r + 2][c]) {
				bln = bln + blocks[r + 1][c - 1].topRightNormal;
				bottomLeftTemp = bottomLeftTemp + blocks[r + 1][c - 1].temp;
				++blc;
			}

			if (!visited[r + 2][c + 2]) {
				brn = brn + blocks[r + 1][c + 1].topRightNormal + blocks[r + 1][c + 1].topLeftNormal;
				bottomRightTemp = bottomRightTemp + blocks[r + 1][c + 1].temp;
				++brc;
			}

			if (!visited[r + 1][c + 2]) {
				urn = urn + blocks[r][c + 1].topLeftNormal + blocks[r][c + 1].topRightNormal;
				brn = brn + blocks[r][c + 1].topLeftNormal;
				upRightTemp = upRightTemp + blocks[r][c + 1].temp;
				bottomRightTemp = bottomRightTemp + blocks[r][c + 1].temp;
				++urc;
				++brc;
			}
			upLeftTemp = upLeftTemp / ulc;
			upRightTemp = upRightTemp / urc;
			bottomLeftTemp = bottomLeftTemp / blc;
			bottomRightTemp = bottomRightTemp / brc;

			glm::normalize(bln);
			glm::normalize(uln);
			glm::normalize(brn);
			glm::normalize(urn);

			vtx_normals.push_back(glm::vec4(brn, 0.f));
			vtx_normals.push_back(glm::vec4(bln, 0.f));
			vtx_normals.push_back(glm::vec4(uln, 0.f));
			vtx_normals.push_back(glm::vec4(brn, 0.f));
			vtx_normals.push_back(glm::vec4(uln, 0.f));
			vtx_normals.push_back(glm::vec4(urn, 0.f));
			vtx_temp.push_back(bottomRightTemp);
			vtx_temp.push_back(bottomLeftTemp);
			vtx_temp.push_back(upLeftTemp);
			vtx_temp.push_back(bottomRightTemp);
			vtx_temp.push_back(upLeftTemp);
			vtx_temp.push_back(upRightTemp);

			if (r == 0) {
				for (int i = 0; i < 6; i++)
				{
					vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
					vtx_temp.push_back(blocks[r][c].temp);
				}
			}
			if (c == 0) {
				for (int i = 0; i < 6; i++)
				{
					vtx_normals.push_back(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
					vtx_temp.push_back(blocks[r][c].temp);
				}
			}
			if (r == numblocks - 1) {
				for (int i = 0; i < 6; i++)
				{
					vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
					vtx_temp.push_back(blocks[r][c].temp);
				}
			}
			if (c == numblocks - 1) {
				for (int i = 0; i < 6; i++)
				{
					vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
					vtx_temp.push_back(blocks[r][c].temp);
				}
			}
		}
	}

	//Lowerplane
	//upper left
	obj_vertices.push_back(glm::vec4(glm::vec3(blocks[0][0].position.x - blockSize / 2, min_alt, blocks[0][0].position.z - blockSize / 2), 1.0f));
	//lower left
	obj_vertices.push_back(glm::vec4(glm::vec3(blocks[numblocks - 1][0].position.x - blockSize / 2, min_alt, blocks[numblocks - 1][0].position.z + blockSize / 2), 1.0f));
	//upper right
	obj_vertices.push_back(glm::vec4(glm::vec3(blocks[0][numblocks - 1].position.x + blockSize / 2, min_alt, blocks[0][numblocks - 1].position.z - blockSize / 2), 1.0f));
	//lower left
	obj_vertices.push_back(glm::vec4(glm::vec3(blocks[numblocks - 1][0].position.x - blockSize / 2, min_alt, blocks[numblocks - 1][0].position.z + blockSize / 2), 1.0f));
	//lower right 
	obj_vertices.push_back(glm::vec4(glm::vec3(blocks[numblocks - 1][numblocks - 1].position.x + blockSize / 2, min_alt, blocks[numblocks - 1][numblocks - 1].position.z + blockSize / 2), 1.0f));
	//upper right
	obj_vertices.push_back(glm::vec4(glm::vec3(blocks[0][numblocks - 1].position.x + blockSize / 2, min_alt, blocks[0][numblocks - 1].position.z - blockSize / 2), 1.0f));
	float minU = tex_coords[T_BEDROCK].x;
	float minV = tex_coords[T_BEDROCK].y;
	float maxU = minU + 0.19;
	float maxV = minV + 0.32;
	vtx_uv.push_back(glm::vec2(maxU, minV));
	vtx_uv.push_back(glm::vec2(minU, minV));
	vtx_uv.push_back(glm::vec2(minU, maxV));
	vtx_uv.push_back(glm::vec2(maxU, minV));
	vtx_uv.push_back(glm::vec2(minU, maxV));
	vtx_uv.push_back(glm::vec2(maxU, maxV));
	for (int i = 0; i < 6; i++)
	{
		vtx_normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
		vtx_temp.push_back(40.f);
	}
	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
}

#define WATER_POS glm::vec4(x_pos, (sin(15*x_pos) * cos(10*z_pos)*t*sinConst + sin(5*z_pos) * cos(5*x_pos)*t*sinConst*2), z_pos, 1.0f)
void TGeom::generate_water(std::vector<glm::vec4>& obj_vertices, std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, float t) {
	obj_vertices.clear();
	vtx_normals.clear();
	obj_faces.clear();
	// Use the blocks vector to get the initial position
	int i = 0; // init loop variable
	int j = 0; // init loop variable
	int len_i; // loop end condition
	int len_j; // loop end condition
	float offset = blockSize / 2; // offset used to position vertices
	float sinConst = 0.002; // multiplied by the wave vertices to make them smoother
	int index = 0; // index used to help keep track of face numbers
	float blk_x; // used to store the position of the block's x coordinate
	float blk_z; // used to store the position of the block's y coordinate
	float x_pos; // used to store the x position for our vertex
	float z_pos; // used to store the z position for our vertex

				 // Create a reference vector so we don't end up with overlapping vertices
	int set[256][256] = { -1 };
	len_i = blocks.size() + 1;
	len_j = blocks.size() + 1;
	for (i; i < len_i; i++) {
		for (j; j < len_j; j++) {
			set[i][j] = -1;
		}
		j = 0;
	}

	// Reset loop variable and set up end condition for loop here
	len_i = blocks.size();
	len_j = blocks.back().size();
	i = 0;
	j = 0;
	for (i; i < len_i; i++) {
		for (j; j < len_j; j++) {
			// grab the position of the block we're on
			blk_x = blocks[i][j].position.x;
			blk_z = blocks[i][j].position.z;

			// Push the Upper Left Corner if it doesn't exist
			if (set[i][j] == -1) {
				x_pos = -offset + blk_x + 0.01f;
				z_pos = -offset + blk_z + 0.01f;
				set[i][j] = index;
				index++;
				obj_vertices.push_back(WATER_POS);
				vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			}

			// Push the Lower Left Corner if it doesn't exist
			if (set[i + 1][j] == -1) {
				x_pos = -offset + blk_x + 0.01f;
				z_pos = offset + blk_z - 0.01f;
				set[i + 1][j] = index;
				index++;
				obj_vertices.push_back(WATER_POS);
				vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			}
			// Push the Lower Right Corner if it doesn't exist
			if (set[i + 1][j + 1] == -1) {
				x_pos = offset + blk_x - 0.01f;
				z_pos = offset + blk_z - 0.01f;
				set[i + 1][j + 1] = index;
				index++;
				obj_vertices.push_back(WATER_POS);
				vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			}
			// Push the Upper Right Corner if it doesn't exist
			if (set[i][j + 1] == -1) {
				x_pos = offset + blk_x - 0.01f;
				z_pos = -offset + blk_z + 0.01f;
				set[i][j + 1] = index;
				index++;
				obj_vertices.push_back(WATER_POS);
				vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			}
			x_pos = blk_x;
			z_pos = blk_z;
			// Push the midpoint, these will never overlap so no check is needed
			obj_vertices.push_back(WATER_POS);
			vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

			// Push our faces using the stored indices
			obj_faces.push_back(glm::uvec3(index, set[i][j + 1], set[i][j]));
			obj_faces.push_back(glm::uvec3(index, set[i + 1][j + 1], set[i][j + 1]));
			obj_faces.push_back(glm::uvec3(index, set[i + 1][j], set[i + 1][j + 1]));
			obj_faces.push_back(glm::uvec3(index, set[i][j], set[i + 1][j]));
			index++;
		}
		j = 0;
	}
	i = 0;

	// Calculate The Face Normals
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 C;
	glm::vec4 Norm;
	len_i = obj_faces.size();
	for (i; i < len_i; i++) {
		A = glm::vec3(obj_vertices[obj_faces[i].x]);
		B = glm::vec3(obj_vertices[obj_faces[i].y]);
		C = glm::vec3(obj_vertices[obj_faces[i].z]);
		Norm = glm::vec4(glm::normalize((B - C)*(C - A)), 0.0f);
		vtx_normals[obj_faces[i].x] += Norm;
		vtx_normals[obj_faces[i].y] += Norm;
		vtx_normals[obj_faces[i].z] += Norm;
	}
	i = 0;
	len_i = vtx_normals.size();
	for (i; i < len_i; i++) {
		vtx_normals[i] = glm::normalize(vtx_normals[i]);
		if (vtx_normals[i].y < 0) {
			vtx_normals[i] = -vtx_normals[i];
		}
		vtx_normals[i].w = 1.0f;
	}
}

void TGeom::subDivide() {
	min_alt = 10000.f;
	smallBlocks = std::vector<std::vector<Sector>>(blocks.size() * 2, std::vector<Sector>(blocks.size() * 2));
	for (unsigned i = 0; i < blocks.back().size(); i++)
		for (unsigned j = 0; j < blocks.back().size(); j++) {
			Sector smallOrig = blocks[i][j];
			smallOrig.discovered = false;
			smallBlocks[2 * i + 1][2 * j + 1] = smallOrig;
			if (i == 0 && j == 0) {
				smallBlocks[2 * i + 1][2 * j] = backPlant(blocks[i][j], blocks[i][j + 1], '2');
				smallBlocks[2 * i][2 * j + 1] = backPlant(blocks[i][j], blocks[i + 1][j], '3');
			}
			else if (i == 0) {
				smallBlocks[2 * i + 1][2 * j] = backPlant(blocks[i][j], blocks[i + 1][j], '2');
				smallBlocks[2 * i][2 * j + 1] = average(blocks[i][j], blocks[i][j - 1], '3');
			}
			else if (j == 0) {
				smallBlocks[2 * i + 1][2 * j] = average(blocks[i][j], blocks[i - 1][j], '2');
				smallBlocks[2 * i][2 * j + 1] = backPlant(blocks[i][j], blocks[i][j + 1], '3');
			}
			else {
				smallBlocks[2 * i + 1][2 * j] = average(blocks[i][j], blocks[i][j - 1], '2');
				smallBlocks[2 * i][2 * j + 1] = average(blocks[i][j], blocks[i - 1][j], '3');
			}
			smallBlocks[2 * i][2 * j] = average(smallBlocks[2 * i + 1][2 * j], smallBlocks[2 * i][2 * j + 1], '1');
		}
	int newDim = smallBlocks.back().size();
	int halfDim = newDim / 2;
	float qSize = blockSize / 2;
	for (int i = -halfDim; i < halfDim; i++)
		for (int j = -halfDim; j < halfDim; j++)
		{
			smallBlocks[j + halfDim][i + halfDim].position.x = i*qSize;
			smallBlocks[j + halfDim][i + halfDim].position.z = j*qSize;
			smallBlocks[j + halfDim][i + halfDim].position.y = smallBlocks[j + halfDim][i + halfDim].alt * (blockSize / 2.0f);
		}

	blocks = smallBlocks;
	blockSize /= 2.0f;
	for (unsigned i = 0; i < blocks.size(); ++i)
	{
		for (unsigned j = 0; j < blocks[0].size(); ++j)
		{
			if (min_alt > blocks[i][j].alt*blockSize) min_alt = blocks[i][j].alt*blockSize;
		}
	}
}

Sector TGeom::average(Sector original, Sector neighbor, char dir) {
	Sector ret = Sector();
	ret.position = glm::vec3(0.0, 0.0, 0.0);
	ret.position.y = (original.position.y + neighbor.position.y) / 2.0f;
	ret.temp = (original.temp + neighbor.temp) / 2.0f;
	ret.alt = (original.alt + neighbor.alt) / 2;
	ret.discovered = false;
	ret.position.y = ret.alt * blockSize;
	ret.setTexture();
	return ret;

}

Sector TGeom::backPlant(Sector original, Sector neighbor, char dir) {
	Sector ret = Sector();
	ret.position = glm::vec3(0.0, 0.0, 0.0);
	ret.position.y = 2 * original.position.y - ((original.position.y + neighbor.position.y) / 2.0f);
	ret.temp = 2 * original.temp - ((original.temp + neighbor.temp) / 2.0f);
	ret.alt = 2 * original.alt - ((original.alt + neighbor.alt) / 2);
	ret.discovered = false;
	ret.position.y = ret.alt * blockSize;
	ret.setTexture();
	return ret;

}

void TGeom::loadNewTexture(const char* imagepath) {
	unsigned char header[54]; // Each BMP file begins with a 54-byte header
	unsigned int dataPos;	  // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize; // = width*height
	unsigned char* data; // the actual data for the image
	GLuint texID; // our texture object to return
	texID = 0;
	FILE* file = fopen(imagepath, "rb");

	// This is here for debugging
	if (!file) {
		std::cout << "image failed to load!\n";
		system("Pause");
	}

	if ((fread(header, 1, 54, file) != 54) || (header[0] != 'B' && header[1] != 'M')) {
		std::cout << "image is not .bmp or is corrupted\n";
		system("Pause");
	}

	// Get information about the image from the header
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// This is here to ensure image is set up correctly (in case header information 
	// is missing or corrupted and was not caught by debug statements)
	if (imageSize == 0) {
		imageSize = width*height * 3;
	}
	if (dataPos == 0) {
		dataPos = 54; // Start reading after the header
	}

	// read data and close the file
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	// Load in our texture to our texture object
	glGenTextures(1, &texID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Sector::setTexture() {
	if (alt < 0) {
		if (temp <= 20) {
			texture = T_ICE;
		}
		else if (temp <= 40) {
			texture = T_GRAVEL;
		}
		else if (temp <= 60) {
			texture = T_MUD;
		}
		else {
			texture = T_SAND;
		}
	}
	else if (alt >= 4) {
		if (temp <= 20) {
			texture = T_SNOW;
		}
		else if (temp <= 32) {
			texture = T_ICE_ROCK;
		}
		else {
			texture = T_ROCK;
		}
	}
	else {
		if (temp <= 20) {
			texture = T_ICE;
		}
		else if (temp <= 32) {
			texture = T_SNOW;
		}
		else if (temp <= 40) {
			texture = T_ICE_GRASS;
		}
		else if (temp <= 60) {
			texture = T_TREE;
		}
		else if (temp <= 75) {
			texture = T_GRASS;
		}
		else if (temp <= 85) {
			texture = T_JUNGLE;
		}
		else if (temp <= 90) {
			texture = T_SCRUB;
		}
		else {
			texture = T_SAND;
		}
	}
}