cmake_minimum_required(VERSION 3.5)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
# C:\cygwin64\home\Paul Belanger\opt\cross\bin\i686-elf-gcc.exe
#



set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_NAME Generic )
set(CMAKE_SYSTEM_PROCESSOR i686 )

set(CMAKE_CXX_COMPILER "/opt/cross/bin/i686-elf-g++.exe")
set(CMAKE_C_COMPILER "/opt/cross/bin/i686-elf-gcc.exe")
set(CMAKE_ASM_COMPILER "/opt/cross/bin/i686-elf-as.exe")

enable_language(ASM)
enable_language(CXX)
enable_language(C)

set(CMAKE_CXX_FLAGS "-ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti " CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS "-ffreestanding -Wall -Wextra" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "" CACHE INTERNAL "" FORCE)
set(CMAKE_ASM_FLAGS "" CACHE INTERNAL "" FORCE)
set(CMAKE_ASM_FLAGS_DEBUG "" CACHE INTERNAL "" FORCE)
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "" FORCE)

set(CRTBEGIN_OBJ "/opt/cross/bin/../lib/gcc/i686-elf/7.2.0/crtbegin.o")
set(CRTEND_OBJ "/opt/cross/bin/../lib/gcc/i686-elf/7.2.0/crtend.o")

set(CMAKE_EXE_LINKER_FLAGS "-T '${CMAKE_SOURCE_DIR}/linker.ld' -ffreestanding -nostdlib -lgcc" )
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \"${CRTBEGIN_OBJ}\" \"${CRTEND_OBJ}\"")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")


project(paulos C CXX ASM)

set(ISOFILE ${CMAKE_BINARY_DIR}/paulos.iso)


set_source_files_properties(${CRTBEGIN_OBJ} ${CRTEND_OBJ}
    PROPERTIES EXTERNAL_OBJECT true
    GENERATED true
)


set(SOURCES
    src/boot.s
    src/kernel.cpp src/kernel.hpp
    src/cpp_support.cpp src/VGA.cpp src/VGA.hpp src/array.hpp src/compile_checks.hpp src/stack.hpp src/hex.hpp src/hex.cpp src/stack.cpp)

# These should be in this exact order! Dont' change it.
add_executable(paulos
    src/crti.s
    ${CRTBEGIN_OBJ}
    ${SOURCES}
    ${CRTEND_OBJ}
    src/crtn.s
)

add_subdirectory(pstdlib)
target_link_libraries(paulos pstdlib)


set_target_properties(paulos PROPERTIES CXX_STANDARD 14)
set_target_properties(paulos PROPERTIES OUTPUT_NAME ${CMAKE_BINARY_DIR}/paulos.bin )

set(ISOFILE ${CMAKE_BINARY_DIR}/paulos.iso)

set(MKISOFS_COMMAND "/usr/bin/mkisofs")


add_custom_command(OUTPUT ${ISOFILE}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/grub_image" "${CMAKE_BINARY_DIR}/grub_image"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/paulos.bin" "${CMAKE_BINARY_DIR}/grub_image/paulos.bin"
    COMMAND ${MKISOFS_COMMAND} -quiet -R -b boot/grub/i386-pc/eltorito.img --no-emul-boot -boot-load-size 4
        --boot-info-table -o "${ISOFILE}" "${CMAKE_BINARY_DIR}/grub_image"
    COMMENT "Building ISO Image"
    DEPENDS paulos
)

add_custom_target(iso ALL
    DEPENDS ${ISOFILE}
)

get_target_property(paulos_ldflags paulos LINK_LIBRARIES)
message(STATUS "paulos link flags: " ${paulos_ldflags})
