set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.air2_tilde) # output bundle: airfx.air2~.mxo (_tilde->~)

target_sources(airfx.air2_tilde
    PRIVATE
        airfx.air2_tilde.cpp)

target_include_directories(airfx.air2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.air2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
