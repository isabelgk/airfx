set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolemcbuss_tilde) # output bundle: airfx.consolemcbuss~.mxo (_tilde->~)

target_sources(airfx.consolemcbuss_tilde
    PRIVATE
        airfx.consolemcbuss_tilde.cpp)

target_include_directories(airfx.consolemcbuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolemcbuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
