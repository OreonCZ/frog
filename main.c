#include "raylib.h"
#include "raymath.h"


float rotationSign = 1.0f;

void changeDirection(){
    if(IsMouseButtonPressed(0)){
        rotationSign *= -1.0f;
    }
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int pixelWidth = 190;
    const int pixelHeight = 102;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - models loading");
    InitAudioDevice();

    Music music = LoadMusicStream("resources/music/crazyFrog.mp3");
    PlayMusicStream(music);

    Camera camera = { 
        .position = (Vector3){ 15.0f, 0.0f, 2.0f },
        .target = (Vector3){ 0.0f, 0.0f, -1.0f },
        .up = (Vector3){ 0.0f, 0.0f, PI * 0.5 },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
     };

    Model model = LoadModel("resources/models/obj/frog.obj");
    Texture2D texture = LoadTexture("resources/models/obj/frogTexture.jpg");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Vector3 position = { 0.0f, 0.0f, -2.0f };

    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    RenderTexture2D renderTexture = LoadRenderTexture(pixelWidth, pixelHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        BeginTextureMode(renderTexture);
        ClearBackground(WHITE);
        BeginMode3D(camera);
                DrawModel(model, position, 1.0f, WHITE);
                model.transform = MatrixRotateXYZ((Vector3){ 0.0f, 0.0f, DEG2RAD*(GetTime() * (300.0f * rotationSign))});
                changeDirection();
        EndMode3D();
        EndTextureMode();
        
        //gg
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
                renderTexture.texture, 
                (Rectangle){ 0, 0, (float)renderTexture.texture.width, -(float)renderTexture.texture.height }, 
                (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight }, 
                (Vector2){ 0, 0 }, 
                0.0f, 
                WHITE
            );

        EndDrawing();
    }
    UnloadMusicStream(music);
    UnloadRenderTexture(renderTexture);
    UnloadTexture(texture);
    UnloadModel(model);

    CloseWindow();

    return 0;
}