set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dehiss_tilde) # output bundle: airfx.dehiss~.mxo (_tilde->~)

target_sources(airfx.dehiss_tilde
    PRIVATE
        airfx.dehiss_tilde.cpp)

target_include_directories(airfx.dehiss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dehiss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
