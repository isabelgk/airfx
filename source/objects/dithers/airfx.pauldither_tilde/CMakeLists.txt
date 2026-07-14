set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pauldither_tilde) # output bundle: airfx.pauldither~.mxo (_tilde->~)

target_sources(airfx.pauldither_tilde
    PRIVATE
        airfx.pauldither_tilde.cpp)

target_include_directories(airfx.pauldither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pauldither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
