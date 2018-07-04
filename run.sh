#!/bin/sh

export DYLD_LIBRARY_PATH=/Users/jwalsh/Documents/42/malloc/libmalloc
export DYLD_INSERT_LIBRARIES='/Users/jwalsh/Documents/42/malloc/libmalloc/libft_malloc.so'
# export DYLD_LIBRARY_PATH=.
# export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1

$@
