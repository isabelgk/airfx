set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.slewonly_tilde) # output bundle: airfx.slewonly~.mxo (_tilde->~)

target_sources(airfx.slewonly_tilde
    PRIVATE
        airfx.slewonly_tilde.cpp)

target_include_directories(airfx.slewonly_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.slewonly_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
