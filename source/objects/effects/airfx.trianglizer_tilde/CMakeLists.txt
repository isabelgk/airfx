set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.trianglizer_tilde) # output bundle: airfx.trianglizer~.mxo (_tilde->~)

target_sources(airfx.trianglizer_tilde
    PRIVATE
        airfx.trianglizer_tilde.cpp)

target_include_directories(airfx.trianglizer_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.trianglizer_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
