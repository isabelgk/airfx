set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.woodenbox_tilde) # output bundle: airfx.woodenbox~.mxo (_tilde->~)

target_sources(airfx.woodenbox_tilde
    PRIVATE
        airfx.woodenbox_tilde.cpp)

target_include_directories(airfx.woodenbox_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.woodenbox_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
