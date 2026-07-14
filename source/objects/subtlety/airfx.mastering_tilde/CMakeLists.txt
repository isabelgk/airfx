set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.mastering_tilde) # output bundle: airfx.mastering~.mxo (_tilde->~)

target_sources(airfx.mastering_tilde
    PRIVATE
        airfx.mastering_tilde.cpp)

target_include_directories(airfx.mastering_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.mastering_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
