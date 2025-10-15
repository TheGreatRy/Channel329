# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2025

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		:= ch329cotmi
GAME_TITLE	:= Channel 329
GAME_SUBTITLE	:= Crimes of the Magically Inclined

# Source code paths

INCLUDEDIRS	:= source
GFXDIRS		:= graphics
BINDIRS		= data

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile