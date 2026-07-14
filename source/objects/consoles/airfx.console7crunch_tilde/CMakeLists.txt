set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console7crunch_tilde) # output bundle: airfx.console7crunch~.mxo (_tilde->~)

target_sources(airfx.console7crunch_tilde
    PRIVATE
        airfx.console7crunch_tilde.cpp)

target_include_directories(airfx.console7crunch_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console7crunch_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
