#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTex_coord;

out VS_OUT {
    vec2 tex_coord;
} vs_out;

void main() {
    vs_out.tex_coord = aTex_coord;
    gl_Position = vec4(aPosition, 1.0f);
}

#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec2 tex_coord;
} fs_in;

uniform sampler2D uColor;
uniform sampler2D uWater;
uniform sampler2D uBackground;
uniform sampler2D uEmissive;

out vec4 fColor;

void main() {
    vec3 color = vec3(0.0f);
    if (texture(uWater, fs_in.tex_coord).a > 0.001f) {
        color = texture(uWater, fs_in.tex_coord).rgb * texture(uWater, fs_in.tex_coord).a + texture(uBackground, fs_in.tex_coord).rgb * (1.0f - texture(uWater, fs_in.tex_coord).a);
    }
    else {
        color = texture(uColor, fs_in.tex_coord).rgb * texture(uColor, fs_in.tex_coord).a + texture(uBackground, fs_in.tex_coord).rgb * (1.0f - texture(uColor, fs_in.tex_coord).a);
    }
    color += texture(uEmissive, fs_in.tex_coord).rgb;
    color = color / (color + vec3(1.0f));
    color = pow(color, vec3(1.0f / 2.2f));
    fColor = vec4(color, 1.0f);
}
