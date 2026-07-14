set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolemdbuss_tilde) # output bundle: airfx.consolemdbuss~.mxo (_tilde->~)

target_sources(airfx.consolemdbuss_tilde
    PRIVATE
        airfx.consolemdbuss_tilde.cpp)

target_include_directories(airfx.consolemdbuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolemdbuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
