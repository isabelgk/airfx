set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.parametric_tilde) # output bundle: airfx.parametric~.mxo (_tilde->~)

target_sources(airfx.parametric_tilde
    PRIVATE
        airfx.parametric_tilde.cpp)

target_include_directories(airfx.parametric_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.parametric_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
