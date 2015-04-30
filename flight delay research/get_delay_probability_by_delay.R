setwd("C:/Users/I311161/Documents/SAP/flight delay/research/week6")
for (i in 1:12){
name <- paste('tailnum_delay_2013_',i,'.csv',sep='')
tailnum_delay<-read.csv(name)
tailnum_delay<-na.omit(tailnum_delay[,-1])

name2<-paste('tailnum_2013_',i,'.csv',sep='')

write.csv(tailnum_delay,name2)
}
