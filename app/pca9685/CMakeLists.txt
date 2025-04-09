add_library(pca9685 STATIC)

target_sources(pca9685 PRIVATE 
    "pca9685.cpp"
)

target_include_directories(pca9685 PUBLIC 
    ${CMAKE_SOURCE_DIR}/app/stm32_utility
)

target_link_libraries(pca9685 PUBLIC
    stm32_utility
)

target_compile_options(pca9685 PUBLIC
    -std=c++23
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
    -Wpedantic
    -Wnarrowing
    -Waddress
    -pedantic
    -Wdeprecated
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wcast-align
    -fconcepts
)
