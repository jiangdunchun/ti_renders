function(meta_pre_compile HEAD_FILES AUTO_GENERATED_H_FILE AUTO_GENERATED_CPP_FILE)
    set(META_PARSER ${META_PARSER_DIR}/meta_parser.py)
    message(STATUS "****meta start to precompile**** python ${META_PARSER} -f ${HEAD_FILES} -gh ${AUTO_GENERATED_H_FILE} -gc ${AUTO_GENERATED_CPP_FILE} -i ${META_INCLUDE_DIR}")
    execute_process(COMMAND
        python ${META_PARSER} -f ${HEAD_FILES} -gh ${AUTO_GENERATED_H_FILE} -gc ${AUTO_GENERATED_CPP_FILE} -i ${META_INCLUDE_DIR}
    )
    
endfunction()
