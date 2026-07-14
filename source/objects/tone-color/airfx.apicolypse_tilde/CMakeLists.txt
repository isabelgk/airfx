set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.apicolypse_tilde) # output bundle: airfx.apicolypse~.mxo (_tilde->~)

target_sources(airfx.apicolypse_tilde
    PRIVATE
        airfx.apicolypse_tilde.cpp)

target_include_directories(airfx.apicolypse_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.apicolypse_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
