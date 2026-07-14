set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.vinyldither_tilde) # output bundle: airfx.vinyldither~.mxo (_tilde->~)

target_sources(airfx.vinyldither_tilde
    PRIVATE
        airfx.vinyldither_tilde.cpp)

target_include_directories(airfx.vinyldither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.vinyldither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
