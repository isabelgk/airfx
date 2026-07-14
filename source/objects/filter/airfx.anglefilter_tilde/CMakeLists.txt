set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.anglefilter_tilde) # output bundle: airfx.anglefilter~.mxo (_tilde->~)

target_sources(airfx.anglefilter_tilde
    PRIVATE
        airfx.anglefilter_tilde.cpp)

target_include_directories(airfx.anglefilter_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.anglefilter_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
