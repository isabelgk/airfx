set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.channel9_tilde) # output bundle: airfx.channel9~.mxo (_tilde->~)

target_sources(airfx.channel9_tilde
    PRIVATE
        airfx.channel9_tilde.cpp)

target_include_directories(airfx.channel9_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.channel9_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
