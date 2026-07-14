set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.derez2_tilde) # output bundle: airfx.derez2~.mxo (_tilde->~)

target_sources(airfx.derez2_tilde
    PRIVATE
        airfx.derez2_tilde.cpp)

target_include_directories(airfx.derez2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.derez2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
