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
uniform int stage;
uniform vec4 camera_position;
out vec4 light_direction;
out vec4 camera_direction;
out vec4 normal;
out vec4 diffuse;
out vec4 world_position;
void main()
{
float R = clamp((1.0/25.0)*temp_data - 2.0, 0.0, 1.0);
float G = sin((3.14159/100)*temp_data);
float B = clamp(-(1.0/25.0)*temp_data + 2.0, 0.0, 1.0);


// Transform vertex into clipping coordinates
	world_position = vertex_position;
	gl_Position = projection * view * vertex_position;
	camera_direction = camera_position - gl_Position;
// Lighting in camera coordinates
//  Compute light direction and transform to camera coordinates
    light_direction = normalize(light_position - vertex_position);
//  Transform normal to camera coordinates
        normal = vertex_normal;
	diffuse = vec4(R, G, B, 1.0);
}
)zzz";

const char* fragment_shader =
R"zzz(#version 330 core
in vec4 normal;
in vec4 light_direction;
in vec4 diffuse;
uniform int stage;
uniform float ambient;
uniform vec4 specular;
uniform float shininess;
in vec4 camera_direction;
out vec4 fragment_color;
void main()
{
	vec4 tColor;
	if(stage % 2 == 0) {
	    tColor = diffuse;
	} else {
        tColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if(stage < 6) {
		fragment_color = tColor;
    } else {
		float dot_nl = dot(normalize(light_direction), normalize(abs(normal)));
		vec3 color = vec3(tColor);
		dot_nl = clamp(dot_nl, 0.0, 1.0);
		vec4 spec = specular * pow(max(0.0, dot(reflect(-light_direction, normal), -camera_direction)), shininess);
		color = clamp(dot_nl * color + ambient*color + vec3(spec), 0.0, 1.0);
		fragment_color = vec4(color, 1.0);
	}
}
)zzz";

const char* overlay_vertex_shader =
R"zzz(#version 330 core
in vec4 vertex_position;
in vec4 vertex_normal;
in float temp_data;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 light_position;
uniform int stage;
out vec4 light_direction;
out vec4 normal;
out vec4 diffuse;
out vec4 world_position;
void main()
{
    float R = clamp((1.0/25.0)*temp_data - 2.0, 0.0, 1.0);
    float G = sin((3.14159/100)*temp_data);
    float B = clamp(-(1.0/25.0)*temp_data + 2.0, 0.0, 1.0);


    // Transform vertex into clipping coordinates
	world_position = vertex_position;
	gl_Position = projection * view * (vertex_position + vec4(vertex_position.x*0.01f, 0.06f, vertex_position.z*0.01f, 0.0f));

    // Lighting in camera coordinates
    // Compute light direction and transform to camera coordinates
    light_direction = normalize(light_position - vertex_position);
    //  Transform normal to camera coordinates
    normal = abs(vertex_normal);
	diffuse = vec4(R, G, B, 1.0);
}
)zzz";

const char* overlay_fragment_shader =
R"zzz(#version 330 core
in vec4 normal;
in vec4 light_direction;
in vec4 diffuse;
out vec4 fragment_color;
void main()
{
	  fragment_color = diffuse;
	  fragment_color.a = 0.5;
}
)zzz";

const char* water_vertex_shader =
R"zzz(#version 330 core
in vec4 vertex_position;
in vec4 vertex_normal;
in float temp_data;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 light_position;
uniform vec4 camera_position;
uniform float step;
out vec4 light_direction;
out vec4 camera_direction;
out vec4 normal;
out vec4 diffuse;
out vec4 world_position;
void main()
{
// Transform vertex into clipping coordinates
	world_position = vertex_position;
	gl_Position = projection * view * vertex_position;
	camera_direction = camera_position - gl_Position;
	camera_direction.w = 1.0;
// Lighting in camera coordinates
//  Compute light direction and transform to camera coordinates
    light_direction = normalize(light_position - vertex_position);
//  Transform normal to camera coordinates
        normal = normalize(vertex_normal);
	diffuse = vec4(0.0, 0.0, 1.0, 1.0);
}
)zzz";

const char* water_fragment_shader =
R"zzz(#version 330 core
in vec4 normal;
in vec4 light_direction;
in vec4 diffuse;
uniform int stage;
uniform float ambient;
uniform vec4 specular;
uniform float shininess;
in vec4 camera_direction;
out vec4 fragment_color;
void main()
{
	vec3 color = vec3(diffuse);
	float dot_nl = dot(normalize(light_direction), normalize(normal));
	dot_nl = clamp(dot_nl, 0.0, 1.0);
	vec4 spec = specular * pow(max(0.0, dot(reflect(-light_direction, normal), -camera_direction)), shininess);
	color = clamp(dot_nl * color + ambient*color + vec3(spec), 0.0, 1.0);
	fragment_color = vec4(color, 0.5);
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
	g_TGeom->generate_noise(mapSize, 5, 2);

	//GenerateGEOM
	g_TGeom->generate_terrain(obj_vertices, vtx_normals, obj_faces, vtx_temp);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	CHECK_GL_ERROR(glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(2));

	// Setup element array buffer.
	CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer_objects[kGeometryVao][kIndexBuffer]));
	CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(uint32_t) * obj_faces.size() * 3,
		&obj_faces[0], GL_STATIC_DRAW));
	
	/*******************************************************************************************
	 ** BEGIN LOADING BUFFER FOR OVERLAY SHADER                                                *
	 *******************************************************************************************/
	// Load the overlay into g_buffer_objects[kOverlayVao][*]
	g_TGeom->generate_trimesh(overlay_vertices, overlay_normals, overlay_faces, overlay_temp);

	// Switch to the VAO for geometry.
	CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kOverlayVao]));

	// Generate buffer objects
	CHECK_GL_ERROR(glGenBuffers(kNumVbos, &g_buffer_objects[kOverlayVao][0]));

	// Setup vertex data in a VBO.
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kOverlayVao][kVertexBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * overlay_vertices.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(0));

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kOverlayVao][kNormalBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * overlay_normals.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(1));

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kOverlayVao][kTempBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.

	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * overlay_temp.size(), nullptr,
		GL_STATIC_DRAW));

	CHECK_GL_ERROR(glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(2));

	// Setup element array buffer.
	CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer_objects[kOverlayVao][kIndexBuffer]));
	CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(uint32_t) * overlay_faces.size() * 3,
		&overlay_faces[0], GL_STATIC_DRAW));
	// END OVERLAY SHADER LOAD


	/*******************************************************************************************
	** BEGIN LOADING BUFFER FOR WATER SHADER                                                   *
	*******************************************************************************************/
	// Load the water into g_buffer_objects[kwaterVao][*]
	g_TGeom->generate_water(water_vertices, water_normals, water_faces, step);

	// Switch to the VAO for geometry.
	CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kWaterVao]));

	// Generate buffer objects
	CHECK_GL_ERROR(glGenBuffers(kNumVbos, &g_buffer_objects[kWaterVao][0]));

	// Setup vertex data in a VBO.
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kWaterVao][kVertexBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * water_vertices.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(0));

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kWaterVao][kNormalBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * water_normals.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0));
	CHECK_GL_ERROR(glEnableVertexAttribArray(1));

	// Setup element array buffer.
	CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer_objects[kWaterVao][kIndexBuffer]));
	CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(uint32_t) * water_faces.size() * 3,
		&water_faces[0], GL_STATIC_DRAW));
	// END WATER SHADER LOAD

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
	GLint camera_position_location = 0;
	CHECK_GL_ERROR(camera_position_location =
		glGetUniformLocation(program_id, "camera_position"));
	GLint stage_position_location = 0;
	CHECK_GL_ERROR(stage_position_location =
		glGetUniformLocation(program_id, "stage"));
	GLint step_position_location = 0;
	CHECK_GL_ERROR(step_position_location =
		glGetUniformLocation(program_id, "step"));
	GLint ambient_location = 0;
	CHECK_GL_ERROR(ambient_location =
		glGetUniformLocation(program_id, "ambient"));
	GLint specular_location = 0;
	CHECK_GL_ERROR(specular_location =
		glGetUniformLocation(program_id, "specular"));
	GLint shininess_location = 0;
	CHECK_GL_ERROR(shininess_location =
		glGetUniformLocation(program_id, "shininess"));

	// SETUP SHADERS FOR OVERLAY

	// Setup vertex shader for the overlay.
	GLuint overlay_vertex_shader_id = 0;
	const char* overlay_vertex_source_pointer = overlay_vertex_shader;
	CHECK_GL_ERROR(overlay_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
	CHECK_GL_ERROR(glShaderSource(overlay_vertex_shader_id, 1, &overlay_vertex_source_pointer, nullptr));
	glCompileShader(overlay_vertex_shader_id);
	CHECK_GL_SHADER_ERROR(overlay_vertex_shader_id);

	// Setup fragment shader for the overlay
	GLuint overlay_fragment_shader_id = 0;
	const char* overlay_fragment_source_pointer = overlay_fragment_shader;
	CHECK_GL_ERROR(overlay_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
	CHECK_GL_ERROR(glShaderSource(overlay_fragment_shader_id, 1,
		&overlay_fragment_source_pointer, nullptr));
	glCompileShader(overlay_fragment_shader_id);
	CHECK_GL_SHADER_ERROR(overlay_fragment_shader_id);
	// END SETUP SHADERS FOR OVERLAY

	/***************************************************************************
	 ** Setup Program for the Overlay                                         **
	 ***************************************************************************/
	GLuint overlay_program_id = 0;
	GLint overlay_projection_matrix_location = 0;
	GLint overlay_view_matrix_location = 0;
	GLint overlay_light_position_location = 0;
	GLint overlay_stage_position_location = 0;

	// Let's create our program.
	CHECK_GL_ERROR(overlay_program_id = glCreateProgram());
	CHECK_GL_ERROR(glAttachShader(overlay_program_id, overlay_vertex_shader_id));
	CHECK_GL_ERROR(glAttachShader(overlay_program_id, overlay_fragment_shader_id));

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kOverlayVao][kVertexBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * overlay_vertices.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kOverlayVao][kNormalBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * overlay_normals.size() * 4, nullptr,
		GL_STATIC_DRAW));
	// Bind attributes.
	CHECK_GL_ERROR(glBindAttribLocation(overlay_program_id, 0, "vertex_position"));
	CHECK_GL_ERROR(glBindAttribLocation(overlay_program_id, 1, "vertex_normal"));
	CHECK_GL_ERROR(glBindAttribLocation(overlay_program_id, 2, "temp_data"));
	CHECK_GL_ERROR(glBindFragDataLocation(overlay_program_id, 0, "fragment_color"));
	glLinkProgram(overlay_program_id);
	CHECK_GL_PROGRAM_ERROR(overlay_program_id);

	// Get the uniform locations.
	CHECK_GL_ERROR(overlay_projection_matrix_location =
		glGetUniformLocation(overlay_program_id, "projection"));
	CHECK_GL_ERROR(overlay_view_matrix_location =
		glGetUniformLocation(overlay_program_id, "view"));
	CHECK_GL_ERROR(overlay_light_position_location =
		glGetUniformLocation(overlay_program_id, "light_position"));
	CHECK_GL_ERROR(overlay_stage_position_location =
		glGetUniformLocation(overlay_program_id, "stage"));
	// END SETUP PROGRAM FOR OVERLAY


	// SETUP SHADERS FOR water

	// Setup vertex shader for the water.
	GLuint water_vertex_shader_id = 0;
	const char* water_vertex_source_pointer = water_vertex_shader;
	CHECK_GL_ERROR(water_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
	CHECK_GL_ERROR(glShaderSource(water_vertex_shader_id, 1, &water_vertex_source_pointer, nullptr));
	glCompileShader(water_vertex_shader_id);
	CHECK_GL_SHADER_ERROR(water_vertex_shader_id);

	// Setup fragment shader for the water
	GLuint water_fragment_shader_id = 0;
	const char* water_fragment_source_pointer = water_fragment_shader;
	CHECK_GL_ERROR(water_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
	CHECK_GL_ERROR(glShaderSource(water_fragment_shader_id, 1,
		&water_fragment_source_pointer, nullptr));
	glCompileShader(water_fragment_shader_id);
	CHECK_GL_SHADER_ERROR(water_fragment_shader_id);
	// END SETUP SHADERS FOR water

	/***************************************************************************
	** Setup Program for the water                                         **
	***************************************************************************/
	GLuint water_program_id = 0;
	GLint water_projection_matrix_location = 0;
	GLint water_view_matrix_location = 0;
	GLint water_light_position_location = 0;
	GLint water_stage_position_location = 0;
	GLint water_step_position_location = 0;
	GLint water_ambient_location = 0;
	GLint water_specular_location = 0;
	GLint water_shininess_location = 0;



	// Let's create our program.
	CHECK_GL_ERROR(water_program_id = glCreateProgram());
	CHECK_GL_ERROR(glAttachShader(water_program_id, water_vertex_shader_id));
	CHECK_GL_ERROR(glAttachShader(water_program_id, water_fragment_shader_id));

	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kWaterVao][kVertexBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * water_vertices.size() * 4, nullptr,
		GL_STATIC_DRAW));
	CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, g_buffer_objects[kWaterVao][kNormalBuffer]));
	// NOTE: We do not send anything right now, we just describe it to OpenGL.
	CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * water_normals.size() * 4, nullptr,
		GL_STATIC_DRAW));
	// Bind attributes.
	CHECK_GL_ERROR(glBindAttribLocation(water_program_id, 0, "vertex_position"));
	CHECK_GL_ERROR(glBindAttribLocation(water_program_id, 1, "vertex_normal"));
	CHECK_GL_ERROR(glBindFragDataLocation(water_program_id, 0, "fragment_color"));
	glLinkProgram(water_program_id);
	CHECK_GL_PROGRAM_ERROR(water_program_id);

	// Get the uniform locations.
	CHECK_GL_ERROR(water_projection_matrix_location =
		glGetUniformLocation(water_program_id, "projection"));
	CHECK_GL_ERROR(water_view_matrix_location =
		glGetUniformLocation(water_program_id, "view"));
	CHECK_GL_ERROR(water_light_position_location =
		glGetUniformLocation(water_program_id, "light_position"));
	CHECK_GL_ERROR(water_stage_position_location =
		glGetUniformLocation(water_program_id, "stage"));
	CHECK_GL_ERROR(water_step_position_location =
		glGetUniformLocation(water_program_id, "step"));
	CHECK_GL_ERROR(water_ambient_location =
		glGetUniformLocation(water_program_id, "ambient"));
	CHECK_GL_ERROR(water_specular_location =
		glGetUniformLocation(water_program_id, "specular"));
	CHECK_GL_ERROR(water_shininess_location =
		glGetUniformLocation(water_program_id, "shininess"));

	// END SETUP PROGRAM FOR water

	// run geometry here so old buffers are bound
	obj_vertices.clear();
	vtx_normals.clear();
	obj_faces.clear();
	vtx_temp.clear();
	g_TGeom->generate_trimesh(obj_vertices, vtx_normals, obj_faces, vtx_temp);

	while (!glfwWindowShouldClose(window)) {
		step += incr;
		g_TGeom->generate_water(water_vertices, water_normals, water_faces, step);
		if (step > PI || step < (-PI)) {
			incr *= -1;
		}
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
		CHECK_GL_ERROR(glUniform4fv(camera_position_location, 1, &g_camera.getEye()[0]));
		CHECK_GL_ERROR(glUniform1i(stage_position_location, stage));
		CHECK_GL_ERROR(glUniform1f(step_position_location, step));
		CHECK_GL_ERROR(glUniform1f(ambient_location, wt_ambient));
		CHECK_GL_ERROR(glUniform4fv(specular_location, 1, &t_specular[0]));
		CHECK_GL_ERROR(glUniform1f(shininess_location, t_shininess));

		// Draw our triangles.
		CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, obj_faces.size() * 3, GL_UNSIGNED_INT, 0));

		/***********************************************************************************
		 ** BEGIN Rendering the overlay                                                   **
		 ***********************************************************************************/
		 // Switch to the Geometry VAO.
		CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kOverlayVao]));

		// Send vertices to the GPU.
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
			g_buffer_objects[kOverlayVao][kVertexBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * overlay_vertices.size() * 4,
			&overlay_vertices[0], GL_STATIC_DRAW));
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
			g_buffer_objects[kOverlayVao][kNormalBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * overlay_normals.size() * 4,
			&overlay_normals[0], GL_STATIC_DRAW));
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
			g_buffer_objects[kOverlayVao][kTempBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * overlay_temp.size(),
			&overlay_temp[0], GL_STATIC_DRAW));

		// Use our program.
		CHECK_GL_ERROR(glUseProgram(overlay_program_id));

		// Pass uniforms in.
		CHECK_GL_ERROR(glUniformMatrix4fv(overlay_projection_matrix_location, 1, GL_FALSE,
			&projection_matrix[0][0]));
		CHECK_GL_ERROR(glUniformMatrix4fv(overlay_view_matrix_location, 1, GL_FALSE,
			&view_matrix[0][0]));
		CHECK_GL_ERROR(glUniform4fv(overlay_light_position_location, 1, &light_position[0]));
		CHECK_GL_ERROR(glUniform1i(overlay_stage_position_location, stage));

		// Draw our triangles.
		if(overlayEnabled)
			CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, overlay_faces.size() * 3, GL_UNSIGNED_INT, 0));
		// END RENDERING THE OVERLAY

		/***********************************************************************************
		** BEGIN Rendering the water                                                   **
		***********************************************************************************/
		// Switch to the Geometry VAO.
		CHECK_GL_ERROR(glBindVertexArray(g_array_objects[kWaterVao]));

		// Send vertices to the GPU.
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
			g_buffer_objects[kWaterVao][kVertexBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * water_vertices.size() * 4,
			&water_vertices[0], GL_STATIC_DRAW));
		CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER,
			g_buffer_objects[kWaterVao][kNormalBuffer]));
		CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * water_normals.size() * 4,
			&water_normals[0], GL_STATIC_DRAW));

		// Use our program.
		CHECK_GL_ERROR(glUseProgram(water_program_id));

		// Pass uniforms in.
		CHECK_GL_ERROR(glUniformMatrix4fv(water_projection_matrix_location, 1, GL_FALSE,
			&projection_matrix[0][0]));
		CHECK_GL_ERROR(glUniformMatrix4fv(water_view_matrix_location, 1, GL_FALSE,
			&view_matrix[0][0]));
		CHECK_GL_ERROR(glUniform4fv(water_light_position_location, 1, &light_position[0]));
		CHECK_GL_ERROR(glUniform1i(water_stage_position_location, stage));
		CHECK_GL_ERROR(glUniform1f(water_step_position_location, step));
		CHECK_GL_ERROR(glUniform1f(ambient_location, wt_ambient));
		CHECK_GL_ERROR(glUniform4fv(water_specular_location, 1, &w_specular[0]));
		CHECK_GL_ERROR(glUniform1f(water_shininess_location, w_shininess));

		// Draw our triangles.
		if (waterEnabled)
			CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, water_faces.size() * 3, GL_UNSIGNED_INT, 0));
		// END RENDERING THE WATER

		// Poll and swap.
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
