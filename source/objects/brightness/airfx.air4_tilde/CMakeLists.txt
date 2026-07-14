set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.air4_tilde) # output bundle: airfx.air4~.mxo (_tilde->~)

target_sources(airfx.air4_tilde
    PRIVATE
        airfx.air4_tilde.cpp)

target_include_directories(airfx.air4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.air4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
