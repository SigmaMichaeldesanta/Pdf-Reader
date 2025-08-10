#define CLAY_IMPLEMENTATION
#include "./clay/renderers/raylib/clay_renderer_raylib.c" //raylib is used
#include "raylib.h"
#include "raymath.h"
#include "./clay/clay.h" // clay is used
#include <stdio.h>
#include <stdlib.h>


const int screenWidth = 800;
const int screenHeight = 600;
const int MIN_WIDTH  = 800;
const int MIN_HEIGHT = 600;
const uint32_t FONT_ID_BODY_16 = 0;


void HandleClayError(Clay_ErrorData errorData) {
    printf("Clay Error: %.*s\n", (int)errorData.errorText.length, errorData.errorText.chars);
}
void RenderHeaderButton(Clay_String text) {
    CLAY({
        .layout = { .padding = { 10, 10, 10, 10 } },
        .backgroundColor = {140, 140, 140, 255},
        .cornerRadius = 5
    }) {
        CLAY_TEXT(
            text,
            CLAY_TEXT_CONFIG({
                .fontId = FONT_ID_BODY_16,
                .fontSize = 20,
                .textColor = {255, 255, 255, 255}
            })
        );
    }
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
    SetTargetFPS(0);
    // Font declaration
    Font fonts[3] = { 0 };  // Initialize array to zero
    fonts[FONT_ID_BODY_16] = LoadFont("C:/New APPLICATION/resources/Roboto/static/Roboto-Regular.ttf");
    if (fonts[1].baseSize == 0) {
        // Font failed to load, fall back to default
        fonts[1] = GetFontDefault();
        printf("Failed to load Roboto font, falling back to default\n");
    }
    SetTextureFilter(fonts[1].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    while (!WindowShouldClose()) {
        // Min Size of the app if resized more than the limit it will snap back
        int w = GetScreenWidth();
        int h = GetScreenHeight();
        if (w < MIN_WIDTH || h < MIN_HEIGHT) {
            SetWindowSize(
                (w < MIN_WIDTH)  ? MIN_WIDTH  : w,
                (h < MIN_HEIGHT) ? MIN_HEIGHT : h
            );
        }
        Clay_SetLayoutDimensions((Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    });
        Clay_Sizing LayoutExpand = {
            .width = CLAY_SIZING_GROW(),
            .height = CLAY_SIZING_GROW()
        };
        Clay_BeginLayout();
        //Build UI here
        CLAY({
            CLAY_ID("OuterContainer"),
            .layout = {
                .sizing = LayoutExpand,
                .padding = { 10, 10, 10, 10 },
                .childGap = 5,
                .layoutDirection = CLAY_TOP_TO_BOTTOM
            },
            .backgroundColor = {242, 242, 240, 255}
        }) { // Child Element

            CLAY({
            CLAY_ID("HeaderBar"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_FIXED(60)

                },
                .childGap = 10,
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
                .padding = { 10, 10, 10, 10 }
            },
            .backgroundColor = {210, 205, 200, 255},
                .cornerRadius = 5
        }) {//Header buttons are here
                CLAY({
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            }
        }
    }) {}
                RenderHeaderButton(CLAY_STRING("Home"));
                RenderHeaderButton(CLAY_STRING("Files"));
                RenderHeaderButton(CLAY_STRING("Favorite"));
            }
            CLAY({
                CLAY_ID("LowerContainer"),
                    .layout = {
                        .sizing = LayoutExpand,
                        .childGap = 10,
                    .layoutDirection = CLAY_LEFT_TO_RIGHT
                    // Add this line - creates 10px gap between children // Also specify direction explicitly
            },
            }) {// Child
                CLAY({
                    CLAY_ID("SideBar"),
                    .layout = {
                        .sizing = {
                        .width = CLAY_SIZING_FIXED(200),
                        .height = CLAY_SIZING_GROW()},
                        .layoutDirection = CLAY_TOP_TO_BOTTOM,
                        .padding = { 10, 10, 10, 10 }
                    },
                    .backgroundColor = {210, 205, 200, 255},
                    // .border = {0, 0, 0, 255},
                    .cornerRadius = 5
                }){}
                CLAY({
                    CLAY_ID("BookGrid"),
                    .layout = {
                        .sizing = {
                        .width = CLAY_SIZING_GROW(), // screen - sidebar - gap - padding
                        .height = CLAY_SIZING_GROW()},
                    .layoutDirection = CLAY_TOP_TO_BOTTOM
                    },
                    .backgroundColor = {210, 205, 200, 255},
                    .cornerRadius = 5
                }){}
            }
        }


        Clay_RenderCommandArray render_commands = Clay_EndLayout();
        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(render_commands, fonts);
        EndDrawing();
    }
}
