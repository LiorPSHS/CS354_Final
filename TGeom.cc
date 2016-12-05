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

void TGeom::generate_trimesh(std::vector<glm::vec4>& obj_vertices,
	std::vector<glm::vec4>& vtx_normals, std::vector<glm::uvec3>& obj_faces, std::vector<float>& vtx_temp) {
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
			//left triangle of bottom face
			//obj_vertices.push_back(glm::vec4(bottomRight.x, bottomRight.y - blockSize, bottomRight.z, 1.0f));
			//obj_vertices.push_back(glm::vec4(bottomLeft.x, bottomLeft.y - blockSize, bottomLeft.z, 1.0f));
			//obj_vertices.push_back(glm::vec4(upperLeft.x, upperLeft.y - blockSize, upperLeft.z, 1.0f));
			//right triangle of top face
			obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
			obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
			obj_vertices.push_back(glm::vec4(upperRight, 1.0f));
			//right triangle of bottom face
			//obj_vertices.push_back(glm::vec4(bottomRight.x, bottomRight.y - blockSize, bottomRight.z, 1.0f));
			//obj_vertices.push_back(glm::vec4(upperLeft.x, upperLeft.y - blockSize, upperLeft.z, 1.0f));
			//obj_vertices.push_back(glm::vec4(upperRight.x, upperRight.y - blockSize, upperRight.z, 1.0f));


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

			//obj_faces.push_back(glm::uvec3(obj_vertices.size() - 12, obj_vertices.size() - 11, obj_vertices.size() - 10));
			//obj_faces.push_back(glm::uvec3(obj_vertices.size() - 9, obj_vertices.size() - 8, obj_vertices.size() - 7));
			obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
			obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));

			//if (r == 0) {
			//	obj_vertices.push_back(glm::vec4(glm::vec3(upperRight.x, upperRight.y - blockSize, upperRight.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(upperLeft.x, upperLeft.y - blockSize, upperLeft.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
			//	obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
			//	obj_vertices.push_back(glm::vec4(upperRight, 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(upperRight.x, upperRight.y - blockSize, upperRight.z), 1.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
			//}
			//if (c == 0) {
			//	obj_vertices.push_back(glm::vec4(glm::vec3(bottomLeft.x, bottomLeft.y - blockSize, bottomLeft.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(upperLeft.x, upperLeft.y - blockSize, upperLeft.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
			//	obj_vertices.push_back(glm::vec4(upperLeft, 1.0f));
			//	obj_vertices.push_back(glm::vec4(bottomLeft, 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(bottomLeft.x, bottomLeft.y - blockSize, bottomLeft.z), 1.0f));
			//	vtx_normals.push_back(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));

			//}
			//if (r == numblocks - 1) {
			//	obj_vertices.push_back(glm::vec4(glm::vec3(bottomLeft.x, bottomLeft.y - blockSize, bottomLeft.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(bottomRight.x, bottomRight.y - blockSize, bottomRight.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(bottomLeft, 1.0f));
			//	obj_vertices.push_back(glm::vec4(bottomLeft, 1.0f));
			//	obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(bottomRight.x, bottomRight.y - blockSize, bottomRight.z), 1.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
			//}
			//if (c == numblocks - 1) {
			//	obj_vertices.push_back(glm::vec4(glm::vec3(upperRight.x, upperRight.y - blockSize, upperRight.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(bottomRight.x, bottomRight.y - blockSize, bottomRight.z), 1.0f));
			//	obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
			//	obj_vertices.push_back(glm::vec4(bottomRight, 1.0f));
			//	obj_vertices.push_back(glm::vec4(upperRight, 1.0f));
			//	obj_vertices.push_back(glm::vec4(glm::vec3(upperRight.x, upperRight.y - blockSize, upperRight.z), 1.0f));
			//	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			//	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 6, obj_vertices.size() - 5, obj_vertices.size() - 4));
			//	obj_faces.push_back(glm::uvec3(obj_vertices.size() - 3, obj_vertices.size() - 2, obj_vertices.size() - 1));
			//}
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

			if (!visited[r][c]){
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

			if (!visited[r + 1][c + 2]){
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
		}
	}
}