#f_ggdata1<-friend_ggdata1
#f_ggdata2<-friend_ggdata2

library(igraph)
people <- unique(data.frame(id=myfriend[, 3], name=myfriend[, 2]))
gg <- graph.data.frame(d=friend_ggdata2, directed=F, vertices=people)
is.simple(gg)
gg <- simplify(gg)
is.simple(gg)
par(mar=c(0,0,0,0))
set.seed(14)
plot(gg,layout=layout.fruchterman.reingold,vertex.size=5,vertex.color="green", 
vertex.label=NA,
edge.color=grey(0.5),edge.arrow.mode="-")

dg <- degree(gg)
gg <- subgraph(gg, which(dg > 0) - 1)

# 子群划分
com <- walktrap.community(gg,steps=6)
V(gg)$sg <- com$membership + 1
V(gg)$color <- rainbow(max(V(gg)$sg))[V(gg)$sg]
# 中间度
V(gg)$bte <- betweenness(gg, directed=F)
top <- quantile(V(gg)$bte,0.98)
V(gg)$size <- 4
V(gg)[bte>=top]$size <- 15
V(gg)$label <- NA
V(gg)[bte>=top]$label <- V(gg)[bte>=top]$name
V(gg)$cex <- 1
V(gg)[bte>=top]$cex <- 2
plot(V(gg)$bte)
png("renren_friend_community_betweenness1.png",width=900,height=900)
par(mar=c(0,0,0,0))
set.seed(14)
plot(gg,
layout=layout.kamada.kawai,#layout.fruchterman.reingold,
vertex.size=V(gg)$size, vertex.color=V(gg)$color,
vertex.label=V(gg)$label, vertex.label.cex=V(gg)$cex,
edge.color=grey(0.8)
)
dev.off()
print(V(gg)[bte>=top]$name)

temp3=friend_ggdata1[which(!(friend_ggdata1[,2] %in% myfriend[,2])),]
temp3=temp3[which(!(temp3[,2] %in% myfriend[,1])),]
listall = sort(table(temp3[,2]),dec=T)
top=names(listall[1:20])
top
temp4=unique(temp3[which(temp3[,2] %in% top),3])
top20 = sort(table(temp4),dec=T)
top20








