cmake_minimum_required(VERSION 2.8.5)
project(amimage LANGUAGES C)

# ACE
add_subdirectory(ACE ace)

add_executable(
	amimage.elf main.c game.c 
	
) # Compiler emits .elf file, we need hunk for Amiga

target_compile_options(amimage.elf PRIVATE -Wall -Wextra)

target_link_libraries(amimage.elf ace)
target_compile_definitions(ace PUBLIC ACE_DEBUG ACE_DEBUG_UAE)

add_custom_command( # So call elf2hunk
	TARGET amimage.elf POST_BUILD
	COMMAND ${ELF2HUNK} amimage.elf amimage.exe
)

set(RES_DIR ${CMAKE_CURRENT_LIST_DIR}/res) # st�d bierzemy pliki do konwersji
set(DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data) # tu maj� l�dowa�
file(MAKE_DIRECTORY ${DATA_DIR}) #za���my data





set(PLT_PATH ${DATA_DIR}/amimage.plt) #tak si� b�dzie nazywa� docelowa paleta
convertPalette(amimage.elf ${RES_DIR}/amimage.pal ${PLT_PATH}) # z res/amimage.pal do build/data/amimage.plt

convertBitmaps(
	TARGET amimage.elf PALETTE ${PLT_PATH}
	INTERLEAVED SOURCES
		${RES_DIR}/arco32.png 
	DESTINATIONS
		${DATA_DIR}/arco32.bm 
)



file(
	COPY ${RES_DIR}/placeholdermod.mod ${RES_DIR}/topaz.fnt
	DESTINATION ${DATA_DIR}
)
