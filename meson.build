project('unity_single_instance_fix', 'c')
compiler = meson.get_compiler('c')
dl_dep = compiler.find_library('dl')
shared_library('unity-single-instance-fix', 'unity-single-instance-fix.c', dependencies: [dl_dep], install: true)
