cmake_minimum_required(VERSION 3.10)
project(cherrie)

set(CMAKE_CXX_STANDARD 17)

# Pridaj hlavičky
include_directories(include)

# Načítaj všetky .cpp zo src/
file(GLOB SOURCES "src/*.cpp")

# Vytvor shared knižnicu s názvom cherrie
add_library(cherrie SHARED ${SOURCES})

# Pridaj linkovanie s GDI32 (pre StretchDIBits a iné Win32 grafické funkcie)
target_link_libraries(cherrie PRIVATE gdi32)

# Nastav meno výsledného súboru
set_target_properties(cherrie PROPERTIES OUTPUT_NAME "cherrie")

# Nastav inštaláciu do systémových priečinkov
install(TARGETS cherrie DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
