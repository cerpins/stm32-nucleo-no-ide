# Code STM32 NUCLEO-F072RB without CubeIDE
The goal of this repository is an exercise to setup a minimal project for programming the STM32 NUCLEO-F072RB microcontroller without using a pre-generated CubeIDE project or CubeIDE itself.

The microcontroller comes with a ST-LINK/v2(-1) programmer, which we interface using the OpenOCD tool.

Setup follows very helpful [guide by kleinembedded](https://kleinembedded.com/stm32-without-cubeide-part-1-the-bare-necessities), which uses a Nucleo with Cortex-M4 (a little different to my Nucleo with a Cortex-M0).

## Setup
Setup is done on Windows.

1. install `msys2`
0. run `install.sh` from `msys2`
0. run `run.sh` from `msys2`

## Debugging
- **Verify that openocd can install programs on the mcu.** Setup a working CubeIDE blinker program. Go to cubeIDE project `Debug/` and run the openocd command found in `run.sh`. Make sure to target the right `Debug/*.elf` file.
- **Verify that code and ld script works.** Copy either of them to a working CubeIDE project and run it. It took some tries to figure out what's wrong by gradually stripping the CubeIDE project and moving my own code into it. When following the tutorial I missed updating a constant to specify that SRAM size is 16KB, not 32KB.

## Commands
Commands are placed in *.sh scripts

## Deviation from article
- Different board (nucleo-f072rb)
- Different sizing for ISR_VECTOR_SIZE_WORDS (47) and memory.
- I don't find information in reference about having to wait after enabling the peripheral clock, so i do not add dummy statements after enabling it.

## personal notes
- **where to find information?** - look for the STM32 webpage which provides multiple documents. most of all the reference manual, very long document with most information. there is also a datasheet and programming manual. cross-check CubeIDE constants and code in their HAL library if you are unsure about your interpretation of the reference manual addresses and behavior.
- **where to find memory size in datasheet?** it's under flash memory, for me it ranges 0x0800'0000 to 0x0802'0000 which is 128KB of memory (131072B / 1024B = 128KB)
- **what sections should be defined in the .ld?** - 
- **where to find memory alignment in reference?** - it's under flash memory, which is organized as 32-bit wide memory cells, which is 4 bytes. ALIGN() is set as bytes and we use it to increment the location counter to an aligned location.
- **what is . in .ld** - current output location counter. we can use it to set up address variables.
- **what clocks do the peripherals use?** - peripheral clocks are derived from their bus clock (HCLK for AHB or PCLK for APB)
