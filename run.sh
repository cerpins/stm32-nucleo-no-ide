#!/bin/bash

set -e
mkdir -p out

# compile
arm-none-eabi-gcc \
    ./src/startup.c ./src/main.c \
    -T ./src/linker.ld \
    -o ./out/main.elf \
    -mcpu=cortex-m0 -mthumb -nostdlib

# upload
openocd \
    -f interface/stlink.cfg \
    -f target/stm32f0x.cfg \
    -c "program ./out/main.elf verify reset exit"
