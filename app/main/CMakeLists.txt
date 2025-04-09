add_executable(main)

target_sources(main PRIVATE 
    "main.cpp"
)

target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/app/pca9685 
    ${CMAKE_SOURCE_DIR}/app/stm32_utility
)

target_link_libraries(main PRIVATE
    stm32cubemx
    stm32_utility
    pca9685
)

target_compile_options(main PUBLIC
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
