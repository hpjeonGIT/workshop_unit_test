#
set(copy_file
hello.txt)
add_test(NAME test01 COMMAND $<TARGET_FILE:a.exe> ./data/hello.txt ./data/hello.out)
add_test(NAME test02 COMMAND ${CMAKE_BINARY_DIR}/main/a.exe ./data/hello.out ./data/final.out )
add_test(NAME test03 COMMAND bash -c "cp ./data/final.out aaa.txt; \
                         $<TARGET_FILE:a.exe> ./aaa.txt ./bbb.txt"  )
# ref:https://stackoverflow.com/questions/3065220/ctest-with-multiple-commands
foreach (f ${copy_file})
  file(COPY ${f} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
endforeach()
