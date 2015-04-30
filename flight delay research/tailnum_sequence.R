setwd("C:/Users/I311161/Documents/SAP/flight delay/research/week6")
args=(commandArgs(TRUE))
if (length(args)==0){
  yearmonth_inds=304:304
  #dayofmonth_inds = 1:7
  #dayofmonth_inds = 8:20
  dayofmonth_inds = 1:30
}else{
  for(i in 1:length(args)){
    print(args[[i]])
    eval(parse(text=args[[i]]))
  }  
}

library(ggplot2)
library(reshape)
library(googleVis)
if (Sys.getenv("JAVA_HOME")!="")
  Sys.setenv(JAVA_HOME="")
library(DBI)
options(java.parameters = "-Xmx2048m")
library(rJava)
library(RJDBC)

port = "30015"
host = "10.128.80.235"
uid = "FLIGHT_DELAY"
pwd = "Initial123"
dbname = "FLIGHT_DELAY"
jdbcDriver <- JDBC("com.sap.db.jdbc.Driver", "C:/Users/I311161/Documents/R/ngdbc.jar",identifier.quote="`")
conn <- dbConnect(jdbcDriver, paste("jdbc:sap:", host, ":", port, sep=""), uid, pwd,dbname)


### select years
query <-  'select distinct "Year","Month" from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "Year", "Month"';
Year_Month <- dbGetQuery(conn,query)          # 1987.10-->1   2014 04   319
Year_Month <- Year_Month[1:319,]


### select dayofmonth
query <-  'select distinct "DayofMonth" from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "DayofMonth"';
DayofMonth <- dbGetQuery(conn,query)          # 1987.10-->1   2014 04   319

### select TailNum
query <- 'select distinct "TailNum" from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "TailNum"';
TailNum<- dbGetQuery(conn,query) 
TailNum<-na.omit(TailNum)

### select OriginCityName
query <-  'select distinct "OriginAirportID"  from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "OriginAirportID"';
OriginAirportID <- dbGetQuery(conn,query) 

### select DestCityName
query <-  'select distinct "DestAirportID"  from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "DestAirportID"';
DestAirportID <- dbGetQuery(conn,query) 
### select OriginCityName
query <-  'select distinct "OriginCityName"  from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "OriginCityName"';
OriginCityName <- dbGetQuery(conn,query) 

### select DestCityName
query <-  'select distinct "DestCityName"  from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "DestCityName"';
DestCityName <- dbGetQuery(conn,query) 



for (yearmonth_ind in yearmonth_inds){
#       tailnum_delay<- data.frame(Year=1987,Month=9,DayofMonth=1,
#                                  TailNum=factor(TailNum[1,1],levels<-TailNum[,1]),
#                                  OriginAirportID=factor(OriginAirportID[1,1],levels<-OriginAirportID[,1]),
#                                  DestAirportID=factor(DestAirportID[1,1],levels<-DestAirportID[,1]),
#                                  OriginCityName=factor(OriginCityName[1,1],levels<-OriginCityName[,1]),
#                                  DestCityName=factor(DestCityName[1,1],levels<-DestCityName[,1]),
#                                  CRSDEPDATETIME=0,CRSARRDATETIME=0,DepDelay=0,ArrDelay=0)
  for (dayofmonth_ind in dayofmonth_inds){
        select_year<-Year_Month[yearmonth_ind,1];
        select_month<-Year_Month[yearmonth_ind,2];
        query <-  paste('select distinct "TailNum" from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT where  
                    "Year"=\'',select_year,'\'  and "Month"=\'',select_month,'\' group by "TailNum"',sep='');
        TailNum<- dbGetQuery(conn,query)   
        TailNum<-na.omit(TailNum)
        tailnum_inds1<-1:(floor(nrow(TailNum)/2)-1)
        tailnum_inds2<-(length(tailnum_inds1)+1):nrow(TailNum)
    for (tailnum_ind in tailnum_inds1){
        select_dayofmonth<-DayofMonth[dayofmonth_ind,1]
        select_tailnum<-TailNum[tailnum_ind,1]
        query<- paste('select "OriginAirportID" as "OriginAirport", "DestAirportID" as "DestAirport", "OriginCityName" as "OriginCity","DestCityName" as "DestCity",
                    "CRSDEPDATETIME" as "DEPDATETIME","CRSARRDATETIME" as "ARRDATETIME","DepDelay" as "DepDelay",
                    "ArrDelay" as "ArrDelay"from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT where 
                    "DepDelay" >0 or "ArrDelay" > 0 and 
                    "Year"=\'',select_year,'\'  and "Month"=\'',select_month,
                    '\' and "DayofMonth"=\'',select_dayofmonth,
                    '\'and "TailNum"=\'',select_tailnum,
                    '\' group by "OriginAirportID", "DestAirportID","OriginCityName","DestCityName","CRSDEPDATETIME","CRSARRDATETIME","DepDelay","ArrDelay" order by "CRSDEPDATETIME"',sep='');
        select_airports <- dbGetQuery(conn,query)
        if (nrow(select_airports)>0){
         newline<-data.frame(c(select_year,select_month,select_dayofmonth,select_tailnum,select_airports))
         names(newline)<-names(tailnum_delay)
         name <-  paste('tailnum_delay1_',select_year,'_',select_month,'_',select_dayofmonth,'_',select_tailnum,'.csv',sep='');
         write.csv(newline,name)
      }
    }
  }
}


dbDisconnect(conn)
