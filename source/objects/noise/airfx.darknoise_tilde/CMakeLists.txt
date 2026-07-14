set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.darknoise_tilde) # output bundle: airfx.darknoise~.mxo (_tilde->~)

target_sources(airfx.darknoise_tilde
    PRIVATE
        airfx.darknoise_tilde.cpp)

target_include_directories(airfx.darknoise_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.darknoise_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
