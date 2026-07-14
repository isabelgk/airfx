set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.highpass2_tilde) # output bundle: airfx.highpass2~.mxo (_tilde->~)

target_sources(airfx.highpass2_tilde
    PRIVATE
        airfx.highpass2_tilde.cpp)

target_include_directories(airfx.highpass2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.highpass2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
