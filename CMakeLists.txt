cmake_minimum_required(VERSION 3.16)
project(LinuxCProgrammingHelper C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(ADWAITA REQUIRED libadwaita-1)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(RESOURCE_XML "${CMAKE_SOURCE_DIR}/src/resources.xml")
set(RESOURCE_C "${CMAKE_BINARY_DIR}/resources.c")

# НОВОЕ: Создаем список всех файлов, от которых зависит ресурс
set(RESOURCE_FILES
    "${CMAKE_SOURCE_DIR}/resources/main.css"
    "${CMAKE_SOURCE_DIR}/resources/c_lang_base_image.png"
    "${CMAKE_SOURCE_DIR}/resources/c_lang_gtk4_image.png"
)

add_custom_command(
    OUTPUT ${RESOURCE_C}
    COMMAND glib-compile-resources ${RESOURCE_XML} --target=${RESOURCE_C} --generate-source --c-name resources
    # ИЗМЕНЕНО: Добавляем все файлы в зависимости
    DEPENDS ${RESOURCE_XML} ${RESOURCE_FILES}
    COMMENT "Generating ${RESOURCE_C} from ${RESOURCE_XML}"
)

add_executable(${PROJECT_NAME} 
    src/main.c
    src/chapters.c
    src/c_base.c
    ${RESOURCE_C}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${GTK4_INCLUDE_DIRS}
    ${ADWAITA_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GTK4_LIBRARIES}
    ${ADWAITA_LIBRARIES}
)