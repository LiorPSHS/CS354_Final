#include "head.h"

// C++ 11 String Literal
// See http://en.cppreference.com/w/cpp/language/string_literal
const char* vertex_shader =
R"zzz(#version 330 core
in vec4 vertex_position;
in vec4 vertex_normal;
in float temp_data;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 light_position;
out vec4 light_direction;
out vec4 normal;
out vec4 color;
out vec4 world_position;
void main()
{
float R = clamp((1.0/25.0)*temp_data - 2.0, 0.0, 1.0);
float G = sin((3.14159/100)*temp_data);
float B = clamp(-(1.0/25.0)*temp_data + 2.0, 0.0, 1.0);


// Transform vertex into clipping coordinates
	world_position = vertex_position;
	gl_Position = projection * view * vertex_position;
// Lighting in camera coordinates
//  Compute light direction and transform to camera coordinates
    light_direction = normalize(light_position - vertex_position);
//  Transform normal to camera coordinates
        normal = abs(vertex_normal);
	color = vec4(R, G, B, 1.0);
}
)zzz";

const char* fragment_shader =
R"zzz(#version 330 core
in vec4 normal;
in vec4 light_direction;
in vec4 color;
out vec4 fragment_color;
void main()
{
	float dot_nl = dot(normalize(light_direction), normalize(normal));
	dot_nl = clamp(dot_nl, 0.0, 1.0);
	fragment_color = clamp(dot_nl * color, 0.0, 1.0);
}
)zzz";
// FIXME: Implement shader effects with an alternative shader.

void ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << "\n";
}

int main(int argc, char* argv[])
{
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

	// Init map data
	srand(time(0));
	// create some variables for readability
	int ULCorner;
	int LRCorner;
	int LLCorner;
	int URCorner;
	// Create initial upper left corner
	m_data.push_back(Sector());
	m_data.back().position = glm::vec3(5.0f, 0.0f, 5.0f);
	m_data.back().temp = 0;
	m_data.back().id = m_data.size() - 1;
	ULCorner = m_data.back().id;
	
	// Create initial lower left corner
	m_data.push_back(Sector());
	m_data.back().position = glm::vec3(5.0f, 0.0f, -5.0f);
	m_data.back().temp = 100;
	m_data.back().id = m_data.size() - 1;
	LLCorner = m_data.back().id;



	// Create initial upper right corner
	m_data.push_back(Sector());
	m_data.back().position = glm::vec3(-5.0f, 0.0f, 5.0f);
	m_data.back().temp = 0;
	m_data.back().id = m_data.size() - 1;
	URCorner = m_data.back().id;

	// Create initial lower right corner
	m_data.push_back(Sector());
	m_data.back().position = glm::vec3(-5.0f, 0.0f, -5.0f);
	m_data.back().temp = 100;
	m_data.back().id = m_data.size() - 1;
	LRCorner = m_data.back().id;

	g_TGeom->generateField(ULCorner, URCorner, LLCorner, LRCorner, m_data, 7);

	//GenerateGEOM
	g_TGeom->generate_terrain(m_data, obj_vertices, vtx_normals, obj_faces, vtx_temp);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	std::cout << vtx_temp.size() << " " << vtx_normals.size();
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

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kTempBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.

	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * vtx_temp.size(), nullptr,
		GL_STATIC_DRAW));

	CHECK_GL_ERROR(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(2));
	
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
	CHECK_GL_ERROR(glBindAttribLocation(program_id, 2, "temp_data"));
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
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
									g_buffer_objects[kGeometryVao][kTempBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
									sizeof(float) * vtx_temp.size(),
									&vtx_temp[0], GL_STATIC_DRAW));
	
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
