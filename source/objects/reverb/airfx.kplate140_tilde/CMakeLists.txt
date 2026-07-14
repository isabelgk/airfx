set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kplate140_tilde) # output bundle: airfx.kplate140~.mxo (_tilde->~)

target_sources(airfx.kplate140_tilde
    PRIVATE
        airfx.kplate140_tilde.cpp)

target_include_directories(airfx.kplate140_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kplate140_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
