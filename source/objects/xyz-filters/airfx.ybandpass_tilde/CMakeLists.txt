set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ybandpass_tilde) # output bundle: airfx.ybandpass~.mxo (_tilde->~)

target_sources(airfx.ybandpass_tilde
    PRIVATE
        airfx.ybandpass_tilde.cpp)

target_include_directories(airfx.ybandpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ybandpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
