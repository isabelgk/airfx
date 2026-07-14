set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bezeq2_tilde) # output bundle: airfx.bezeq2~.mxo (_tilde->~)

target_sources(airfx.bezeq2_tilde
    PRIVATE
        airfx.bezeq2_tilde.cpp)

target_include_directories(airfx.bezeq2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bezeq2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
