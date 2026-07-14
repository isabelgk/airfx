set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.spiral_tilde) # output bundle: airfx.spiral~.mxo (_tilde->~)

target_sources(airfx.spiral_tilde
    PRIVATE
        airfx.spiral_tilde.cpp)

target_include_directories(airfx.spiral_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.spiral_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
