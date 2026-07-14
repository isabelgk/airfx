set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.density3_tilde) # output bundle: airfx.density3~.mxo (_tilde->~)

target_sources(airfx.density3_tilde
    PRIVATE
        airfx.density3_tilde.cpp)

target_include_directories(airfx.density3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.density3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
