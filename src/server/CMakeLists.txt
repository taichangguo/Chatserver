#  把.路径下的所有源文件放入SRC_LIST中，避免文件过多，需要一个个列出来
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

#  将 SRC_LIST 中的文件编译为一个可执行程序 server 
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

# ChatServer 需要链接 muduo_net muduo_base pthread mysqlclient库文件
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread)