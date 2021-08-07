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

layout(location = 0) out vec4 fColor;

const float PI = 3.14159265359;

void main() {
    vec3 normal = normalize(fs_in.position);
    vec3 irradiance = vec3(0.0);

    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(up, normal);
    up = cross(normal, right);

    float sampleDelta = 0.025;
    int nrSamples = 0;
    for (float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
    {
        for (float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
            // spherical to cartesian (in tangent space)
            vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            // tangent space to world
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal;

            irradiance += texture(uEnvironment, sampleVec).rgb * cos(theta) * sin(theta);
            nrSamples++;
        }
    }
    irradiance = PI * irradiance * (1.0 / float(nrSamples));

    fColor = vec4(irradiance, 1.0);
}
