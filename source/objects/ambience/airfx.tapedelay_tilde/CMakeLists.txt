set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tapedelay_tilde) # output bundle: airfx.tapedelay~.mxo (_tilde->~)

target_sources(airfx.tapedelay_tilde
    PRIVATE
        airfx.tapedelay_tilde.cpp)

target_include_directories(airfx.tapedelay_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tapedelay_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
