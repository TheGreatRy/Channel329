# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2025

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		:= ch329cotmi
GAME_TITLE	:= Channel 329: Crimes of the Magically Inclined
GAME_SUBTITLE	:= Detective battles!

# Source code paths

INCLUDEDIRS	:= source

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile

# Additional rules to build the dynamic library:
#
# 1. Build ELF file of main ARM9 binary.
# 2. Build ELF file of library.
# 3. Generate DSL of the library taking both ELF files as input.
# 4. Save the DSL in the NitroFS folder.
# 5. Build NDS ROM.

