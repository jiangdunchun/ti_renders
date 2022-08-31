#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    vec4 position = uProjection * uView * uModel * vec4(aPosition, 1.0f);
    gl_Position = position + vec4(0.0f, 0.0f, 0.00001f, 0.0f);
}


#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
uniform vec4 uID;

layout(location = 0) out vec4 fID;

void main() {
    fID = uID;
}
