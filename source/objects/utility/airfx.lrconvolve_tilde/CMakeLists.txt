set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.lrconvolve_tilde) # output bundle: airfx.lrconvolve~.mxo (_tilde->~)

target_sources(airfx.lrconvolve_tilde
    PRIVATE
        airfx.lrconvolve_tilde.cpp)

target_include_directories(airfx.lrconvolve_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.lrconvolve_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
