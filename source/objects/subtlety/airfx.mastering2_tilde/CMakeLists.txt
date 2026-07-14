set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.mastering2_tilde) # output bundle: airfx.mastering2~.mxo (_tilde->~)

target_sources(airfx.mastering2_tilde
    PRIVATE
        airfx.mastering2_tilde.cpp)

target_include_directories(airfx.mastering2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.mastering2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
