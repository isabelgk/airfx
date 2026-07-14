set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.srsly2_tilde) # output bundle: airfx.srsly2~.mxo (_tilde->~)

target_sources(airfx.srsly2_tilde
    PRIVATE
        airfx.srsly2_tilde.cpp)

target_include_directories(airfx.srsly2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.srsly2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
