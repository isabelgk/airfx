set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.midside_tilde) # output bundle: airfx.midside~.mxo (_tilde->~)

target_sources(airfx.midside_tilde
    PRIVATE
        airfx.midside_tilde.cpp)

target_include_directories(airfx.midside_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.midside_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
