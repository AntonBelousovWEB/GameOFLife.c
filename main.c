#include <stdlib.h>
#include <raylib.h>

#define WIDTH 1920
#define HEIGHT 1080
#define SCALE 0.5

int main() {
    InitWindow(WIDTH, HEIGHT, "GPU Game Of Life");
    ToggleFullscreen();
    SetTargetFPS(60);

    RenderTexture2D frames[2];
    frames[0] = LoadRenderTexture(WIDTH * SCALE, HEIGHT * SCALE);
    SetTextureWrap(frames[0].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(frames[0].texture, TEXTURE_FILTER_POINT);
    frames[1] = LoadRenderTexture(WIDTH * SCALE, HEIGHT * SCALE);
    SetTextureWrap(frames[1].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(frames[1].texture, TEXTURE_FILTER_POINT);
    int current = 0;

    Shader gol_shader = LoadShader(NULL, "gol.glsl");
    Vector2 resolution = {(WIDTH * SCALE), (HEIGHT * SCALE)};
    int resolution_loc = GetShaderLocation(gol_shader, "resolution");
    SetShaderValue(gol_shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);

    BeginTextureMode(frames[0]);
        ClearBackground(BLACK);
        for (int i = 0; i < (WIDTH*SCALE); i++){
            for (int j = 0; j < (HEIGHT*SCALE); j++) {
                float color = (float)(rand() % 2);
                DrawPixel(i, j, ColorFromNormalized((Vector4){color, color, color, 1.0}));
            }
        }
    EndTextureMode();

    while (!WindowShouldClose()) {
        BeginTextureMode(frames[1 - current]);
        ClearBackground(BLACK);
        BeginShaderMode(gol_shader);
        DrawTexture(frames[current].texture, 0, 0, RED);
        EndShaderMode();
        EndTextureMode();

        current = 1 - current;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureEx(frames[current].texture, (Vector2){0, 0}, 0, 1 / SCALE, RED);
        EndDrawing();


    }

    CloseWindow();
}