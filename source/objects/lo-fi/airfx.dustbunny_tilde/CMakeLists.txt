set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dustbunny_tilde) # output bundle: airfx.dustbunny~.mxo (_tilde->~)

target_sources(airfx.dustbunny_tilde
    PRIVATE
        airfx.dustbunny_tilde.cpp)

target_include_directories(airfx.dustbunny_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dustbunny_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
