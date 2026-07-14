set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.verbtiny_tilde) # output bundle: airfx.verbtiny~.mxo (_tilde->~)

target_sources(airfx.verbtiny_tilde
    PRIVATE
        airfx.verbtiny_tilde.cpp)

target_include_directories(airfx.verbtiny_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.verbtiny_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
