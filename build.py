#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

nitrofs = NitroFS()
nitrofs.add_nflib_bg_tiled(['assets/map'], 'bg')
nitrofs.add_nflib_bg_8bit(['assets/backgrounds'], 'bmp')
nitrofs.add_nflib_sprite_256(['assets/characters/cameron/idle'], 'sprite')
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'nflib'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDSEXT}/nflib']
)
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9, nitrofs],
    nds_path='ch329cotmi.nds',
    game_title='Channel329',
    game_subtitle='Crimes of the Magically Inclined',
    game_author='TheGreatRy'
    #game_icon='icon.bmp'
)
nds.generate_nds()

nds.run_command_line_arguments()