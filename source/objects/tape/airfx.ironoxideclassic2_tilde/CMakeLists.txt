set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ironoxideclassic2_tilde) # output bundle: airfx.ironoxideclassic2~.mxo (_tilde->~)

target_sources(airfx.ironoxideclassic2_tilde
    PRIVATE
        airfx.ironoxideclassic2_tilde.cpp)

target_include_directories(airfx.ironoxideclassic2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ironoxideclassic2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
