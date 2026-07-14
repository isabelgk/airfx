set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.balanced_tilde) # output bundle: airfx.balanced~.mxo (_tilde->~)

target_sources(airfx.balanced_tilde
    PRIVATE
        airfx.balanced_tilde.cpp)

target_include_directories(airfx.balanced_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.balanced_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
