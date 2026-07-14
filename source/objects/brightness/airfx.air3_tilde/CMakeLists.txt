set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.air3_tilde) # output bundle: airfx.air3~.mxo (_tilde->~)

target_sources(airfx.air3_tilde
    PRIVATE
        airfx.air3_tilde.cpp)

target_include_directories(airfx.air3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.air3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
