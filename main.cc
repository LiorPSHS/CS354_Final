#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// OpenGL library includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <debuggl.h>
#include "TGeom.h"
#include "camera.h"
#define PRESS_W key == GLFW_KEY_W && action != GLFW_RELEASE
#define PRESS_A key == GLFW_KEY_A && action != GLFW_RELEASE
#define PRESS_S key == GLFW_KEY_S && action != GLFW_RELEASE
#define PRESS_D key == GLFW_KEY_D && action != GLFW_RELEASE
#define PRESS_LEFT key == GLFW_KEY_LEFT && action != GLFW_RELEASE
#define PRESS_RIGHT key == GLFW_KEY_RIGHT && action != GLFW_RELEASE
#define PRESS_UP key == GLFW_KEY_UP && action != GLFW_RELEASE
#define PRESS_DOWN key == GLFW_KEY_DOWN && action != GLFW_RELEASE
#define PRESS_MIDDLE_BUTTON g_current_button == GLFW_MOUSE_BUTTON_MIDDLE || g_current_button == GLFW_MOUSE_BUTTON_8
void generateGeom();

int window_width = 800, window_height = 600;
bool isGlobal = true;
std::vector<glm::vec4> obj_vertices;
std::vector<glm::vec4> vtx_normals;
std::vector<glm::uvec3> obj_faces;
std::vector<glm::vec4> floor_vertices;
std::vector<glm::vec4> floor_normals;
std::vector<glm::uvec3> floor_faces;
glm::vec4 min_bounds = glm::vec4(std::numeric_limits<float>::max());
glm::vec4 max_bounds = glm::vec4(-std::numeric_limits<float>::max());

// Mouse position vectors
glm::vec2 cPos = glm::vec2(0, 0);
glm::vec2 lPos = glm::vec2(0, 0);
glm::vec2 dV = glm::vec2(0, 0);
float dVl = glm::length(dV);

// Main Loop Vars
glm::vec4 light_position = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
float aspect = 0.0f;
float theta = 0.0f;

// VBO and VAO descriptors.
enum { kVertexBuffer, kNormalBuffer, kIndexBuffer, kNumVbos };

// These are our VAOs.
enum { kGeometryVao, kFloorVao, kNumVaos };

GLuint g_array_objects[kNumVaos];  // This will store the VAO descriptors.
GLuint g_buffer_objects[kNumVaos][kNumVbos];  // These will store VBO descriptors.

// C++ 11 String Literal
// See http://en.cppreference.com/w/cpp/language/string_literal
const char* vertex_shader =
R"zzz(#version 330 core
in vec4 vertex_position;
in vec4 vertex_normal;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 light_position;
out vec4 light_direction;
out vec4 normal;
out vec4 color;
out vec4 world_position;
void main()
{
// Transform vertex into clipping coordinates
	world_position = vertex_position;
	gl_Position = projection * view * vertex_position;
// Lighting in camera coordinates
//  Compute light direction and transform to camera coordinates
    light_direction = normalize(light_position - vertex_position);
//  Transform normal to camera coordinates
        normal = abs(vertex_normal);
}
)zzz";

const char* fragment_shader =
R"zzz(#version 330 core
in vec4 normal;
in vec4 light_direction;
out vec4 fragment_color;
void main()
{
	vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
	float dot_nl = dot(normalize(light_direction), normalize(normal));
	dot_nl = clamp(dot_nl, 0.0, 1.0);
	fragment_color = clamp(dot_nl * color, 0.0, 1.0);
}
)zzz";
// FIXME: Implement shader effects with an alternative shader.

void
ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << "\n";
}

std::shared_ptr<TGeom> g_TGeom;
Camera g_camera;
glm::vec3 AOR;

void
KeyCallback(GLFWwindow* window,
            int key,
            int scancode,
            int action,
            int mods)
{
	// Note:
	// This is only a list of functions to implement.
	// you may want to re-organize this piece of code.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (PRESS_W) {
		if (isGlobal) {
			g_camera.setEye(g_camera.getEye() +
				g_camera.getZoomSpeed()*g_camera.getLook());
		}
		else {
			g_camera.setEye(g_camera.getEye() +
				g_camera.getZoomSpeed()*g_camera.getLook());
			g_camera.setCenter(g_camera.getCenter() +
				g_camera.getZoomSpeed()*g_camera.getLook());
		}
	} else if (PRESS_S) {
		if (isGlobal) {
			g_camera.setEye(g_camera.getEye() -
				g_camera.getZoomSpeed()*g_camera.getLook());
		}
		else {
			g_camera.setEye(g_camera.getEye() -
				g_camera.getZoomSpeed()*g_camera.getLook());
			g_camera.setCenter(g_camera.getCenter() -
				g_camera.getZoomSpeed()*g_camera.getLook());
		}
	} else if (PRESS_A) {
		if (isGlobal) {
			g_camera.setEye(g_camera.getEye() +
				g_camera.getPanSpeed()*g_camera.getRight());
		} else {
			g_camera.setEye(g_camera.getEye() +
				g_camera.getPanSpeed()*g_camera.getRight());
			g_camera.setCenter(g_camera.getCenter() + 
				g_camera.getPanSpeed()*g_camera.getRight());
		}
	}
	else if (PRESS_D) {
		if (isGlobal) {
			g_camera.setEye(g_camera.getEye() -
				g_camera.getPanSpeed()*g_camera.getRight());
		}
		else {
			g_camera.setEye(g_camera.getEye() -
				g_camera.getPanSpeed()*g_camera.getRight());
			g_camera.setCenter(g_camera.getCenter() -
				g_camera.getPanSpeed()*g_camera.getRight());
		}
	} else if (PRESS_UP) {
		if (isGlobal) {
			g_camera.setEye(g_camera.getEye() -
				g_camera.getPanSpeed()*g_camera.getUp());
		} else {
			g_camera.setEye(g_camera.getEye() -
				g_camera.getPanSpeed()*g_camera.getUp());
			g_camera.setCenter(g_camera.getCenter() -
				g_camera.getPanSpeed()*g_camera.getUp());
		}
	}
	else if (PRESS_DOWN) {
		if (isGlobal) {
			g_camera.setEye(g_camera.getEye() +
				g_camera.getPanSpeed()*g_camera.getUp());
		}
		else {
			g_camera.setEye(g_camera.getEye() +
				g_camera.getPanSpeed()*g_camera.getUp());
			g_camera.setCenter(g_camera.getCenter() +
				g_camera.getPanSpeed()*g_camera.getUp());
		}
	}
	else if (PRESS_LEFT) {
		g_camera.rotateEye(-g_camera.getLook(), g_camera.getRollSpeed());
	} else if (PRESS_RIGHT) {
		g_camera.rotateEye(-g_camera.getLook(), -g_camera.getRollSpeed());
	} else if (key == GLFW_KEY_C && action != GLFW_RELEASE) {
		isGlobal = !isGlobal;
	}
	if (!g_TGeom)
		return ; // 0-4 only available in TGeom mode.
	if (key == GLFW_KEY_0 && action != GLFW_RELEASE) {
		g_TGeom->set_nesting_level(0);
		obj_faces.clear();
		obj_vertices.clear();
		vtx_normals.clear();
		generateGeom();
	} else if (key == GLFW_KEY_1 && action != GLFW_RELEASE) {
		g_TGeom->set_nesting_level(1);
		obj_faces.clear();
		obj_vertices.clear();
		vtx_normals.clear();
		generateGeom();
	} else if (key == GLFW_KEY_2 && action != GLFW_RELEASE) {
		g_TGeom->set_nesting_level(2);
		obj_faces.clear();
		obj_vertices.clear();
		vtx_normals.clear();
		generateGeom();
	} else if (key == GLFW_KEY_3 && action != GLFW_RELEASE) {
		g_TGeom->set_nesting_level(3);
		obj_faces.clear();
		obj_vertices.clear();
		vtx_normals.clear();
		generateGeom();
	} else if (key == GLFW_KEY_4 && action != GLFW_RELEASE) {
		g_TGeom->set_nesting_level(4);
		obj_faces.clear();
		obj_vertices.clear();
		vtx_normals.clear();
		generateGeom();
	}
}

int g_current_button;
bool g_mouse_pressed;

void
MousePosCallback(GLFWwindow* window, double mouse_x, double mouse_y)
{
	lPos = cPos;
	cPos = glm::vec2(mouse_x, mouse_y);
	dV = lPos - cPos;
	dVl = glm::length(dV);
	if (!g_mouse_pressed)
		return;
	if (g_current_button == GLFW_MOUSE_BUTTON_LEFT) {
		if (isGlobal) {
			g_camera.rotateEye(g_camera.getUp(), g_camera.getRotationSpeed() * (dV.x / dVl)*.3);
			g_camera.rotateEye(g_camera.getRight(), g_camera.getRotationSpeed() * (dV.y / dVl)*.3);
		} else {
			g_camera.setEye(g_camera.getEye() +
				0.2f*(dV.x / dVl)*g_camera.getPanSpeed()*g_camera.getRight());
			g_camera.setCenter(g_camera.getCenter() +
				0.2f*(dV.x / dVl)*g_camera.getPanSpeed()*g_camera.getRight());
			g_camera.setEye(g_camera.getEye() +
				-0.2f*(dV.y / dVl)*g_camera.getPanSpeed()*g_camera.getUp());
			g_camera.setCenter(g_camera.getCenter() +
				-0.2f*(dV.y / dVl)*g_camera.getPanSpeed()*g_camera.getUp());
		}
	} else if (g_current_button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (isGlobal) {
			g_camera.setEye(g_camera.getEye() -
				-0.1f*dV.y*g_camera.getZoomSpeed()*g_camera.getLook());
		}else {
			g_camera.setEye(g_camera.getEye() -
				-0.1f*dV.y*g_camera.getZoomSpeed()*g_camera.getLook());
			g_camera.setCenter(g_camera.getCenter() -
				-0.1f*dV.y*g_camera.getZoomSpeed()*g_camera.getLook());
		}
	} else if (PRESS_MIDDLE_BUTTON) {
		std::cout << std::to_string(g_camera.getLook().z) << "\n";
	}
}

void
MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	g_mouse_pressed = (action == GLFW_PRESS);
	g_current_button = button;
}

int main(int argc, char* argv[])
{
	std::string window_title = "TGeom";
	if (!glfwInit()) exit(EXIT_FAILURE);
	g_TGeom = std::make_shared<TGeom>();
	glfwSetErrorCallback(ErrorCallback);

	// Ask an OpenGL 3.3 core profile context 
	// It is required on OSX and non-NVIDIA Linux
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(window_width, window_height,
			&window_title[0], nullptr, nullptr);
	CHECK_SUCCESS(window != nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	CHECK_SUCCESS(glewInit() == GLEW_OK);
	glGetError();  // clear GLEW's error for it
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MousePosCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSwapInterval(1);
	const GLubyte* renderer = glGetString(GL_RENDERER);  // get renderer string
	const GLubyte* version = glGetString(GL_VERSION);    // version as a string
	std::cout << "Renderer: " << renderer << "\n";
	std::cout << "OpenGL version supported:" << version << "\n";

	//GenerateGEOM
	g_TGeom->set_nesting_level(1);
	g_TGeom->generate_terrain(obj_vertices, vtx_normals, obj_faces);
	g_TGeom->set_clean();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	for (int i = 0; i < obj_vertices.size(); ++i) {
		min_bounds = glm::min(obj_vertices[i], min_bounds);
		max_bounds = glm::max(obj_vertices[i], max_bounds);
	}
	std::cout << "min_bounds = " << glm::to_string(min_bounds) << "\n";
	std::cout << "max_bounds = " << glm::to_string(max_bounds) << "\n";

	// Setup our VAO array.
	CHECK_GL_ERROR(glGenVertexArrays(kNumVaos, &g_array_objects[0]));

	// Switch to the VAO for Geometry.
	CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kGeometryVao]));

	// Generate buffer objects
	CHECK_GL_ERROR(glGenBuffers(kNumVbos, &g_buffer_objects[kGeometryVao][0]));

	// Setup vertex data in a VBO.
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kVertexBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * obj_vertices.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(0));

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kNormalBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * vtx_normals.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(1));

	// Setup element array buffer.
	CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kIndexBuffer]));
	CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(uint32_t) * obj_faces.size() * 3,
		&obj_faces[0], GL_STATIC_DRAW));

	/*
 	 * So far the geometry is loaded into g_buffer_objects[kGeometryVao][*].
	 * These buffers are bound to g_array_objects[kGeometryVao]
	 */

	// Setup vertex shader.
	GLuint vertex_shader_id = 0;
	const char* vertex_source_pointer = vertex_shader;
	CHECK_GL_ERROR(vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
	CHECK_GL_ERROR(glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, nullptr));
	glCompileShader(vertex_shader_id);
	CHECK_GL_SHADER_ERROR(vertex_shader_id);

	// Setup fragment shader.
	GLuint fragment_shader_id = 0;
	const char* fragment_source_pointer = fragment_shader;
	CHECK_GL_ERROR(fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
	CHECK_GL_ERROR(glShaderSource(fragment_shader_id, 1, &fragment_source_pointer, nullptr));
	glCompileShader(fragment_shader_id);
	CHECK_GL_SHADER_ERROR(fragment_shader_id);

	// Let's create our program.
	GLuint program_id = 0;
	CHECK_GL_ERROR(program_id = glCreateProgram());
	CHECK_GL_ERROR(glAttachShader(program_id, vertex_shader_id));
	CHECK_GL_ERROR(glAttachShader(program_id, fragment_shader_id));
    //CHECK_GL_ERROR(glAttachShader(program_id, geometry_shader_id));

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kVertexBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * obj_vertices.size() * 4, nullptr,
				GL_STATIC_DRAW));
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kNormalBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * vtx_normals.size() * 4, nullptr,
				GL_STATIC_DRAW));
	// Bind attributes.
	CHECK_GL_ERROR(glBindAttribLocation(program_id, 0, "vertex_position"));
	CHECK_GL_ERROR(glBindAttribLocation(program_id, 1, "vertex_normal"));
	CHECK_GL_ERROR(glBindFragDataLocation(program_id, 0, "fragment_color"));
	glLinkProgram(program_id);
	CHECK_GL_PROGRAM_ERROR(program_id);

	// Get the uniform locations.
	GLint projection_matrix_location = 0;
	CHECK_GL_ERROR(projection_matrix_location =
			glGetUniformLocation(program_id, "projection"));
	GLint view_matrix_location = 0;
	CHECK_GL_ERROR(view_matrix_location =
			glGetUniformLocation(program_id, "view"));
	GLint light_position_location = 0;
	CHECK_GL_ERROR(light_position_location =
			glGetUniformLocation(program_id, "light_position"));

	while (!glfwWindowShouldClose(window)) {
		// Setup some basic window stuff.
		glfwGetFramebufferSize(window, &window_width, &window_height);
		glViewport(0, 0, window_width, window_height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);

		// Switch to the Geometry VAO.
		CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kGeometryVao]));

		if (g_TGeom && g_TGeom->is_dirty()) {
		  g_TGeom->generate_terrain(obj_vertices, vtx_normals, obj_faces);
			g_TGeom->set_clean();
		}

		// Compute the projection matrix.
		aspect = static_cast<float>(window_width) / window_height;
		glm::mat4 projection_matrix =
			glm::perspective(glm::radians(45.0f), aspect, 0.0001f, 1000.0f);

		// Compute the view matrix
		// FIXME: change eye and center through mouse/keyboard events.
		glm::mat4 view_matrix = g_camera.get_view_matrix();

		// Send vertices to the GPU.
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
		                            g_buffer_objects[kGeometryVao][kVertexBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		                            sizeof(float) * obj_vertices.size() * 4,
		                            &obj_vertices[0], GL_STATIC_DRAW));
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
		                            g_buffer_objects[kGeometryVao][kNormalBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		                            sizeof(float) * vtx_normals.size() * 4,
		                            &vtx_normals[0], GL_STATIC_DRAW));
	
		// Use our program.
		CHECK_GL_ERROR(glUseProgram(program_id));

		// Pass uniforms in.
		CHECK_GL_ERROR(glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE,
					&projection_matrix[0][0]));
		CHECK_GL_ERROR(glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE,
					&view_matrix[0][0]));
		CHECK_GL_ERROR(glUniform4fv(light_position_location, 1, &light_position[0]));

		// Draw our triangles.
		CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, obj_faces.size() * 3, GL_UNSIGNED_INT, 0));

		// Poll and swap.
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void generateGeom() {
	g_TGeom->generate_terrain(obj_vertices, vtx_normals, obj_faces);
	g_TGeom->set_clean();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Setup element array buffer.
	CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kIndexBuffer]));
	CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(uint32_t) * obj_faces.size() * 3,
		&obj_faces[0], GL_STATIC_DRAW));
}
