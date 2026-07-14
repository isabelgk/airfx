set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bezeq_tilde) # output bundle: airfx.bezeq~.mxo (_tilde->~)

target_sources(airfx.bezeq_tilde
    PRIVATE
        airfx.bezeq_tilde.cpp)

target_include_directories(airfx.bezeq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bezeq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
