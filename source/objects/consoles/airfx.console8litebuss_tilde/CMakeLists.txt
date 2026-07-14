set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console8litebuss_tilde) # output bundle: airfx.console8litebuss~.mxo (_tilde->~)

target_sources(airfx.console8litebuss_tilde
    PRIVATE
        airfx.console8litebuss_tilde.cpp)

target_include_directories(airfx.console8litebuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console8litebuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
