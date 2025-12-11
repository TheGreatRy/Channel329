#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

nitrofs = NitroFS()
nitrofs.add_nflib_bg_tiled(['assets/bg'], 'bg')
nitrofs.add_nflib_bg_8bit(['assets/bitmaps'], 'bmp')

nitrofs.add_nflib_sprite_256(['assets/characters/cameron/idle'], 'sprite')
nitrofs.add_nflib_sprite_256(['assets/characters/cameron/walk'], 'sprite')
nitrofs.add_nflib_sprite_256(['assets/characters/npcs/overworld'], 'sprite')

nitrofs.add_nflib_sprite_3d(['assets/text_display'], 'txt')
nitrofs.add_nflib_sprite_3d(['assets/characters/cameron/battle'], 'sprite')
nitrofs.add_nflib_sprite_3d(['assets/characters/npcs/battle'], 'sprite')

nitrofs.add_nflib_font(['assets/fonts'], 'fnt')
nitrofs.add_nflib_colbg(['assets/colbg'], 'colbg')

nitrofs.generate_image()
nitrofs_soundbank_header = nitrofs.add_mmutil(['nitrofs/audio'])


arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'nflib'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDSEXT}/nflib']
)

arm9.add_header_dependencies([nitrofs_soundbank_header])
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