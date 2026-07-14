set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kplatec_tilde) # output bundle: airfx.kplatec~.mxo (_tilde->~)

target_sources(airfx.kplatec_tilde
    PRIVATE
        airfx.kplatec_tilde.cpp)

target_include_directories(airfx.kplatec_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kplatec_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
