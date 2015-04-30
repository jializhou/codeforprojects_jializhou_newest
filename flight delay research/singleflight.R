
args=(commandArgs(TRUE))
if (length(args)==0){
  yearmonth_inds=168:171
  flight_inds = 5
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
query <-  'select distinct "TailNum" from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "TailNum"';
TailNum<- dbGetQuery(conn,query)   
TailNum<-na.omit(TailNum)

### select OriginCityName
query <-  'select distinct "OriginCityName"  from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "OriginCityName"';
OriginCityName <- dbGetQuery(conn,query) 

### select DestCityName
query <-  'select distinct "DestCityName"  from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT order by "DestCityName"';
DestCityName <- dbGetQuery(conn,query) 

Year_Month_get <- Year_Month[,1]*100+Year_Month[,2]

singleflight_delay<- data.frame(Year=1987,Month=9,DayofMonth=1,
                                TailNum=factor(TailNum[1,1],levels<-TailNum[,1]),CNT=0,
                                OriginCityName=factor(OriginCityName[1,1],levels<-OriginCityName[,1]),
                                DestCityName=factor(DestCityName[1,1],levels<-DestCityName[,1]),
                                CRSDEPDATETIME=0,CRSARRDATETIME=0,DepDelay=0,ArrDelay=0)

for (yearmonth_ind in yearmonth_inds){
  for (dayofmonth_ind in dayofmonth_inds){
    for (flight_ind in flight_inds){
      select_year<-Year_Month[yearmonth_ind,1];
      select_month<-Year_Month[yearmonth_ind,2];
      select_dayofmonth<-DayofMonth[dayofmonth_ind,1]
      select_flight<-TailNum[flight_ind,1];
      query<- paste('select count(*) as cnt,"OriginCityName" as "OriginCity","DestCityName" as "DestCity",
                    "CRSDEPDATETIME" as "DEPDATETIME","CRSARRDATETIME" as "ARRDATETIME","DepDelay" as "DepDelay",
                    "ArrDelay" as "ArrDelay"from FLIGHT_DELAY.FLIGHTS_UTC_CORRECT where  
                    "TailNum"=\'',select_flight,'\' and "Year"=\'',select_year,'\'  and "Month"=\'',select_month,
                    '\' and "DayofMonth"=\'',select_dayofmonth,
                    '\'group by "OriginCityName","DestCityName","CRSDEPDATETIME","CRSARRDATETIME","DepDelay","ArrDelay"',sep='');
      select_flights <- dbGetQuery(conn,query)
      if (nrow(select_flights)>0){
        newline<-data.frame(c(select_year,select_month,select_dayofmonth,select_flight,select_flights))
        names(newline)<-names(singleflight_delay)
        singleflight_delay <- rbind(singleflight_delay,newline);  
      }
    }
  }
}

singleflight_delay<- singleflight_delay[-1,]
write.csv(singleflight_delay,"singleflight_delay.csv")
dbDisconnect(conn)
