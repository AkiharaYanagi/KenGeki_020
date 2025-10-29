file = ARGV[0]
base = file.sub(/_bhv\.lz4$/, '')

newname1 = "#{base}_1p_bhv.lz4"
newname2 = "#{base}_2p_bhv.lz4"

# 元ファイルをコピーして2つの新しいファイルを作成
require 'fileutils'
FileUtils.cp(file, newname1)
FileUtils.cp(file, newname2)

puts "Created: #{newname1}"
puts "Created: #{newname2}"
# gets  # コンソール保持（必要なら有効化）

