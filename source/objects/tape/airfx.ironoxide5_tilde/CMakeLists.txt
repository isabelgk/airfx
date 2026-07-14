set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ironoxide5_tilde) # output bundle: airfx.ironoxide5~.mxo (_tilde->~)

target_sources(airfx.ironoxide5_tilde
    PRIVATE
        airfx.ironoxide5_tilde.cpp)

target_include_directories(airfx.ironoxide5_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ironoxide5_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
