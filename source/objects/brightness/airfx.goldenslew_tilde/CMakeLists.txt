set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.goldenslew_tilde) # output bundle: airfx.goldenslew~.mxo (_tilde->~)

target_sources(airfx.goldenslew_tilde
    PRIVATE
        airfx.goldenslew_tilde.cpp)

target_include_directories(airfx.goldenslew_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.goldenslew_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
