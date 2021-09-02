#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTex_coord;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBi_tangent;

out VS_OUT {
    vec3 frag_position;
    vec2 tex_coord;
    vec3 normal;
    mat3 TBN;
    mat4 pv;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    vec4 model_pos = uModel * vec4(aPosition, 1.0f);

    vs_out.pv = uProjection * uView;

    vs_out.frag_position = model_pos.rgb;

    vs_out.tex_coord = aTex_coord;

    vs_out.normal = normalize((uModel * vec4(aNormal, 1.0f)).rgb);

    mat3 model_mat = mat3(transpose(inverse(uModel)));
    vec3 T = normalize(model_mat * aTangent);
    vec3 N = normalize(model_mat * aNormal);
    vec3 B = normalize(cross(N,T));
    vs_out.TBN = transpose(mat3(T, B, N));

    gl_Position = vs_out.pv * model_pos;
}

#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec3 frag_position;
    vec2 tex_coord;
    vec3 normal;
    mat3 TBN;
    mat4 pv;
} fs_in;

uniform vec3 uView_position;
uniform vec2 uScreen;
uniform sampler2D uPosition;
uniform sampler2D uBase_color;
uniform samplerCube uEnvironment;

layout(location = 0) out vec4 fColor;

vec2 get_pixel(vec3 position) {
    vec4 p_pos = fs_in.pv * vec4(position, 1.0f);
    vec2 p_uv = 0.5f * (p_pos.xy / p_pos.w + vec2(1.0f));
    return vec2(p_uv.x * uScreen.x, p_uv.y * uScreen.y);
}

void main() {
    fColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec3 V = normalize(uView_position - fs_in.frag_position);
    vec3 R = normalize(reflect(-1.0f * V, fs_in.normal));

    vec2 pixel = gl_FragCoord.xy;
    vec2 uv = vec2(pixel.x / uScreen.x, pixel.y / uScreen.y);
    vec3 position = fs_in.frag_position;

    vec4 b_color = texture(uBase_color, uv);
    float alpha = 5.0f;
    if (b_color.a > 0.1f) alpha = length(texture(uPosition, uv).rgb - position);
    if (alpha > 5.0f) alpha = 5.0f;
    alpha = alpha / 5.0f;
    fColor.rgb += b_color.rgb * (1.0f - alpha);

    vec2 dst_pixel = get_pixel(position + R);
    vec2 delta_pixel = dst_pixel - pixel;
    float scale_pixel = 1.0f;
    if (abs(delta_pixel.x) > abs(delta_pixel.y)) scale_pixel = 1.0f / abs(delta_pixel.x);
    else scale_pixel = 1.0f / abs(delta_pixel.y);
    delta_pixel = scale_pixel * delta_pixel;
    vec3 step = scale_pixel * R;

    int index = -1;
    for (int i = 0; i < 1000; i++) {
        vec2 n_pixel = pixel + vec2(int(delta_pixel.x * i), int(delta_pixel.y * i));
        vec2 n_uv = vec2(n_pixel.x / uScreen.x, n_pixel.y / uScreen.y);
        vec3 n_position = position + i * step;
        if (n_uv.x < 0.0f || n_uv.x > 1.0f || n_uv.y < 0.0f || n_uv.y > 1.0f) break;
        if (texture(uBase_color, n_uv).a > 0.1f 
            && length(texture(uPosition, n_uv).rgb - uView_position) < length(n_position - uView_position)
            && abs(length(texture(uPosition, n_uv).rgb - uView_position) - length(n_position - uView_position)) < 1.0f) {
                index = i;
                break;
            }
    }

    if (index > 0) {
        vec2 n_pixel = pixel + vec2(int(delta_pixel.x * index), int(delta_pixel.y * index));
        vec2 n_uv = vec2(n_pixel.x / uScreen.x, n_pixel.y / uScreen.y);
        fColor.rgb += texture(uBase_color, n_uv).rgb;
    }
    else {
        fColor.rgb += texture(uEnvironment, R).rgb;
    }
}
