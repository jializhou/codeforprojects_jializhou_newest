library(RCurl)
library(rjson)
getfriendlist <- function(uid){
thisurl <- paste("http://friend.renren.com/GetFriendList.do?curpage=0&id=", uid, sep="")
hh <- getURL(thisurl, curl=cH, encoding="gbk")
# 多少页
write(hh,"website.txt")
imax <- 0

if(length(grep("最后页", hh)) > 0){
h<-strsplit(hh,"最后页")[[1]][2]
imax <- strsplit(h, "curpage=")[[1]][2]
imax <- strsplit(imax, "&amp")[[1]][1]
}
if(length(grep("最后页", hh)) == 0 & length(grep("下一页", hh)) > 0){
h<-strsplit(hh,"下一页")[[1]][2]
imax <- strsplit(h, "curpage=")[[1]][2]
imax <- strsplit(imax, "&amp")[[1]][1]
}

imax <- as.numeric(imax)
imax<-imax+1

# 我的名字
u0 <- strsplit(hh[grep("的好友</title>", hh)], "的好友</title>")[[1]][1]
u0 <- strsplit(u0, "人人网 - ")[[1]][2]
u0
friend <- data.frame(id0=NULL, u1=NULL, id1=NULL)
# 页面循环
if(imax >= 1){
for(pagei in 1:imax){
	thisurl <- paste("http://friend.renren.com/GetFriendList.do?curpage=", pagei-1, "&id=", uid, sep="")
	hh <- getURL(thisurl, curl=cH, encoding="gbk")
	# 搜索每个好友的名字。每个好友都可以即时聊天。忘记为什么了，有的只有‘打个招呼’
	h <- strsplit(hh,"即时聊天")[[1]]
	if(length(ii) >= 1){
		for(j in 1:length(ii)){
		h0 <- h[j]
		ff <- strsplit(h0, "event,'")[[1]][2]
		ff <- strsplit(ff, "'[)]")[[1]][1]
		ff1 <- strsplit(ff, "','")[[1]][1]
		ff2 <- strsplit(ff, "','")[[1]][2]
		friendnew <- data.frame(id0=uid,u1=ff2, id1=ff1)
		friend <- rbind(friend, friendnew)
		}
	}
}
}
colnames(friend)<-c("id0","u1","id1")
return(friend)
}
name="18911020762"
pwd="2HBB8SJS"

memory.limit(4000)

myH <- c(
"User-Agent"="Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.12) Gecko/20101026 Firefox/3.6.12",
"Accept"="text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
"Accept-Language"="zh-cn,zh;q=0.5",
#"Accept-Encoding"="gzip,deflate",
"Accept-Charset"="GB2312,utf-8;q=0.7,*;q=0.7",
"Keep-Alive"="115",
"Connection"="keep-alive",
#"Host"="status.renren.com",
"Content-Type"="application/x-www-form-urlencoded; charset=UTF-8",
#"Content-Length"=as.character(nchar(xx)*2+1),
"Pragma"="no-cache",
#"Referer"="http://status.renren.com/ajaxproxy.htm",
"Cache-Control"="no-cache"
)
d <- debugGatherer()
cH <- getCurlHandle(debugfunction=d$update, verbose=T, ssl.verifyhost=F, 
ssl.verifypeer=F, followlocation=T, cookiefile="cc.txt")
pinfo <- c(
"email"=name,
"password"=pwd,
"origURL"="http://www.renren.com/Home.do",
"domain"="renren.com"
)
pinfo <- iconv(pinfo, from="GB18030", to="UTF-8")
ttt <- postForm("http://passport.renren.com/PLogin.do", httpheader=myH,
.params=pinfo, curl=cH, style="post")
getCurlInfo(cH)[["cookielist"]]

h <- getURL("http://www.renren.com", curl=cH, encoding="gbk")
write(h, "temp.txt")
hh <- readLines("temp.txt", encoding="gbk")

rm(h)
hh <- hh[grep("ruid", hh)]
hh <- gsub("[^0-9]", "", hh)
uid <- hh
 uid
#  "348722945"
myfriend<-na.omit(getfriendlist(uid))

friend_ggdata

friend_gg1<-data.frame(id0=NULL,u1=NULL, id1=NULL)
friend_gg2<-data.frame(id0=NULL,u1=NULL, id1=NULL)
for(i in 1:nrow(myfriend)){
id<-myfriend[i,3]
friend_friend<-na.omit(getfriendlist(id))
friend_gg1<-rbind(friend_gg1,friend_friend)
fri_gg1 <- friend_friend[which(friend_friend$id1 %in% myfriend[,3]),]
fri_gg2<-na.omit(fri_gg1)
friend_gg2<-rbind(friend_gg2,fri_gg2)
}
a<-friend_ggdata2[,2]
friend_ggdata2[,2]<-friend_ggdata2[,3]
friend_ggdata2[,3]<-a
b<-friend_ggdata1[,2]
friend_ggdata1[,2]<-friend_ggdata1[,3]
friend_ggdata1[,3]<-b
c<-myfriend[,2]
myfriend[,2]<-myfriend[,3]
myfriend[,3]<-c
colnames(friend_ggdata1)<-c("id0","id1","u1")
colnames(friend_ggdata2)<-c("id0","id1","u1")
colnames(myfriend)<-c("id0","id1","u1")
