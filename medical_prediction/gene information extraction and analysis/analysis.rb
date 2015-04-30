require 'rake'
filelist = FileList["*.txt"].reject { |f| f =~ /^analysis/ }

File.open("analysis_result.txt",'w') do |out|
filelist.each do |f|
	File.open("analysis_"+f, 'w') do |fout|
		calculation = Array.new
		i = 0
		max_xulie = 0
		min_xulie = 1000000
		min_xuhao = 0
		min_line = Array.new(3) { |i|  }
		File.open(f).each do |line|
			a= line.chomp.split("\t")
			next unless line.length>0
			calculation[i]=a[3].to_i-a[2].to_i
			if max_xulie < calculation[i]
				max_xulie = calculation[i]
			end
			if min_xulie > calculation[i]
				min_xulie = calculation[i]
				min_line = a
				min_xuhao = i
			end
			fout.puts calculation[i] 
			i+=1
		end
		# f.close
		 cal_sum = calculation.inject{|sum,item| sum+item}
		 out.puts   "filename=" + File.basename(f)
		 average=cal_sum/calculation.length 
		 out.puts "average=" + average.to_s
		 out.puts "number of xulie=" + calculation.length.to_s
		 out.puts "min=" + min_xulie.to_s
		 out.puts "min_xuhao=" + min_xuhao.to_s
		 out.puts min_line
		 out.puts "max=" + max_xulie.to_s
		 sum=0
		 calculation.each do |item|
		   sum +=(average-item)*(average-item)		  
		end	
		deviation = Math.sqrt(sum/calculation.length)
		out.puts "deviation=" + deviation.to_s
	end
end
end
