#version 330 core

flat in vec3 normal; // Receive the flat normal computed per face
in vec2 texCoord;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
    float brightness = 1.0;
    
    // Use the dominant normal axis to simulate Minecraft-style face lighting.
    // Top face: brightest; bottom face: darkest; side faces: intermediate brightness.
    if (abs(normal.y) > 0.9) {
        brightness = normal.y > 0.0 ? 1.0 : 0.5;
    } else if (abs(normal.x) > 0.9) {
        brightness = normal.x > 0.0 ? 0.8 : 0.6;
    } else if (abs(normal.z) > 0.9) {
        brightness = normal.z > 0.0 ? 0.8 : 0.6;
    }
    
    // Sample the texture and apply the brightness
    vec4 texColor = texture(tex, texCoord);
    FragColor = vec4(texColor.rgb * brightness, texColor.a);
}