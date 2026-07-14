set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cliponly3_tilde) # output bundle: airfx.cliponly3~.mxo (_tilde->~)

target_sources(airfx.cliponly3_tilde
    PRIVATE
        airfx.cliponly3_tilde.cpp)

target_include_directories(airfx.cliponly3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cliponly3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
