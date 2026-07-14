set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cans_tilde) # output bundle: airfx.cans~.mxo (_tilde->~)

target_sources(airfx.cans_tilde
    PRIVATE
        airfx.cans_tilde.cpp)

target_include_directories(airfx.cans_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cans_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
