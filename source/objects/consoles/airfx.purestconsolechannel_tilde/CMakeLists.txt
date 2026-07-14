set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestconsolechannel_tilde) # output bundle: airfx.purestconsolechannel~.mxo (_tilde->~)

target_sources(airfx.purestconsolechannel_tilde
    PRIVATE
        airfx.purestconsolechannel_tilde.cpp)

target_include_directories(airfx.purestconsolechannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestconsolechannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
