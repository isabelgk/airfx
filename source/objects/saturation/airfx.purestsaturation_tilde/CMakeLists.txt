set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestsaturation_tilde) # output bundle: airfx.purestsaturation~.mxo (_tilde->~)

target_sources(airfx.purestsaturation_tilde
    PRIVATE
        airfx.purestsaturation_tilde.cpp)

target_include_directories(airfx.purestsaturation_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestsaturation_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
