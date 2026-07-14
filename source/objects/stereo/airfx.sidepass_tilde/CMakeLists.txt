set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.sidepass_tilde) # output bundle: airfx.sidepass~.mxo (_tilde->~)

target_sources(airfx.sidepass_tilde
    PRIVATE
        airfx.sidepass_tilde.cpp)

target_include_directories(airfx.sidepass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.sidepass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
