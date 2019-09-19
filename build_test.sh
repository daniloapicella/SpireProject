project_path=./Spire-c/
test_path=./Spire-c_test/
to_compile_files_list_path=$project_path"build_list";

for p in $(cat $to_compile_files_list_path)
  do
    file_path_to_append=$project_path$p;
    files_to_compile="$files_to_compile $file_path_to_append"
  done

to_compile_files_list_path=$test_path"build_test_list"

for p in $(cat $to_compile_files_list_path)
  do
    file_path_to_append=$test_path$p;
    files_to_compile="$files_to_compile $file_path_to_append"
  done

to_compile_files_list_path=$test_path"build_test_list"

executable_file_path="$path_destination"test
compile_script_path=$test_path"compile_test"
echo "gcc $files_to_compile -o $executable_file_path -Wall" > $compile_script_path;
compile_command=$test_path"compile_test"

$compile_command
