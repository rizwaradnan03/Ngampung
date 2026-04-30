cmake_minimum_required(VERSION 3.10)
project(Ngampung)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Ngampung ${SOURCES})

# raylib
find_package(raylib REQUIRED)
target_link_libraries(Ngampung raylib)

# =========================
# COPY ASSETS (build time)
# =========================
add_custom_command(TARGET Ngampung POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Ngampung>/assets
)

# =========================
# INSTALL (UNTUK INSTALLER)
# =========================

# exe
install(TARGETS Ngampung DESTINATION .)

# assets
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION .)

# 🔥 IMPORTANT: DLL RAYLIB + GCC
set(MINGW_BIN "C:/msys64/mingw64/bin")

install(FILES
    "${MINGW_BIN}/libraylib.dll"
    "${MINGW_BIN}/glfw3.dll"
    "${MINGW_BIN}/libgcc_s_seh-1.dll"
    "${MINGW_BIN}/libstdc++-6.dll"
    "${MINGW_BIN}/libwinpthread-1.dll"
    DESTINATION .
)

# =========================
# CPACK CONFIG
# =========================
set(CPACK_PACKAGE_NAME "Ngampung")
set(CPACK_PACKAGE_VENDOR "Rizwar")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Game Ngampung")

# nama file installer
set(CPACK_PACKAGE_FILE_NAME "Ngampung-Installer")

# NSIS
set(CPACK_GENERATOR "NSIS")

# optional (biar lebih keren)
set(CPACK_NSIS_DISPLAY_NAME "Ngampung Game")
set(CPACK_NSIS_CONTACT "rizwar@email.com")
set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)