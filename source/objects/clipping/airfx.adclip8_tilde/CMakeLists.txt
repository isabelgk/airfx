set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.adclip8_tilde) # output bundle: airfx.adclip8~.mxo (_tilde->~)

target_sources(airfx.adclip8_tilde
    PRIVATE
        airfx.adclip8_tilde.cpp)

target_include_directories(airfx.adclip8_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.adclip8_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
