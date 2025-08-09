#define CLAY_IMPLEMENTATION
#include "./clay/renderers/raylib/clay_renderer_raylib.c" //raylib is used
#include "raylib.h"
#include "raymath.h"
#include "./clay/clay.h" // clay is used
#include <stdio.h>
#include <stdlib.h>


const int screenWidth = 800;
const int screenHeight = 600;
const Clay_Color COLOR_LIGHT = (Clay_Color){224, 215, 210, 255};
const Clay_Color COLOR_RED = (Clay_Color){168, 66, 28, 255};
const Clay_Color COLOR_ORANGE = (Clay_Color){225, 138, 50, 255};

// Add these variable declarations
float mousePositionX = 0;
float mousePositionY = 0;
bool isMouseDown = false;
float mouseWheelX = 0;
float mouseWheelY = 0;
float deltaTime = 0;
// Texture2D profilePicture;

void HandleClayError(Clay_ErrorData errorData) {
    printf("Clay Error: %.*s\n", (int)errorData.errorText.length, errorData.errorText.chars);
}
int main(void) {
    Clay_Raylib_Initialize(800, 600, "My Window", FLAG_WINDOW_RESIZABLE);
    uint64_t requiredMemory = Clay_MinMemorySize();
    Clay_Arena arena = (Clay_Arena){
        .memory = malloc(requiredMemory),
        .capacity = requiredMemory
    };
    Clay_Initialize(arena, (Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    }, (Clay_ErrorHandler) {
        .errorHandlerFunction = HandleClayError,
        .userData = NULL
    });

    // profilePicture = LoadTexture("C:/Users/dey87/Downloads/ChicoFace.jpg");
    SetTargetFPS(60);
    // Font declaration
    Font fonts[3];
    fonts[0] = GetFontDefault();

    while (!WindowShouldClose()) {
        Clay_SetLayoutDimensions((Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    });
        Clay_BeginLayout();
        //Build UI here
        CLAY({

            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_GROW()
                },
                .padding = { 10, 10, 10, 10 },
                .childGap = 5,
                .layoutDirection = CLAY_LEFT_TO_RIGHT
            },
            .backgroundColor = {250, 244, 230, 255}
        }) {}
        Clay_RenderCommandArray render_commands = Clay_EndLayout();
        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(render_commands, fonts);
        EndDrawing();
    }
}
