#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define WIDTH 1920
#define HEIGHT 1080
#define SCALE 0.5

#define NUM_ISLANDS 100
#define MAX_SOUNDS 10

int main() {
    InitWindow(WIDTH, HEIGHT, "GPU Game Of Life");
    ToggleFullscreen();
    SetTargetFPS(60);
    
    InitAudioDevice();
    Sound sounds[MAX_SOUNDS];
    int numSounds = 0;
    for (int i = 0; i < MAX_SOUNDS; i++) {
        char filename[64];
        sprintf(filename, "./resources/muz/sound%d.ogg", i);
        sounds[i] = LoadSound(filename);
        if (sounds[i].stream.buffer != NULL) {
            numSounds++;
        } else {
            UnloadSound(sounds[i]);
            break;
        }
    }

    int currentSoundIndex = 0;
    bool isReSpawn = false;
    
    RenderTexture2D frames[2];
    frames[0] = LoadRenderTexture(WIDTH * SCALE, HEIGHT * SCALE);
    SetTextureWrap(frames[0].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(frames[0].texture, TEXTURE_FILTER_POINT);
    frames[1] = LoadRenderTexture(WIDTH * SCALE, HEIGHT * SCALE);
    SetTextureWrap(frames[1].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(frames[1].texture, TEXTURE_FILTER_POINT);
    int current = 0;

    Shader gol_shader = LoadShader(NULL, "./resources/gol.glsl");
    Vector2 resolution = {(WIDTH * SCALE), (HEIGHT * SCALE)};
    int resolution_loc = GetShaderLocation(gol_shader, "resolution");
    SetShaderValue(gol_shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);
    
    float zoomFactor = 0.5f;

    BeginTextureMode(frames[0]);
    ClearBackground(BLACK);
    for (int i = 0; i < (WIDTH * SCALE); i++) {
        for (int j = 0; j < (HEIGHT * SCALE); j++) {
            float color = (float)(rand() % 2);
            DrawPixel(i, j, ColorFromNormalized((Vector4){color, color, color, 1.0}));
        }
    }
    EndTextureMode();
    
    int currentCol = 0;

    while (!WindowShouldClose()) {
        Color frameColors[13] = { RED, GRAY, BLUE, YELLOW, PINK, ORANGE, GREEN, PURPLE, WHITE, GOLD, BROWN, LIME, MAGENTA }; 
        Color currentColor = frameColors[currentCol];
        
        if (IsKeyPressed(KEY_SPACE)) {
            if(currentSoundIndex >= numSounds) {
                StopSound(sounds[currentSoundIndex - 1]);
                currentSoundIndex = 0;
            } else {
                if (currentSoundIndex > 0) {
                    StopSound(sounds[currentSoundIndex - 1]);
                }
                PlaySound(sounds[currentSoundIndex]);
                currentSoundIndex += 1;
            }
        }
        
        int length = sizeof(frameColors) / sizeof(frameColors[0]);
        
        if (IsKeyPressed(KEY_RIGHT)) {
            currentCol = (currentCol + 1 >= length) ? 0 : currentCol + 1;
        }
        if (IsKeyPressed(KEY_LEFT)) {
            currentCol = (currentCol - 1 < 0) ? length - 1 : currentCol - 1;
        }


        if (IsKeyPressed(KEY_KP_ADD)) {
            zoomFactor += 0.1f;
        } else if (IsKeyPressed(KEY_KP_SUBTRACT)) {
            zoomFactor -= 0.1f;
            if (zoomFactor < 0.1f) zoomFactor = 0.1f; 
        }

        BeginTextureMode(frames[1 - current]);
        ClearBackground(BLACK);
        BeginShaderMode(gol_shader);
        DrawTexturePro(frames[current].texture, (Rectangle){
        0, 0, 
        frames[current].texture.width, 
        -frames[current].texture.height}, 
                       (Rectangle){0, 0, WIDTH * zoomFactor, HEIGHT * zoomFactor}, 
                       (Vector2){0, 0}, 0.0f, currentColor);
        EndShaderMode();
        
        if (IsKeyDown(KEY_RIGHT_CONTROL)) {
            isReSpawn = !isReSpawn;
        }

        for (int k = 0; k < (isReSpawn ? 1 : NUM_ISLANDS); k++) {
            int x = GetRandomValue(0, WIDTH * zoomFactor);
            int y = GetRandomValue(0, HEIGHT * zoomFactor);

            if ((!isReSpawn && IsKeyDown(KEY_KP_SUBTRACT) && zoomFactor > 0.2f) || isReSpawn) {
                for (int i = -5; i <= 5; i++) {
                    for (int j = -5; j <= 5; j++) {
                        if (GetRandomValue(0, 10) > 6) {
                            DrawPixel(x + i, y + j, WHITE);
                        }
                    }
                }
            }
        }


        EndTextureMode();

        current = 1 - current;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(frames[current].texture, (Rectangle){
        0, 0, 
        frames[current].texture.width, 
        -frames[current].texture.height}, 
                       (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()}, 
                       (Vector2){0, 0}, 0.0f, currentColor);
        DrawText("Press SPACE to PLAY the sound!", 30, 30, 15, WHITE);
        DrawText(TextFormat("Press '<- or ->' to Change Color %d", currentCol + 1), 30, 60, 15, WHITE);
        DrawText((isReSpawn ? "Turn OFF respawn 'R Ctrl'" : "Turn ON respawn 'R Ctrl'"), 30, 90, 15, WHITE);
        EndDrawing();
    }
    
      
    CloseAudioDevice();
    CloseWindow();
    return 0;
}