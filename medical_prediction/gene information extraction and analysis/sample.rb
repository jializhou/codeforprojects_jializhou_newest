#!/usr/bin/env ruby
# encoding: UTF-8
require 'rake'

foreground_list = (1..4720).to_a
test_foreground_list = foreground_list.sample(400)
train_foreground_list = (foreground_list - test_foreground_list).sample(4000)

background_list = (1..15161).to_a
test_background_list = background_list.sample(400)
train_background_list = (background_list - test_background_list).sample(4000)


File.open("foreground_test.fa", 'w') do |foreground_test|
File.open("foreground_train.fa", 'w') do |foreground_train|
	temp = ""
	n = 0
	File.open("foreground.fa").each do |line|
		DNA = line.chomp.split(/[\d]/)
		if DNA[0] == ">chr"
			n = n+1
			if test_foreground_list.include? n-1
				foreground_test.puts temp
				temp =""
			elsif train_foreground_list.include? n-1
				foreground_train.puts temp
				temp =""
			end
			if test_foreground_list.include? n
				foreground_test.puts line
			elsif train_foreground_list.include? n
				foreground_train.puts line
			end
		else
			line = temp+line
			temp = line.chomp
		end
	end				
end
end


File.open("background_test.fa", 'w') do |background_test|
File.open("background_train.fa", 'w') do |background_train|
	temp = ""
	n = 0
	File.open("background.fa").each do |line|
		DNA = line.chomp.split(/[\d]/)
		if DNA[0] == ">chr"
			n = n+1
			if test_background_list.include? n-1
				background_test.puts temp
				temp =""
			elsif train_background_list.include? n-1 
				background_train.puts temp
				temp =""
			end
			if test_background_list.include? n
				background_test.puts line
			elsif train_background_list.include? n
				background_train.puts line
			end
		else
			line = temp+line
			temp = line.chomp
		end
	end				
end
end
