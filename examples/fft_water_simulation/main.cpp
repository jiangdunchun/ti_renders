#include "graphic_interface.h"
#include <GLFW/glfw3.h>

#include "shader_files.h"
#include <ctime>

#define PI 3.1415926
#define G 9.81

const int FFT_N = 512;
const float FFT_L = 400.0f;
const vec2 FFT_W = normalize(vec2(1.0f, 1.0f));
const float FFT_V = 40.0f;
const float FFT_A = 20.0f;

const float zoom = 90.0f;
const float z_near = 0.1f;
const float z_far = 1000.0f;
const vector<vertex> scr_vertices = {
    {vec3(-1.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
    {vec3(1.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
    {vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
    {vec3(-1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)}
};
const vector<unsigned int> scr_indices = {
    0, 1, 3,
    1, 2, 3
};
const vector<string> sky_images = {
    "asset/image/right.jpg",
    "asset/image/left.jpg",
    "asset/image/top.jpg",
    "asset/image/bottom.jpg",
    "asset/image/front.jpg",
    "asset/image/back.jpg"};
const vector<vertex> sky_vertices = {
    //front
    {vec3(-1.0f, -1.0f, -1.0f)},
    {vec3(1.0f, -1.0f, -1.0f)},
    {vec3(1.0f,  1.0f, -1.0f)},
    {vec3(-1.0f,  1.0f, -1.0f)},
    //back
    {vec3(1.0f, -1.0f,  1.0f)},
    {vec3(-1.0f, -1.0f,  1.0f)},
    {vec3(-1.0f,  1.0f,  1.0f)},
    {vec3(1.0f,  1.0f,  1.0f)},
    //left
    {vec3(-1.0f, -1.0f,  1.0f)},
    {vec3(-1.0f, -1.0f, -1.0f)},
    {vec3(-1.0f,  1.0f, -1.0f)},
    {vec3(-1.0f,  1.0f,  1.0f)},
    //right
    {vec3(1.0f, -1.0f, -1.0f)},
    {vec3(1.0f, -1.0f,  1.0f)},
    {vec3(1.0f,  1.0f,  1.0f)},
    {vec3(1.0f,  1.0f, -1.0f)},
    //up
    {vec3(-1.0f,  1.0f, -1.0f)},
    {vec3(1.0f,  1.0f, -1.0f)},
    {vec3(1.0f,  1.0f,  1.0f)},
    {vec3(-1.0f,  1.0f,  1.0f)},
    //down
    {vec3(-1.0f, -1.0f,  1.0f)},
    {vec3(1.0f, -1.0f,  1.0f)},
    {vec3(1.0f, -1.0f, -1.0f)},
    {vec3(-1.0f, -1.0f, -1.0f)}};
const vector<unsigned int> sky_indices = {
    //front
    0, 1, 3,
    1, 2, 3,
    //back
    4, 5, 7,
    5, 6, 7,
    //left
    8, 9, 11,
    9, 10, 11,
    //right
    12, 13, 15,
    13, 14, 15,
    //up
    16, 17, 19,
    17, 18, 19,
    //down
    20, 21, 23,
    21, 22, 23};

float timer = 0.0f;
unsigned int scr_width = 800;
unsigned int scr_height = 600;
vec3 camera_position = vec3(0.0f, 100.0f, 200.0f);
vec3 camera_rotation = vec3(-30.0f, 0.0f, 0.0f);
mat4 view;
mat4 projection;

GLuint fft_ht_shader;
GLuint fft_ifft_shader;
GLuint fft_displacement_shader;
GLuint fft_normal_bubble_shader;

GLuint h0_k_texture;
GLuint h0_kneg_conj_texture;

GLuint ht_k_y_texture;
GLuint ht_k_x_texture;
GLuint ht_k_z_texture;

GLuint steps = 0;
GLuint butterfly_indices_texture;
GLuint pingpong_y_textures[2];
GLuint pingpong_z_textures[2];
GLuint pingpong_x_textures[2];

GLuint displacement_texture;

GLuint normal_texture;
GLuint bubble_texture;

GLuint sky_shader;
GLuint sky_cubemap;
GLuint sky_mesh_VAO;
GLuint sky_mesh_VBO;
GLuint sky_mesh_EBO;
GLuint sky_mesh_triagnle_size;
  
GLuint water_shader;
GLuint water_mesh_VAO;
GLuint water_mesh_VBO;
GLuint water_mesh_EBO;
GLuint water_mesh_triagnle_size;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void create_resource(void);
void ifft(GLuint ht_texture, GLuint* pingpong_textures, GLuint& out_texture);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(scr_width, scr_height, "FFT water simulation", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    create_resource();

    
    construct_projection(zoom, float(scr_height)/ scr_width, z_near, z_far, projection);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    clock_t start, end;
    while(!glfwWindowShouldClose(window)) {
        start = clock();
        processInput(window);

        // ht
        glUseProgram(fft_ht_shader);
        glBindImageTexture(0, h0_k_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
	    glBindImageTexture(1, h0_kneg_conj_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
        glBindImageTexture(2, ht_k_y_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glBindImageTexture(3, ht_k_x_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glBindImageTexture(4, ht_k_z_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glUniform1f(glGetUniformLocation(fft_ht_shader, "u_Timer"), timer);
        glUniform1i(glGetUniformLocation(fft_ht_shader, "u_N"), FFT_N);
        glUniform1f(glGetUniformLocation(fft_ht_shader, "u_L"), FFT_L);
        glDispatchCompute(FFT_N, FFT_N, 1);
	    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        // ifft
        GLuint height_texture;
        ifft(ht_k_y_texture, pingpong_y_textures, height_texture);
        GLuint diplacement_x_texture;
        ifft(ht_k_x_texture, pingpong_x_textures, diplacement_x_texture);
        GLuint diplacement_z_texture;
        ifft(ht_k_z_texture, pingpong_z_textures, diplacement_z_texture);

        // displacement
        glUseProgram(fft_displacement_shader);
        glBindImageTexture(0, height_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
        glBindImageTexture(1, diplacement_x_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
        glBindImageTexture(2, diplacement_z_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
        glBindImageTexture(3, displacement_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glUniform1i(glGetUniformLocation(fft_displacement_shader, "u_N"), FFT_N);
        glUniform1f(glGetUniformLocation(fft_displacement_shader, "u_A"), FFT_A);
        glDispatchCompute(FFT_N, FFT_N, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        // displacement
        glUseProgram(fft_normal_bubble_shader);
        glBindImageTexture(0, displacement_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
        glBindImageTexture(1, normal_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glBindImageTexture(2, bubble_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glUniform1i(glGetUniformLocation(fft_normal_bubble_shader, "u_N"), FFT_N);
        glUniform1f(glGetUniformLocation(fft_normal_bubble_shader, "u_L"), FFT_L);
        glDispatchCompute(FFT_N, FFT_N, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        glViewport(0, 0, scr_width, scr_height);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // draw sky
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        construct_view(vec3(0.0f, 0.0f, 0.0f), camera_rotation, view);
        glUseProgram(sky_shader);
        glUniformMatrix4fv(glGetUniformLocation(sky_shader, "uProjection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(sky_shader, "uView"), 1, GL_FALSE, &view[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(sky_shader, "uSky"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sky_cubemap);
        glBindVertexArray(sky_mesh_VAO);
        glDrawElements(GL_TRIANGLES, sky_mesh_triagnle_size * 3, GL_UNSIGNED_INT, 0);

        //// draw water
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClear(GL_DEPTH_BUFFER_BIT);
        construct_view(camera_position, camera_rotation, view);
        glUseProgram(water_shader);
        glUniformMatrix4fv(glGetUniformLocation(water_shader, "uProjection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(water_shader, "uView"), 1, GL_FALSE, &view[0][0]);
        glUniform3fv(glGetUniformLocation(water_shader, "uView_pos"), 1, &camera_position[0]);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(water_shader, "uDisplacement"), 0);
        glBindTexture(GL_TEXTURE_2D, displacement_texture);
        glActiveTexture(GL_TEXTURE1);
        glUniform1i(glGetUniformLocation(water_shader, "uSky"), 1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sky_cubemap);
        glActiveTexture(GL_TEXTURE2);
        glUniform1i(glGetUniformLocation(water_shader, "uNormal"), 2);
        glBindTexture(GL_TEXTURE_2D, normal_texture);
        glActiveTexture(GL_TEXTURE3);
        glUniform1i(glGetUniformLocation(water_shader, "uBubble"), 3);
        glBindTexture(GL_TEXTURE_2D, bubble_texture);
        glBindVertexArray(water_mesh_VAO);
        glDrawElements(GL_TRIANGLES, water_mesh_triagnle_size * 3, GL_UNSIGNED_INT, 0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        glfwSwapBuffers(window);
        glfwPollEvents();
        end = clock();
		timer += float(end - start) / 1000.0f;
    }
    glfwTerminate();
    return 1;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    scr_width = width;
    scr_height = height;

    construct_projection(zoom, float(height)/ width, z_near, z_far, projection);
}

GLfloat rand(const GLfloat start, const GLfloat end) {
	return ((GLfloat)rand() / (GLfloat)RAND_MAX) * (end - start) + start;
}
 
GLfloat rand_normal(const GLfloat mean, const GLfloat standardDeviation) {
	GLfloat x1, x2;
	x1 = rand(0.000001f, 1.0f - 0.000001f);
	x2 = rand(0.0f, 1.0f);
 
	return mean + standardDeviation * (sqrtf(-2.0f * logf(x1)) * cosf(2.0f * PI * x2));
}
 
GLfloat phillips(GLfloat A, GLfloat L, glm::vec2 wave_dir, glm::vec2 wind_dir) {
	GLfloat k = glm::length(wave_dir);
	GLfloat waveDotWind = glm::dot(wave_dir, wind_dir);
 
	if (L == 0.0f || k == 0.0f) return 0.0f;
	return A * expf(-1.0f / (k * L * k * L)) / (k * k * k * k) * waveDotWind * waveDotWind;
}

void butterfly_shuffle_indices(GLfloat* indices, int num) {
    struct butterfly_shuffle_item{
        vector<GLfloat> indices;
        butterfly_shuffle_item* left = nullptr;
        butterfly_shuffle_item* right = nullptr;

        butterfly_shuffle_item() {}
        ~butterfly_shuffle_item() {
            if (left) delete left;
            if (right) delete right;
        }
        static void split(butterfly_shuffle_item* n_item) {
            if (n_item->indices.size() <= 2) return;

            n_item->left = new butterfly_shuffle_item();
            n_item->right = new butterfly_shuffle_item();
            for (int i = 0; i < n_item->indices.size(); i++) {
                if (i % 2 == 0) n_item->left->indices.push_back(n_item->indices[i]);
                else n_item->right->indices.push_back(n_item->indices[i]);
            }
            split(n_item->left);
            split(n_item->right);
        }
        static void tranverse(butterfly_shuffle_item* n_item, vector<GLfloat>& indices) {
            if (n_item->indices.size() <= 2) {
                indices.push_back(n_item->indices[0]);
                indices.push_back(n_item->indices[1]);
            }
            else {
                tranverse(n_item->left, indices);
                tranverse(n_item->right, indices);
            }
        }
    };
    butterfly_shuffle_item* n_item = new butterfly_shuffle_item();
    for (int i = 0; i < num; i++) n_item->indices.push_back(indices[i]);
    butterfly_shuffle_item::split(n_item);
    vector<GLfloat> buffer;
    butterfly_shuffle_item::tranverse(n_item, buffer); 
    for (int i = 0; i < num; i++) indices[i] = buffer[i];
    delete n_item;
}

void create_resource(void) {
    // fft
    create_shader(fft_ht_compute_shader, fft_ht_shader);
    create_shader(fft_ifft_compute_shader, fft_ifft_shader);
    //create_shader(fft_ifft_0_compute_shader, fft_ifft_shader);
    create_shader(fft_displacement_compute_shader, fft_displacement_shader);
    create_shader(fft_normal_bubble_compute_shader, fft_normal_bubble_shader);

    GLfloat* h0_k_data = (GLfloat*)malloc(FFT_N * FFT_N * 2 * sizeof(GLfloat));
    GLfloat* h0_kneg_conj_data = (GLfloat*)malloc(FFT_N * FFT_N * 2 * sizeof(GLfloat));
    vec2 wave_dir;
    for (int i = 0; i < FFT_N; i++) {
        wave_dir.y = ((GLfloat)i - (GLfloat)FFT_N / 2.0f) * (2.0f * PI / FFT_L);
        for (int j = 0; j < FFT_N; j++) {
            wave_dir.x = ((GLfloat)j - (GLfloat)FFT_N / 2.0f) * (2.0f * PI / FFT_L);
            float L = FFT_V * FFT_V / G;
            float k_phillips_value = phillips(FFT_A, L, wave_dir, FFT_W);
            h0_k_data[i * 2 * FFT_N + j * 2 + 0] = 1.0f / sqrtf(2.0f) * rand_normal(0.0f, 1.0f) * k_phillips_value;
            h0_k_data[i * 2 * FFT_N + j * 2 + 1] = 1.0f / sqrtf(2.0f) * rand_normal(0.0f, 1.0f) * k_phillips_value;

            float kneg_phillips_value = phillips(FFT_A, L, -1.0f * wave_dir, FFT_W);
            h0_kneg_conj_data[i * 2 * FFT_N + j * 2 + 0] = 1.0f / sqrtf(2.0f) * rand_normal(0.0f, 1.0f) * kneg_phillips_value;
            h0_kneg_conj_data[i * 2 * FFT_N + j * 2 + 1] = -1.0f / sqrtf(2.0f) * rand_normal(0.0f, 1.0f) * kneg_phillips_value;
        }
    }
    create_texture_2d(FFT_N, FFT_N, h0_k_texture, GL_RG, h0_k_data);
    create_texture_2d(FFT_N, FFT_N, h0_kneg_conj_texture, GL_RG, h0_kneg_conj_data);
    free(h0_k_data);
    free(h0_kneg_conj_data);

    create_texture_2d(FFT_N, FFT_N, ht_k_y_texture, GL_RG);
    create_texture_2d(FFT_N, FFT_N, ht_k_x_texture, GL_RG);
    create_texture_2d(FFT_N, FFT_N, ht_k_z_texture, GL_RG);

    GLint temp = FFT_N;
    while (!(temp & 0x1)) {
        temp = temp >> 1;
        steps++;
    }
    GLfloat* butterfly_indices_data = (GLfloat*)malloc(FFT_N * sizeof(GLfloat));
    for (int i = 0; i < FFT_N; i++) butterfly_indices_data[i] = i;
    butterfly_shuffle_indices(butterfly_indices_data, FFT_N);
    create_texture_1d(FFT_N, butterfly_indices_texture, GL_RED, butterfly_indices_data);
    free(butterfly_indices_data);
    create_texture_2d(FFT_N, FFT_N, pingpong_y_textures[0], GL_RG);
    create_texture_2d(FFT_N, FFT_N, pingpong_y_textures[1], GL_RG);
    create_texture_2d(FFT_N, FFT_N, pingpong_x_textures[0], GL_RG);
    create_texture_2d(FFT_N, FFT_N, pingpong_x_textures[1], GL_RG);
    create_texture_2d(FFT_N, FFT_N, pingpong_z_textures[0], GL_RG);
    create_texture_2d(FFT_N, FFT_N, pingpong_z_textures[1], GL_RG);

    create_texture_2d(FFT_N, FFT_N, displacement_texture, GL_RG);

    create_texture_2d(FFT_N, FFT_N, normal_texture, GL_RG);
    create_texture_2d(FFT_N, FFT_N, bubble_texture, GL_RG);


    // sky
    create_shader(sky_vertex_shader, sky_fragment_shader, sky_shader);
    create_cubemap(sky_images, sky_cubemap);
    create_vertex_buffer(sky_vertices, sky_indices, sky_mesh_VAO, sky_mesh_VBO, sky_mesh_EBO);
    sky_mesh_triagnle_size = sky_indices.size() / 3;

    // water
    create_shader(water_vertex_shader, water_fragment_shader, water_shader);
    vector<vertex> water_vertices;
    vector<unsigned int> water_indices;
    generate_plane(FFT_L, FFT_L, FFT_N, FFT_N, water_vertices, water_indices);
    create_vertex_buffer(water_vertices, water_indices, water_mesh_VAO, water_mesh_VBO, water_mesh_EBO);
    water_mesh_triagnle_size = water_indices.size() / 3;
}

void ifft(GLuint ht_texture, GLuint* pingpong_textures, GLuint& out_texture) {
    //glUseProgram(fft_ifft_shader);
    //glBindImageTexture(0, ht_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
    //glBindImageTexture(1, pingpong_textures[0], 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
    //glBindImageTexture(2, butterfly_indices_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
    //glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_processColumn"), 0);
    //glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_steps"), steps);
    //glDispatchCompute(1, FFT_N, 1);
    //glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    //glBindImageTexture(0, pingpong_textures[0], 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
    //glBindImageTexture(1, pingpong_textures[1], 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
    //glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_processColumn"), 1);
    //glDispatchCompute(1, FFT_N, 1);
    //glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    //out_texture = pingpong_textures[1];

    glUseProgram(fft_ifft_shader);
    glBindImageTexture(0, butterfly_indices_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
    glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_N"), FFT_N);
    glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_Direction"), 0);
    glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_Step_max"), steps - 1);
    GLuint now_in = ht_texture;
    GLuint now_out = pingpong_textures[0];
    for (int i = 0; i < steps; i++) {
        glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_Step"), i);
        glBindImageTexture(1, now_in, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
        glBindImageTexture(2, now_out, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glDispatchCompute(1, FFT_N, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        now_in = now_out;
        now_out = pingpong_textures[0] == now_in ? pingpong_textures[1] : pingpong_textures[0];
    }
    glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_Direction"), 1);
    for (int i = 0; i < steps; i++) {
        glUniform1i(glGetUniformLocation(fft_ifft_shader, "u_Step"), i);
        glBindImageTexture(1, now_in, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA16F);
        glBindImageTexture(2, now_out, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
        glDispatchCompute(1, FFT_N, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        now_in = now_out;
        now_out = pingpong_textures[0] == now_in ? pingpong_textures[1] : pingpong_textures[0];
    }
    out_texture = now_in;
}