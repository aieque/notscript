@echo off

set code_dir=%cd%/code/
set compiler_flags=-nologo -FC -Gm- -GR- -EHa- -nologo -Zi -MT -wd4477 -Od
set link_flags=-opt:ref -incremental:no

pushd build
cl %compiler_flags% %code_dir%/notscript.cpp -DNS_PLATFORM_WINDOWS -link %link_flags%
popd