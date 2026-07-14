set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.srsly_tilde) # output bundle: airfx.srsly~.mxo (_tilde->~)

target_sources(airfx.srsly_tilde
    PRIVATE
        airfx.srsly_tilde.cpp)

target_include_directories(airfx.srsly_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.srsly_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
