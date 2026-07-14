set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.everyconsole_tilde) # output bundle: airfx.everyconsole~.mxo (_tilde->~)

target_sources(airfx.everyconsole_tilde
    PRIVATE
        airfx.everyconsole_tilde.cpp)

target_include_directories(airfx.everyconsole_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.everyconsole_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
