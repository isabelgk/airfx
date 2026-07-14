set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cliponly_tilde) # output bundle: airfx.cliponly~.mxo (_tilde->~)

target_sources(airfx.cliponly_tilde
    PRIVATE
        airfx.cliponly_tilde.cpp)

target_include_directories(airfx.cliponly_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cliponly_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
