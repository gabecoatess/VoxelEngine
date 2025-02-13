#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal; // New normal attribute

uniform mat4 transform;
uniform mat4 sModelMatrix;
uniform mat4 sViewMatrix;
uniform mat4 sProjectionMatrix;

out vec3 color;
out vec2 texCoord;
flat out vec3 normal; // We'll output a flat (non-interpolated) normal

void main()
{
    // Multiply matrices in reverse order (projection, view, model)
    gl_Position = sProjectionMatrix * sViewMatrix * sModelMatrix * vec4(aPos, 1.0);
    color = aColor;
    texCoord = aTexCoord;

    // Transform the normal to world space so it reflects the cube's rotation.
    // If your matrix only rotates and translates (or uniform scales), this is sufficient.
    normal = aNormal;//normal = normalize(mat3(transpose(inverse(sModelMatrix))) * aNormal);
    
    // For non-uniform scaling, consider:
    // normal = normalize(mat3(transpose(inverse(sModelMatrix))) * aNormal);
}