nbd<-read.table(file="analysis_nbd.txt")
nbd_numeric<-numeric()
for ( i in 1:dim(nbd)[1]){
	nbd_numeric[i] = nbd[i,1]
}
hist(nbd_numeric,breaks= "Sturges",freq=FALSE)
lines(density(nbd_numeric),col="blue")

nob<-read.table(file="analysis_nob.txt")
nob_numeric<-numeric()
for ( i in 1:dim(nob)[1]){
	nob_numeric[i] = nob[i,1]
}
hist(nob_numeric,breaks= "Sturges",freq=FALSE)
lines(density(nob_numeric),col="blue")

all_sa<-read.table(file="analysis_all_sa.txt")
all_sa_numeric<-numeric()
for ( i in 1:dim(all_sa)[1]){
	all_sa_numeric[i] = all_sa[i,1]
}
hist(all_sa_numeric,breaks= "Sturges",freq=FALSE)
lines(density(all_sa_numeric),col="blue")

contained_sa<-read.table(file="analysis_contained_sa.txt")
contained_sa_numeric<-numeric()
for ( i in 1:dim(contained_sa)[1]){
	contained_sa_numeric[i] = contained_sa[i,1]
}
hist(contained_sa_numeric,breaks= "Sturges",freq=FALSE)
lines(density(contained_sa_numeric),col="blue")

divergent_sa<-read.table(file="analysis_divergent_sa.txt")
divergent_sa_numeric<-numeric()
for ( i in 1:dim(divergent_sa)[1]){
	divergent_sa_numeric[i] = divergent_sa[i,1]
}
hist(divergent_sa_numeric,breaks= "Sturges",freq=FALSE)
lines(density(divergent_sa_numeric),col="blue")

convergent_sa<-read.table(file="analysis_convergent_sa.txt")
convergent_sa_numeric<-numeric()
for ( i in 1:dim(convergent_sa)[1]){
	convergent_sa_numeric[i] = convergent_sa[i,1]
}
hist(convergent_sa_numeric,breaks= "Sturges",freq=FALSE)
lines(density(convergent_sa_numeric),col="blue")

others_sa<-read.table(file="analysis_others_sa.txt")
others_sa_numeric<-numeric()
for ( i in 1:dim(others_sa)[1]){
	others_sa_numeric[i] = others_sa[i,1]
}
hist(others_sa_numeric,breaks= "Sturges",freq=FALSE)
lines(density(others_sa_numeric),col="blue")