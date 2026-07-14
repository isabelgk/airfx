set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.blockparty_tilde) # output bundle: airfx.blockparty~.mxo (_tilde->~)

target_sources(airfx.blockparty_tilde
    PRIVATE
        airfx.blockparty_tilde.cpp)

target_include_directories(airfx.blockparty_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.blockparty_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
