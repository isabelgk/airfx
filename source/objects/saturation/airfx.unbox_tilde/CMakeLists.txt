set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.unbox_tilde) # output bundle: airfx.unbox~.mxo (_tilde->~)

target_sources(airfx.unbox_tilde
    PRIVATE
        airfx.unbox_tilde.cpp)

target_include_directories(airfx.unbox_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.unbox_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
