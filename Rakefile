task :build, 'filepath', "plus_arg"
task :build do |t, args|
  sh "gcc #{args['filepath']}.c lib/get_num.c lib/error_functions.c #{args['plus_arg']}"
end
