set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ultrasonx_tilde) # output bundle: airfx.ultrasonx~.mxo (_tilde->~)

target_sources(airfx.ultrasonx_tilde
    PRIVATE
        airfx.ultrasonx_tilde.cpp)

target_include_directories(airfx.ultrasonx_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ultrasonx_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
