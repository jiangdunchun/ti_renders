#version 450

layout(binding = 0) uniform UniformBufferObject {
    float rotation;
} ubo;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

void main() {
    float cos_r = cos(ubo.rotation);
    float sin_r = sin(ubo.rotation);

    vec2 n_pos = vec2(inPosition.x * cos_r - inPosition.y * sin_r, inPosition.x * sin_r + inPosition.y * cos_r);
    gl_Position = vec4(n_pos, 0.0, 1.0);
    fragTexCoord = inTexCoord;
}