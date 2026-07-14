set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.thunder_tilde) # output bundle: airfx.thunder~.mxo (_tilde->~)

target_sources(airfx.thunder_tilde
    PRIVATE
        airfx.thunder_tilde.cpp)

target_include_directories(airfx.thunder_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.thunder_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
