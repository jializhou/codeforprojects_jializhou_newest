require 'rake'

foreground_filelist = FileList["*.fa"].reject{|f| f =~ /background/}

background_filelist = FileList["*.fa"].reject{|f| f =~ /foreground/}

File.open("background.fa","w") {|f| f.puts background_filelist.map{|nm| IO.read nm}}

File.open("foreground.fa","w") {|f| f.puts foreground_filelist.map{|nm| IO.read nm}}

