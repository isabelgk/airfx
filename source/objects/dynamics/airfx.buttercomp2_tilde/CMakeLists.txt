set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.buttercomp2_tilde) # output bundle: airfx.buttercomp2~.mxo (_tilde->~)

target_sources(airfx.buttercomp2_tilde
    PRIVATE
        airfx.buttercomp2_tilde.cpp)

target_include_directories(airfx.buttercomp2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.buttercomp2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
