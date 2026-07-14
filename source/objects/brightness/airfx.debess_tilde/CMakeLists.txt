set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.debess_tilde) # output bundle: airfx.debess~.mxo (_tilde->~)

target_sources(airfx.debess_tilde
    PRIVATE
        airfx.debess_tilde.cpp)

target_include_directories(airfx.debess_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.debess_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
