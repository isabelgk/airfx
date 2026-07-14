set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.naturalizedither_tilde) # output bundle: airfx.naturalizedither~.mxo (_tilde->~)

target_sources(airfx.naturalizedither_tilde
    PRIVATE
        airfx.naturalizedither_tilde.cpp)

target_include_directories(airfx.naturalizedither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.naturalizedither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
