aux_source_directory(. CLIENT_DIR)

include_directories(${LIB_DIR})
include_directories(${THIRDPARTY_DIR})

link_directories(
    ${PROJECT_SOURCE_DIR}/bin
)

set (LINK_LIB
    libcomm.a
    libbase.a
    
    libevent.a
    libevent_core.a
    libevent_extra.a
    libprotobuf.a
    libprotobuf-lite.a
    libprotoc.a
)

add_executable(client 
    ${CLIENT_DIR}
    )
target_link_libraries(client 
    ${LINK_LIB}
    )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/client")