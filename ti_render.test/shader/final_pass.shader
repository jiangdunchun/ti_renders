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
uniform sampler2D uBackground;
uniform sampler2D uEmissive;

out vec4 fColor;

void main() {
    float alpha = texture(uColor, fs_in.tex_coord).a;
    vec3 color = texture(uColor, fs_in.tex_coord).rgb * alpha + texture(uBackground, fs_in.tex_coord).rgb * (1.0f - alpha);
    color += texture(uEmissive, fs_in.tex_coord).rgb;
    color = color / (color + vec3(1.0f));
    color = pow(color, vec3(1.0f / 2.2f));
    fColor = vec4(color, 1.0f);
}
