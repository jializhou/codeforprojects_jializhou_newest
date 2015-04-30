require 'rake'

filelist = FileList["*.txt"].reject{|f| f =~ /get/}

filelist.each do |f|
	File.open("get_"+f,'w') do |fout|
		lines = File.readlines(f)
		seen ={}
		lines.each do |line|
			if !seen[line]
				fout.puts line
				seen[line] = true
			end
		end
	end
end