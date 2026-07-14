set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestsquish_tilde) # output bundle: airfx.purestsquish~.mxo (_tilde->~)

target_sources(airfx.purestsquish_tilde
    PRIVATE
        airfx.purestsquish_tilde.cpp)

target_include_directories(airfx.purestsquish_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestsquish_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
