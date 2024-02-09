#version 330
in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution;

float sample_position(vec2 pos) {
    pos = vec2(pos.x, -pos.y);
    return texture(texture0, pos).r;
}

void main() {

    vec2 pixelsize = vec2(1.0, 1.0) / resolution;

    float alive = sample_position(fragTexCoord);

    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (abs(i) + abs(j) != 0) {
                if (sample_position(fragTexCoord + (vec2(i, -j) * pixelsize)) == 1.0) {
                    count++;
                }
            }
        }
    }
    finalColor = texture(texture0, vec2(fragTexCoord.x, -fragTexCoord.y));
    finalColor -= vec4(0.5, 0.03, 0.01, 0.0);
    if (alive == 1.0) {
        if (count == 2) {finalColor = vec4(vec3(1.0), 1.0);}
        if (count == 3) {finalColor = vec4(vec3(1.0), 1.0);}
    } else {
        if (count == 3) {finalColor = vec4(vec3(1.0), 1.0);}
    }
}