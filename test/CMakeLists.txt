add_executable(numbertowords_unittest
  ${RAPIDASSIST_EXPORT_HEADER}
  ${RAPIDASSIST_VERSION_HEADER}
  ${RAPIDASSIST_CONFIG_HEADER}
  main.cpp
  TestFrench.h
  TestFrench.cpp
  TestEnglish.h
  TestEnglish.cpp
)

# Unit test projects requires to link with pthread if also linking with gtest
if(NOT WIN32)
  set(PTHREAD_LIBRARIES -pthread)
endif()

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(numbertowords_unittest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_include_directories(numbertowords_unittest PRIVATE rapidassist)
target_include_directories(numbertowords_unittest PRIVATE ${GTEST_INCLUDE_DIR})
add_dependencies(numbertowords_unittest numbertowords)
target_link_libraries(numbertowords_unittest PUBLIC rapidassist numbertowords ${PTHREAD_LIBRARIES} ${GTEST_LIBRARIES} )

# Copy test files database to target dir
add_custom_command( TARGET numbertowords_unittest POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/french $<TARGET_FILE_DIR:numbertowords_unittest>/db
                    COMMENT "Copying french database.")

install(TARGETS numbertowords_unittest
        EXPORT numbertowords-targets
        ARCHIVE DESTINATION ${NUMBERTOWORDS_INSTALL_LIB_DIR}
        LIBRARY DESTINATION ${NUMBERTOWORDS_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${NUMBERTOWORDS_INSTALL_BIN_DIR}
)
