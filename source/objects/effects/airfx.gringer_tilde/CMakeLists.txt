set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.gringer_tilde) # output bundle: airfx.gringer~.mxo (_tilde->~)

target_sources(airfx.gringer_tilde
    PRIVATE
        airfx.gringer_tilde.cpp)

target_include_directories(airfx.gringer_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.gringer_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
