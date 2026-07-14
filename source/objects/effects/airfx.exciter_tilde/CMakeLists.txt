set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.exciter_tilde) # output bundle: airfx.exciter~.mxo (_tilde->~)

target_sources(airfx.exciter_tilde
    PRIVATE
        airfx.exciter_tilde.cpp)

target_include_directories(airfx.exciter_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.exciter_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
