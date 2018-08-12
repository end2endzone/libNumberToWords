set(NUMBERTOWORDS_HEADER_FILES ""
  ${NUMBERTOWORDS_INCLUDE_DIR}/numbertowords/numbertowords.h
  ${NUMBERTOWORDS_INCLUDE_DIR}/numbertowords/ITextGenerator.h
  ${NUMBERTOWORDS_INCLUDE_DIR}/numbertowords/FrenchTextGenerator.h
)

add_library(numbertowords STATIC
  ${NUMBERTOWORDS_HEADER_FILES}
  ${NUMBERTOWORDS_EXPORT_HEADER}
  ${NUMBERTOWORDS_VERSION_HEADER}
  ${NUMBERTOWORDS_CONFIG_HEADER}
  ITextGenerator.cpp
  FrenchTextGenerator.cpp
)

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(numbertowords PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# Define include directories for exported code.
target_include_directories(numbertowords
  PUBLIC
    $<INSTALL_INTERFACE:${NUMBERTOWORDS_INSTALL_INCLUDE_DIR}>  # for clients using the installed library.
  PRIVATE
    
    ${GTEST_INCLUDE_DIR}
)
target_link_libraries(numbertowords PUBLIC rapidassist PRIVATE ${PTHREAD_LIBRARIES} ${GTEST_LIBRARIES} )

install(TARGETS numbertowords
        EXPORT numbertowords-targets
        ARCHIVE DESTINATION ${NUMBERTOWORDS_INSTALL_LIB_DIR}
        LIBRARY DESTINATION ${NUMBERTOWORDS_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${NUMBERTOWORDS_INSTALL_BIN_DIR}
)
