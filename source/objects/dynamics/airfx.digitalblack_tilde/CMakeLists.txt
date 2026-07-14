set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.digitalblack_tilde) # output bundle: airfx.digitalblack~.mxo (_tilde->~)

target_sources(airfx.digitalblack_tilde
    PRIVATE
        airfx.digitalblack_tilde.cpp)

target_include_directories(airfx.digitalblack_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.digitalblack_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
