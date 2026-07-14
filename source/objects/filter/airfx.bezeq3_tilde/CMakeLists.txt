set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bezeq3_tilde) # output bundle: airfx.bezeq3~.mxo (_tilde->~)

target_sources(airfx.bezeq3_tilde
    PRIVATE
        airfx.bezeq3_tilde.cpp)

target_include_directories(airfx.bezeq3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bezeq3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
