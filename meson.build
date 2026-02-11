project(
  'tempo-estimator',
  'c',
  version: '1.0.0',
  default_options: [
    'c_std=c99',
    'warning_level=2',
    'buildtype=release'])

# source
inc = include_directories('source')
src = files(
  'source/wav.c',
  'source/main.c')

executable(
  'tempo-estimator',
  src,
  include_directories: inc)