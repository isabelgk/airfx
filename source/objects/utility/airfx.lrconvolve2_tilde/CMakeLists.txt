set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.lrconvolve2_tilde) # output bundle: airfx.lrconvolve2~.mxo (_tilde->~)

target_sources(airfx.lrconvolve2_tilde
    PRIVATE
        airfx.lrconvolve2_tilde.cpp)

target_include_directories(airfx.lrconvolve2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.lrconvolve2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
