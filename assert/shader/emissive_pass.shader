#__COMPUTE_SHADER__
#version 430 core
layout(binding = 0, rgba16f) uniform image2D u_Input;
layout(binding = 1, rgba16f) uniform image2D u_Output;

uniform int u_Direction;

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

float weight[5] = float[](0.227027f, 0.1945946f, 0.1216216f, 0.054054f, 0.016216f);

void main(void) {
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);

	ivec2 step = ivec2(0, 0);
	if (u_Direction > 0) step.x = 1;
	else step.y = 1;

	vec3 result = imageLoad(u_Input, pos).rgb * weight[0];
	for (int i = 1; i < 5; i++) {
		result += imageLoad(u_Input, pos + i * step).rgb * weight[i];
		result += imageLoad(u_Input, pos - i * step).rgb * weight[i];
	}
	imageStore(u_Output, pos, vec4(result, 0.0f));
}
