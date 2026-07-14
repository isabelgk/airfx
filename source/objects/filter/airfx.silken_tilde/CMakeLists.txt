set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.silken_tilde) # output bundle: airfx.silken~.mxo (_tilde->~)

target_sources(airfx.silken_tilde
    PRIVATE
        airfx.silken_tilde.cpp)

target_include_directories(airfx.silken_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.silken_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
