require 'rake'
require 'csv'

File.open("get_cDNA_with_AS.csv",'w') do |yes_out|
File.open("get_cDNA_with_AS.txt",'w') do |yes|
File.open("get_cDNA_with_no_AS.csv",'w') do |no_out|
File.open("get_cDNA_with_no_AS.txt",'w') do |no|
	seen = {}
	File.open("get_overlap_combine.txt").each do |line_yes_cDNA|
		cDNA = line_yes_cDNA.chomp.split("\t")
		if !seen[cDNA[4]]
			csv_yes_cDNA = line_yes_cDNA.gsub("\t",",")
			yes_out.puts csv_yes_cDNA
			if cDNA[1] == "+"
				yes.puts cDNA[0]+":"+cDNA[2]+"-"+cDNA[3]
			else
				yes.puts cDNA[0]+":"+cDNA[3]+"-"+cDNA[2]
			seen[cDNA[4]] = true
		end
	end
	File.open("get_cDNA_combine.txt").each do |line_cDNA|
		no_cDNA = line_cDNA.chomp.split("\t")
		if !seen[no_cDNA[4]]
			csv_no_cDNA = line_cDNA.gsub("\t",",")
			no_out.puts csv_no_cDNA
			if cDNA[1] == "+"
				no.puts cDNA[0]+":"+cDNA[2]+"-"+cDNA[3]
			else
				no.puts cDNA[0]+":"+cDNA[3]+"-"+cDNA[2]
		end
	end
end
end
end
end