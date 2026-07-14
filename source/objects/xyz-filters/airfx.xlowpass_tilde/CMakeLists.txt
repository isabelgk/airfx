set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.xlowpass_tilde) # output bundle: airfx.xlowpass~.mxo (_tilde->~)

target_sources(airfx.xlowpass_tilde
    PRIVATE
        airfx.xlowpass_tilde.cpp)

target_include_directories(airfx.xlowpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.xlowpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
