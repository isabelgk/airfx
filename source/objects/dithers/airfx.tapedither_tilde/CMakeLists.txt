set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tapedither_tilde) # output bundle: airfx.tapedither~.mxo (_tilde->~)

target_sources(airfx.tapedither_tilde
    PRIVATE
        airfx.tapedither_tilde.cpp)

target_include_directories(airfx.tapedither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tapedither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
