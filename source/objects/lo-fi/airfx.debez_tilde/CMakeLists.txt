set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.debez_tilde) # output bundle: airfx.debez~.mxo (_tilde->~)

target_sources(airfx.debez_tilde
    PRIVATE
        airfx.debez_tilde.cpp)

target_include_directories(airfx.debez_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.debez_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
