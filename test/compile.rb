#!/usr/local/bin/ruby
CXX="c++-7"
CXXFLAGS="-std=c++17"

test_files = Dir["*.test.cpp"]
parent_file_pairs = test_files.map do |file|
  [file, '../' + file[0,file.index('.test')] + '.cpp']
end

parent_file_pairs.each do |pair|
  system CXX, CXXFLAGS, '-o', pair[0][0,pair[0].index('.test')], pair[0], pair[1]
end
