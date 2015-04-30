#!/usr/bin/env ruby
# encoding: UTF-8
require 'rake'
white_list = {}; ["chr1", "chr2", "chr3", "chr4", "chr5", "chr6", "chr7", "chr8", "chr9", "chrM", "chrX", "chrY", "chr12", "chr14", "chr16", "chr15", "chr17", "chr18", "chr13", "chr11", "chr19", "chr10", "chr20", "chr21", "chr22"].each { |n| white_list[n] = true }

n=0

# chr1	HAVANA	gene	11869	14409	.	+	.	gene_id "ENSG00000223972.5"; transcript_id "ENSG00000223972.5"; 
# gene_type "transcribed_unprocessed_pseudogene"; gene_status "KNOWN"; gene_name "DDX11L1"; 
# transcript_type "transcribed_unprocessed_pseudogene"; 
# transcript_status "KNOWN"; transcript_name "DDX11L1"; 
# level 2; havana_gene "OTTHUMG00000000961.2";


File.open("antisense_pos.txt", 'w') do |foutP_antisense|
File.open("antisense_neg.txt", 'w') do |foutN_antisense|
File.open("cRNA_pos.txt", 'w') do |foutP_cRNA|
File.open("cRNA_neg.txt", 'w') do |foutN_cRNA|
File.open("lincRNA_pos.txt", 'w') do |foutP_lincRNA|
File.open("lincRNA_neg.txt", 'w') do |foutN_lincRNA|
File.open("lnRNA_pos.txt", 'w') do |foutP_lnRNA|
File.open("lnRNA_neg.txt", 'w') do |foutN_lnRNA|
File.open("sense_intronic_pos.txt", 'w') do |foutP_intronic|
File.open("sense_intronic_neg.txt", 'w') do |foutN_intronic|
File.open("sense_overlapping_pos.txt", 'w') do |foutP_sense_overlapping|
File.open("sense_overlapping_neg.txt", 'w') do |foutN_sense_overlapping|
	File.open("gencode.v21.annotation.gtf").each do |line|
		n = n+1
		next if n < 6 
		col = line.chomp.split("\t")
	    if white_list[col[0]]
	    	name = col[8].chomp.split(";")
	    	gene_id = name[0].chomp.split("\"")
	    	gene_type = name[2].chomp.split("\"")
	    	#puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]
	    	#(col[6] == '+' ? foutp : foutn).puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]  if col[2]=="gene"
	    	next unless col[2] == "transcript"
	    	(col[6] == '+' ? foutP_antisense : foutN_antisense).puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]  if gene_type[1] =="antisense"
	    	(col[6] == '+' ? foutP_cRNA : foutN_cRNA).puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]  if gene_type[1] =="protein_coding"
	    	(col[6] == '+' ? foutP_lincRNA : foutN_lincRNA).puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]  if gene_type[1] =="lincRNA"
	    	(col[6] == '+' ? foutP_lnRNA : foutN_lnRNA).puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]  if gene_type[1] =="non_coding"
	    	(col[6] == '+' ? foutP_intronic : foutN_intronic).puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]  if gene_type[1] =="sense_intronic"
	    	(col[6] == '+' ? foutP_sense_overlapping : foutN_sense_overlapping).puts col[0]+"\t"+col[6]+"\t"+col[3]+"\t"+col[4]+"\t"+gene_id[1]  if gene_type[1] =="sense_overlapping"
		end
	end
end
end
end
end
end
end
end
end
end
end
end
end



# File.open("gencode.v21.annotation.gtf").each do |line|
# 	n = n+1
# 	next if n < 6 
# 	col = line.chomp.split(";")
# 	if n==7
# 		puts col[0]
# 		puts col[1]
# 		puts col[3]
# 		puts col[4]+"\t"  
# 	end  
# end