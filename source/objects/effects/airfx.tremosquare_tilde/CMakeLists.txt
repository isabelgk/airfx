set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tremosquare_tilde) # output bundle: airfx.tremosquare~.mxo (_tilde->~)

target_sources(airfx.tremosquare_tilde
    PRIVATE
        airfx.tremosquare_tilde.cpp)

target_include_directories(airfx.tremosquare_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tremosquare_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
