aux_source_directory(./login_server DIR_LOGIN_SERVER)
aux_source_directory(./login_account DIR_LOGIN_ACCOUNT)

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

add_executable(login_server 
    main.cpp
    ${DIR_LOGIN_ACCOUNT}
    ${DIR_LOGIN_SERVER}
    )
target_link_libraries(login_server 
    ${LINK_LIB}
    )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/login_server")