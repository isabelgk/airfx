set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.primefir_tilde) # output bundle: airfx.primefir~.mxo (_tilde->~)

target_sources(airfx.primefir_tilde
    PRIVATE
        airfx.primefir_tilde.cpp)

target_include_directories(airfx.primefir_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.primefir_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
