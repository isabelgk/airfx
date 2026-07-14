set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.lilamp_tilde) # output bundle: airfx.lilamp~.mxo (_tilde->~)

target_sources(airfx.lilamp_tilde
    PRIVATE
        airfx.lilamp_tilde.cpp)

target_include_directories(airfx.lilamp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.lilamp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
