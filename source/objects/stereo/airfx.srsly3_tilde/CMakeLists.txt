set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.srsly3_tilde) # output bundle: airfx.srsly3~.mxo (_tilde->~)

target_sources(airfx.srsly3_tilde
    PRIVATE
        airfx.srsly3_tilde.cpp)

target_include_directories(airfx.srsly3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.srsly3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
