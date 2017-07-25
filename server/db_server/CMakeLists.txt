aux_source_directory(./db_server DIR_DB_SERVER)

include_directories(${LIB_DIR})
include_directories(${THIRDPARTY_DIR})

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

add_executable(db_server 
    main.cpp
    ${DIR_DB_SERVER}
    )
target_link_libraries(db_server 
    ${LINK_LIB}
    )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/db_server")