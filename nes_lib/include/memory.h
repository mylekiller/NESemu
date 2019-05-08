/*
 * memory.h file contains the data structure for the NES's internal RAM
 */

#ifndef NESEMU_MEMORY_H
#define NESEMU_MEMORY_H

#include <cstdlib>
#include "Gamepak.h"
#include "PPU.h"
#include "utils.h"
#include "InputDevice.h"
#include "APU.h"

#define CPU_RAM_SIZE 2*KILO // 2KBytes

class APU;
class NesCPUMemory {
private:
    uint8_t cpu_ram[CPU_RAM_SIZE] = {0};
    Gamepak *gamepak;
    APU *apu;
    PPU *ppu;
    InputDevice *joypad1;
    InputDevice *joypad2;

public:
    NesCPUMemory(PPU *ppu, APU *apu, Gamepak *gamepak, InputDevice *joypad1, InputDevice *joypad2);
    ~NesCPUMemory();

    uint8_t read_byte(uint16_t address);
    nes_cpu_clock_t write_byte(uint16_t address, uint8_t value);
    uint16_t read_word(uint16_t address);
    uint16_t read_word_page_bug(uint16_t address);
    void write_word(uint16_t address, uint16_t value);
    void stack_write_word(uint16_t address, uint16_t value);
    void map_memory(uint16_t address, uint8_t * data, size_t size);
//    void printTest();
};

#endif //NESEMU_MEMORY_H
