#  把.路径下的所有源文件放入SRC_LIST中，避免文件过多，需要一个个列出来
aux_source_directory(. SRC_LIST)

#  将 SRC_LIST 中的文件编译为一个可执行程序 server 
add_executable(ChatClient ${SRC_LIST} )

# ChatClient 需要链接 pthread 库文件
target_link_libraries(ChatClient pthread)