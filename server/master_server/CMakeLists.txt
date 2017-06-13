aux_source_directory(./ DIR_MASTER_SERVER)
aux_source_directory(./server_manager DIR_SERVER_MANAGER)

include_directories(${LIB_DIR})
include_directories(${THIRDPARTY_DIR})
include_directories(./)

link_directories(
    ${PROJECT_SOURCE_DIR}/bin
)

set (LINK_LIB
    libsrv.a
    libcomm.a
    libbase.a
    
    libevent.a
    libevent_core.a
    libevent_extra.a
    libprotobuf.a
    libprotobuf-lite.a
    libprotoc.a
)

add_executable(master_server 
    ${DIR_MASTER_SERVER}
    ${DIR_SERVER_MANAGER}
    )
target_link_libraries(master_server 
    ${LINK_LIB}
    )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/master_server")