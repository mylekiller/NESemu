#include <iostream>
#include <SDL.h>
#include "nes_lib/Gamepak.h"
#include "nes_lib/PPU.h"
#include "nes_lib/memory.h"
#include "nes_lib/cpu.h"

#define NES_A_BUTTON 1
#define NES_B_BUTTON 0
#define NES_START_BUTTON 9
#define NES_SELECT_BUTTON 8

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR,
                "SDL_Init Error",
                SDL_GetError(),
                nullptr);
        return -1;
    }

    const char *error = nullptr;

    if (argc != 2) {
        SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR,
                "Usage error",
                "Usage: NESEmu <rom_file_path>",
                nullptr);
        return -1;
    }

    SDL_Joystick * joystick = nullptr;

    /*
    if (SDL_NumJoysticks() < 1) {
        SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR,
                "Usage error",
                "No Joypad Connected",
                nullptr);
        return -1;
    }
    */

    SDL_Window * sdl_window;
    SDL_Renderer * sdl_renderer;
    SDL_CreateWindowAndRenderer(100, 100, SDL_WINDOW_SHOWN, &sdl_window, &sdl_renderer); //TODO: Sizes Need Changed to actual
    if (!sdl_window || !sdl_renderer) {
        SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR,
                "System Error",
                "Could not create window or renderer",
                nullptr);
        return -1;
    }

    SDL_SetWindowTitle(sdl_window, "Ethan And Kyle NESEmu v0.1");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_RenderSetLogicalSize(sdl_renderer, 100, 100); //TODO: Sizes need to be changed to actual

    SDL_Texture * sdl_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 100, 100); //TODO: Update Sizes

    joystick = SDL_JoystickOpen(0);

    SDL_Delay(1000);

    //TODO: Implement the rest of the main including the game loop

    std::string rom_filename = argv[1];

    Gamepak rom_gamepak = Gamepak(rom_filename);
    if (rom_gamepak.initialize()) return EXIT_FAILURE;

    PPU ppu;

    NesCPUMemory memory(&ppu, &rom_gamepak);
    NesCpu cpu(&memory);

    cpu.power_up();

    cpu.setPC(0xC000);

    size_t counter = 0;

    while(counter < 8992) {
        cpu.step();
        //memory.printTest();
        counter++;
    }

    return 0;
}