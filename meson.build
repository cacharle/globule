project(
  'mellow',
  'c',
  default_options : ['c_std=c99'],
  # c_args : ['Wall', 'Wextra']
)
b_coverage=true
add_global_arguments('-g', language : 'c')
if host_machine.system() == 'linux'
  add_global_arguments('--coverage', language : 'c')
endif
incdir = include_directories('include')
subdir('src')
lib = library('globule', sources, include_directories : incdir)
subdir('examples')
subdir('test')

