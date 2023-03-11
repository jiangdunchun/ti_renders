function(compile_shader SHADER_SRC_FILES GENERATED_DIR)
    foreach(SHADER_SRC_FILE ${SHADER_SRC_FILES})
        message(STATUS "*****compile_shader*****->${SHADER_SRC_FILE}")

        get_filename_component(SHADER_NAME ${SHADER_SRC_FILE} NAME)

        string(REPLACE "." "_" SHADER_NAME ${SHADER_NAME})
        set(SHADER_BIN_FILE ${GENERATED_DIR}/${SHADER_NAME})

        execute_process(COMMAND 
	        glslangValidator
		        -V ${SHADER_SRC_FILE}
		        -o ${SHADER_BIN_FILE})

	
	    file(READ ${SHADER_BIN_FILE} HEX_CONTENT HEX)
        string(REPEAT "[0-9a-f]" 32 PATTERN)
        string(REGEX REPLACE "(${PATTERN})" "\\1\n" CONTENT "${HEX_CONTENT}")
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " CONTENT "${CONTENT}")
        string(REGEX REPLACE ", $" "" CONTENT "${CONTENT}")
        set(CODE_ARRAY "static const std::vector<unsigned char> ${SHADER_NAME} = {\n${CONTENT}\n}\;")
        set(FILE_CONTENT "/**\n * @file ${SHADER_NAME}.h\n * @brief Auto generated file.\n */\n#include <vector>\n${CODE_ARRAY}\n")
        file(WRITE ${GENERATED_DIR}/${SHADER_NAME}.h ${FILE_CONTENT})

        file(REMOVE ${SHADER_BIN_FILE})
        message(STATUS "********************")
    endforeach()
endfunction()