set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bitglitter_tilde) # output bundle: airfx.bitglitter~.mxo (_tilde->~)

target_sources(airfx.bitglitter_tilde
    PRIVATE
        airfx.bitglitter_tilde.cpp)

target_include_directories(airfx.bitglitter_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bitglitter_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
