set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.chamber_tilde) # output bundle: airfx.chamber~.mxo (_tilde->~)

target_sources(airfx.chamber_tilde
    PRIVATE
        airfx.chamber_tilde.cpp)

target_include_directories(airfx.chamber_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.chamber_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
