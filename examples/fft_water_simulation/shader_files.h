#ifndef SHADER_FILES_H
#define SHADER_FILES_H

#include <string>

using namespace std;

string fft_ht_compute_shader = R"delimiter(
#version 430 core
#define G 9.81
#define PI 3.1415926
 
layout (binding = 0, rgba16f) uniform image2D u_H0_k; 
layout (binding = 1, rgba16f) uniform image2D u_H0_kneg_conj;
layout (binding = 2, rgba16f) uniform image2D u_Ht_k_y; 
layout (binding = 3, rgba16f) uniform image2D u_Ht_k_x;
layout (binding = 4, rgba16f) uniform image2D u_Ht_k_z; 
 
uniform float u_Timer;
uniform int u_N;
uniform float u_L;

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

vec2 complex_multiply(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
 
void main(void){
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);

	vec2 h0_k = imageLoad(u_H0_k, pos).xy;
	vec2 h0_kneg_conj = imageLoad(u_H0_kneg_conj, pos).xy;
 
	vec2 k = (2.0 * PI / u_L) * (pos - 0.5f * vec2(u_N, u_N));
 
	float omega_t = sqrt(G * length(k)) * u_Timer;
	float cos_omega_t = cos(omega_t);
	float sin_omega_t = sin(omega_t);

	vec2 ht_y = complex_multiply(h0_k, vec2(cos_omega_t, sin_omega_t)) + complex_multiply(h0_kneg_conj, vec2(cos_omega_t, -1.0f * sin_omega_t));

	k = k / max(0.001f, length(k));

	vec2 ht_x = complex_multiply(ht_y, vec2(0.0f, -1.0f * k.x));
	vec2 ht_z = complex_multiply(ht_y, vec2(0.0f, -1.0f * k.y));

	imageStore(u_Ht_k_y, pos, vec4(ht_y, 0.0f, 0.0f));
	imageStore(u_Ht_k_x, pos, vec4(ht_x, 0.0f, 0.0f));
	imageStore(u_Ht_k_z, pos, vec4(ht_z, 0.0f, 0.0f));
}
)delimiter";

string fft_ifft_compute_shader = R"delimiter(
#version 430 core
#define G 9.81
#define PI 3.1415926

layout (binding = 0, rgba16f) uniform image1D u_Butterfly_indices;
layout (binding = 1, rgba16f) uniform image2D u_Ht_k;
layout (binding = 2, rgba16f) uniform image2D u_Pingpong;

uniform int u_Step;
uniform int u_Step_max;
uniform int u_N;
uniform int u_Direction;

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

vec2 complex_multiply(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

void main(void){
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
	int section = 1 << u_Step;
	for (int i = 0; i < u_N / 2; i++) {
		vec2 w = vec2(cos(2.0f * PI * float(i % section) / float(2 * section)), sin(2.0f * PI * float(i % section) / float(2 * section)));
		int left_index_in_butterfly = (i / section) * (2 * section) + (i % section);
		int right_index_in_butterfly = left_index_in_butterfly + section;
		int left = int(imageLoad(u_Butterfly_indices, left_index_in_butterfly).r);
		int right = int(imageLoad(u_Butterfly_indices, right_index_in_butterfly).r);
			
		ivec2 left_index;
		ivec2 right_index;
		if (u_Direction > 0) {
			left_index = ivec2(pos.y, left);
			right_index = ivec2(pos.y, right);
		}
		else {
			left_index = ivec2(left, pos.y);
			right_index = ivec2(right, pos.y);
		}
			
		vec2 p = imageLoad(u_Ht_k, left_index).xy;
		vec2 q = imageLoad(u_Ht_k, right_index).xy;

		vec2 left_value = p + complex_multiply(w, q);
		vec2 right_value = p - complex_multiply(w, q);
		if (u_Step == u_Step_max) {
			ivec2 left_store_index;
			ivec2 right_store_index;
			float e_left = 1.0f;
			float e_right = 1.0f;
			if (u_Direction > 0) {
				left_store_index = ivec2(pos.y, left_index_in_butterfly);
				right_store_index = ivec2(pos.y, right_index_in_butterfly);
				if ((left_store_index.x + left_store_index.y) % 2 == 0) e_left = -1.0f;
				if ((right_store_index.x + right_store_index.y) % 2 == 0) e_right = -1.0f;
			}
			else {
				left_store_index = ivec2(left_index_in_butterfly, pos.y);
				right_store_index = ivec2(right_index_in_butterfly, pos.y);
			}

			imageStore(u_Pingpong, left_store_index, vec4(e_left * left_value, 0.0f, 0.0f));
			imageStore(u_Pingpong, right_store_index, vec4(e_right * right_value, 0.0f, 0.0f));
		}
		else {
			imageStore(u_Pingpong, left_index, vec4(left_value, 0.0f, 0.0f));
			imageStore(u_Pingpong, right_index, vec4(right_value, 0.0f, 0.0f));
		}
	}
}
)delimiter";

string fft_displacement_compute_shader = R"delimiter(
#version 430 core

layout (binding = 0, rgba16f) uniform image2D u_Height;
layout (binding = 1, rgba16f) uniform image2D u_Displacement_x;
layout (binding = 2, rgba16f) uniform image2D u_Displacement_z;
layout (binding = 3, rgba16f) uniform image2D u_Displacement;

uniform float u_A;
uniform int u_N;

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

void main(void){
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);

	float y = length(imageLoad(u_Height, pos).xy) / (u_N * u_N) * u_A;
    float x = length(imageLoad(u_Displacement_x, pos).xy) / (u_N * u_N);
    float z = length(imageLoad(u_Displacement_z, pos).xy) / (u_N * u_N);

	imageStore(u_Displacement, pos, vec4(x, y, z, 0.0f));
}
)delimiter";

string fft_normal_bubble_compute_shader = R"delimiter(
#version 430 core

layout (binding = 0, rgba16f) uniform image2D u_Displacement;
layout (binding = 1, rgba16f) uniform image2D u_Normal;
layout (binding = 2, rgba16f) uniform image2D u_Bubble;

uniform int u_N;
uniform float u_L;

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

void main(void){
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);

	float unit_len = u_L / (u_N - 1.0f);

	ivec2 xneg_pos = ivec2((pos.x - 1 + u_N) % u_N, pos.y);
	ivec2 xpos_pos = ivec2((pos.x + 1 + u_N) % u_N, pos.y);
	ivec2 zneg_pos = ivec2(pos.x, (pos.y - 1 + u_N) % u_N);
	ivec2 zpos_pos = ivec2(pos.x, (pos.y + 1 + u_N) % u_N);

    vec3 xneg_displacement = imageLoad(u_Displacement, xneg_pos).xyz;
    vec3 xpos_displacement = imageLoad(u_Displacement, xpos_pos).xyz;
    vec3 zneg_displacement = imageLoad(u_Displacement, zneg_pos).xyz;
    vec3 zpos_displacement = imageLoad(u_Displacement, zpos_pos).xyz;

	vec3 delta_x = xpos_displacement - xneg_displacement + 2.0f * vec3(unit_len, 0.0f, 0.0f);
	vec3 delta_z = zpos_displacement - zneg_displacement + 2.0f * vec3(0.0f, 0.0f, unit_len);

	vec3 normal = normalize(cross(delta_z, delta_x));
	normal = 0.5f * (normal + vec3(1.0f));

	vec3 ddx = xpos_displacement - xneg_displacement;
	vec3 ddz = zpos_displacement - zneg_displacement;

	float jacobian = (1.0f + ddx.x) * (1.0f + ddz.z) - ddx.z * ddz.x;
	float bubble = clamp(1.0f - jacobian, 0.0f, 1.0f);

	imageStore(u_Normal, pos, vec4(normal.x, normal.z, normal.y, 0.0f));
	imageStore(u_Bubble, pos, vec4(bubble, bubble, bubble, 0.0f));
}
)delimiter";

string fft_ifft_0_compute_shader = R"delimiter(
#version 430 core
 
#define N 512
#define PI	3.1415926
 
uniform int u_processColumn;
 
uniform int u_steps;
 
layout (binding = 0, rgba16f) uniform image2D u_imageIn; 
layout (binding = 1, rgba16f) uniform image2D u_imageOut;
layout (binding = 2, rgba16f) uniform image1D u_imageIndices;
 
shared vec2 sharedStore[N];
 
// as N = 512, so local size is 512/2 = 256. Processing two fields per invocation.
layout (local_size_x = 256, local_size_y = 1, local_size_z = 1) in;
 
vec2 mulc(vec2 a, vec2 b)
{
	vec2 result;
	
	result.x = a.x * b.x - a.y * b.y;
	result.y = a.x * b.y + b.x * a.y;
	
	return result;
}
 
vec2 rootOfUnityc(int n, int k)
{
	vec2 result;
	
	result.x = cos(2.0 * PI * float(k) / float(n));
	result.y = sin(2.0 * PI * float(k) / float(n));
 
	return result;
}
 
void main(void)
{
	ivec2 leftStorePos;
	ivec2 rightStorePos;
 
	ivec2 leftLoadPos;
	ivec2 rightLoadPos;
 
	int xIndex = int(gl_GlobalInvocationID.x);
	int yIndex = int(gl_GlobalInvocationID.y);
 
	int leftStoreIndex = 2 * xIndex;
	int rightStoreIndex = 2 * xIndex + 1;
 
	int leftLoadIndex = int(imageLoad(u_imageIndices, leftStoreIndex).r);
	int rightLoadIndex = int(imageLoad(u_imageIndices, rightStoreIndex).r);
 
	if (u_processColumn == 0)
	{
		leftLoadPos = ivec2(leftLoadIndex, yIndex);
		rightLoadPos = ivec2(rightLoadIndex, yIndex);
 
		leftStorePos = ivec2(leftStoreIndex, yIndex);
		rightStorePos = ivec2(rightStoreIndex, yIndex);
	}
	else
	{
		leftLoadPos = ivec2(yIndex, leftLoadIndex);
		rightLoadPos = ivec2(yIndex, rightLoadIndex);
 
		leftStorePos = ivec2(yIndex, leftStoreIndex);
		rightStorePos = ivec2(yIndex, rightStoreIndex);
	}
 
	vec2 leftValue = imageLoad(u_imageIn, leftLoadPos).xy;
	vec2 rightValue = imageLoad(u_imageIn, rightLoadPos).xy;

	sharedStore[leftStoreIndex] = leftValue;
	sharedStore[rightStoreIndex] = rightValue;
 

	memoryBarrierShared();
	barrier();
	
	
	int numberSections = N / 2;
	int numberButterfliesInSection = 1;
 
	int currentSection = xIndex;
	int currentButterfly = 0;
 

	for (int currentStep = 0; currentStep < u_steps; currentStep++)
	{	

		int leftIndex = currentButterfly + currentSection * numberButterfliesInSection * 2;
		int rightIndex = currentButterfly + numberButterfliesInSection + currentSection * numberButterfliesInSection * 2;

		leftValue = sharedStore[leftIndex];
		rightValue = sharedStore[rightIndex];
			 						
		vec2 currentW = rootOfUnityc(numberButterfliesInSection * 2, currentButterfly);
	
		vec2 multiply;
		vec2 addition;
		vec2 subtraction;
 
		multiply = mulc(currentW, rightValue);	
		
		addition = leftValue + multiply;
		subtraction = leftValue - multiply; 
 
		sharedStore[leftIndex] = addition;
		sharedStore[rightIndex] = subtraction;		
 

		memoryBarrierShared();
 

		numberButterfliesInSection *= 2;
		numberSections /= 2;
 
		currentSection /= 2;
		currentButterfly = xIndex % numberButterfliesInSection;
 

		barrier();
	}
	
	if (u_processColumn == 1)
	{
		if ((leftStorePos.x + leftStorePos.y) % 2 == 0)
		{
			sharedStore[leftStoreIndex] *= -1.0;
		}
		if ((rightStorePos.x + rightStorePos.y) % 2 == 0)
		{
			sharedStore[rightStoreIndex] *= -1.0;			
		}
		
		memoryBarrierShared();
	}
	
	imageStore(u_imageOut, leftStorePos, vec4(sharedStore[leftStoreIndex], 0.0, 0.0));
	imageStore(u_imageOut, rightStorePos, vec4(sharedStore[rightStoreIndex], 0.0, 0.0));
}
)delimiter";


string sky_vertex_shader = R"delimiter(
#version 330 core
layout(location = 0) in vec3 aPosition;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 tex_coord;

void main() {
    tex_coord = normalize(aPosition);
    gl_Position = uProjection * uView * vec4(aPosition, 1.0f);
}
)delimiter";

string sky_fragment_shader = R"delimiter(
#version 330 core
in vec3 tex_coord;

uniform samplerCube uSky;

out vec3 fColor;

void main() {
    fColor = texture(uSky, normalize(tex_coord)).rgb;
}
)delimiter";

string water_vertex_shader = R"delimiter(
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTex_coord;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;

uniform mat4 uProjection;
uniform mat4 uView;
uniform sampler2D uDisplacement;

out vec3 position;
out vec2 tex_coord;
out vec3 normal;
out mat3 TBN;

void main() {
    position = aPosition + texture(uDisplacement, aTex_coord).rgb;
    tex_coord = aTex_coord;
    normal = aNormal;
    vec3 B = normalize(cross(aNormal,aTangent));
    TBN = transpose(mat3(aTangent, B, aNormal));

    gl_Position = uProjection * uView * vec4(position, 1.0f);
}
)delimiter";

    
string water_fragment_shader = R"delimiter(
#version 330 core
in vec3 position;
in vec2 tex_coord;
in vec3 normal;
in mat3 TBN;

uniform samplerCube uSky;
uniform sampler2D uNormal;
uniform sampler2D uBubble;
uniform vec3 uView_pos;

out vec3 fColor;

void main() {
	vec3 N = normalize(inverse(TBN) * (texture(uNormal, tex_coord).rgb * 2.0f - 1.0f));
	vec3 V = normalize(uView_pos - position);
	vec3 R = reflect(-1.0f * V, N);

	float F = pow(1.0f - max(0.0f, dot(N, V)), 1);
	F = clamp(F, 0.0f, 1.0f);

	vec3 diffuse = vec3(0.04f, 0.16f, 0.47f);
	vec3 specular = texture(uSky, R).rgb;

	vec3 color = F * specular + (1.0f - F) * diffuse;
	
	float bubble = 10.0f * texture(uBubble, tex_coord).r;

    fColor = bubble * vec3(1.0f, 1.0f, 1.0f) + (1.0f - bubble) * color;
}
)delimiter";

#endif