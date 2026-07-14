set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.lrconvolve3_tilde) # output bundle: airfx.lrconvolve3~.mxo (_tilde->~)

target_sources(airfx.lrconvolve3_tilde
    PRIVATE
        airfx.lrconvolve3_tilde.cpp)

target_include_directories(airfx.lrconvolve3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.lrconvolve3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
