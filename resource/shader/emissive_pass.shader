#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTex_coord;

out VS_OUT {
    vec2 tex_coord;
} vs_out;

void main() 
{
    vs_out.tex_coord = aTex_coord;
    gl_Position = vec4(aPosition, 1.0f);
}

#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec2 tex_coord;
} fs_in;

uniform bool uHorizontal;
uniform sampler2D uEmissive;

layout(location = 0) out vec3 fEmissive;

float weight[5] = float[] (0.227027f, 0.1945946f, 0.1216216f, 0.054054f, 0.016216f);

void main() {
    vec2 tex_offset = 1.0 / textureSize(uEmissive, 0);
    vec3 result = texture(uEmissive, fs_in.tex_coord).rgb * weight[0];
    if(uHorizontal) {
        for(int i = 1; i < 5; ++i) {
            result += texture(uEmissive, fs_in.tex_coord + vec2(tex_offset.x * i, 0.0f)).rgb * weight[i];
            result += texture(uEmissive, fs_in.tex_coord - vec2(tex_offset.x * i, 0.0f)).rgb * weight[i];
        }
    }
    else {
        for(int i = 1; i < 5; ++i) {
            result += texture(uEmissive, fs_in.tex_coord + vec2(0.0f, tex_offset.y * i)).rgb * weight[i];
            result += texture(uEmissive, fs_in.tex_coord - vec2(0.0f, tex_offset.y * i)).rgb * weight[i];
        }
    }
    fEmissive = result;
}
