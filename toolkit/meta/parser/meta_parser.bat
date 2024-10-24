set parser=%~dp0meta_parser.py
set head_files=%1
set generated_head_file=%2
set generated_source_file=%3
set include_path=%4

echo "start pre build"
call python %parser% -f %head_files% -gh %generated_head_file% -gc %generated_source_file% -i %include_path%
