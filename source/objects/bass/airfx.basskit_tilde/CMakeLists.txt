set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.basskit_tilde) # output bundle: airfx.basskit~.mxo (_tilde->~)

target_sources(airfx.basskit_tilde
    PRIVATE
        airfx.basskit_tilde.cpp)

target_include_directories(airfx.basskit_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.basskit_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
