require 'rake'

File.open("overlap_antisense_pos.txt", 'w') do |fout|
File.open("get_antisense_pos.txt").each do |line_pos|
	b = line_pos.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_neg.txt").each do |line_neg|
		a = line_neg.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "-" + "\t" + a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_antisense_neg.txt", 'w') do |fout|
File.open("get_antisense_neg.txt").each do |line_neg|
	b = line_neg.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_pos.txt").each do |line_pos|
		a = line_pos.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i	
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "+" + "\t" + a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_lincRNA_pos.txt", 'w') do |fout|
File.open("get_lincRNA_pos.txt").each do |line_pos|
	b = line_pos.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_neg.txt").each do |line_neg|
		a = line_neg.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "-" + "\t"+ a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_lincRNA_neg.txt", 'w') do |fout|
File.open("get_lincRNA_neg.txt").each do |line_neg|
	b = line_neg.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_pos.txt").each do |line_pos|
		a = line_pos.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i	
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "+" + "\t" + a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end


File.open("overlap_lnRNA_pos.txt", 'w') do |fout|
File.open("get_lnRNA_pos.txt").each do |line_pos|
	b = line_pos.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_neg.txt").each do |line_neg|
		a = line_neg.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "-" + "\t"+ a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_lnRNA_neg.txt", 'w') do |fout|
File.open("get_lnRNA_neg.txt").each do |line_neg|
	b = line_neg.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_pos.txt").each do |line_pos|
		a = line_pos.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i	
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "+" + "\t" + a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_sense_intronic_pos.txt", 'w') do |fout|
File.open("get_sense_intronic_pos.txt").each do |line_pos|
	b = line_pos.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_neg.txt").each do |line_neg|
		a = line_neg.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "-" + "\t"+ a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_sense_intronic_neg.txt", 'w') do |fout|
File.open("get_sense_intronic_neg.txt").each do |line_neg|
	b = line_neg.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_pos.txt").each do |line_pos|
		a = line_pos.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i	
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "+" + "\t" + a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_overlapping_pos.txt", 'w') do |fout|
File.open("get_sense_overlapping_pos.txt").each do |line_pos|
	b = line_pos.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_neg.txt").each do |line_neg|
		a = line_neg.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "-" + "\t"+ a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end

File.open("overlap_sense_overlapping_neg.txt", 'w') do |fout|
File.open("get_sense_overlapping_neg.txt").each do |line_neg|
	b = line_neg.chomp.split("\t")
	item1 = b[0]
	File.open("get_cDNA_pos.txt").each do |line_pos|
		a = line_pos.chomp.split("\t", -1)
		next unless (a[0] == item1)
		a[2].to_i < b[2].to_i ? item2 = b[2]: item2 = a[2]
		a[3].to_i > b[3].to_i ? item3 = b[3]: item3 = a[3]
		item4 = item3.to_i - item2.to_i	
		next unless item4.to_i > 0
		puts item4
		fout.puts item1 + "\t" + "+" + "\t" + a[2] + "\t" + a[3] + "\t" + a[4] + "\t" + b[2] + "\t" + b[3] + "\t" + b[4] + "\t"+ item4.to_s
	end
end
end



