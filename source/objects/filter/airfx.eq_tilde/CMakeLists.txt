set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.eq_tilde) # output bundle: airfx.eq~.mxo (_tilde->~)

target_sources(airfx.eq_tilde
    PRIVATE
        airfx.eq_tilde.cpp)

target_include_directories(airfx.eq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.eq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
