# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ckoji/githome/new_static_site_generator/build/_deps/md4qt-src"
  "/home/ckoji/githome/new_static_site_generator/build/_deps/md4qt-build"
  "/mnt/c/Users/ckoji/git-workspace/new_static_site_generator/build/_deps/md4qt-subbuild/md4qt-populate-prefix"
  "/mnt/c/Users/ckoji/git-workspace/new_static_site_generator/build/_deps/md4qt-subbuild/md4qt-populate-prefix/tmp"
  "/mnt/c/Users/ckoji/git-workspace/new_static_site_generator/build/_deps/md4qt-subbuild/md4qt-populate-prefix/src/md4qt-populate-stamp"
  "/mnt/c/Users/ckoji/git-workspace/new_static_site_generator/build/_deps/md4qt-subbuild/md4qt-populate-prefix/src"
  "/mnt/c/Users/ckoji/git-workspace/new_static_site_generator/build/_deps/md4qt-subbuild/md4qt-populate-prefix/src/md4qt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/ckoji/git-workspace/new_static_site_generator/build/_deps/md4qt-subbuild/md4qt-populate-prefix/src/md4qt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/ckoji/git-workspace/new_static_site_generator/build/_deps/md4qt-subbuild/md4qt-populate-prefix/src/md4qt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
