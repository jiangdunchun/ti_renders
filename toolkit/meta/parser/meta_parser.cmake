function(meta_pre_compile HEAD_FILES AUTO_GENERATED_FILE)
    set(META_PARSER ${META_PARSER_DIR}/meta_parser.py)
    message(STATUS "*****meta start to precompile*****->python python ${META_PARSER} -f ${HEAD_FILES} -g ${AUTO_GENERATED_FILE} -i ${WORD_DIR}")
    execute_process(COMMAND
        python ${META_PARSER} -f ${HEAD_FILES} -g ${AUTO_GENERATED_FILE} -i ${META_INCLUDE_DIR}
    )
    
endfunction()
