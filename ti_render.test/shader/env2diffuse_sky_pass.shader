#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;

out VS_OUT {
    vec3 position;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    vs_out.position = aPosition;
    gl_Position = uProjection * uView * vec4(aPosition, 1.0f);
}


#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec3 position;
} fs_in;

uniform samplerCube uEnvironment;

layout(location = 0) out vec3 fDiffuse;

const float PI = 3.14159265359f;
const float SAMPLE_STEP = 0.025f;

void main() {
    vec3 normal = normalize(fs_in.position);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    vec3 right = cross(up, normal);
    up = cross(normal, right);

    vec3 irradiance = vec3(0.0f);
    int sample_index = 0;
    for (float phi = 0.0f; phi < 2.0f * PI; phi += SAMPLE_STEP) {
        for (float theta = 0.0; theta < 0.5f * PI; theta += SAMPLE_STEP) {
            vec3 tangent = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            vec3 direction = tangent.x * right + tangent.y * up + tangent.z * normal;
            irradiance += texture(uEnvironment, direction).rgb * cos(theta) * sin(theta);
            sample_index++;
        }
    }
    fDiffuse = PI * irradiance * (1.0 / float(sample_index));
}
