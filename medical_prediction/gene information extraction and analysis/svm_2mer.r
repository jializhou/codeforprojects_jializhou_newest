setwd("C:/Users/I311161/Desktop/gencode/whole gene/transcripts/k_mer/group4/2mer")
library(e1071)
par(mfrow=c(5,2))
min_num<-rep(0,times=10)
test_err_rate_2mer_min<-rep(0,times=10)
train_err_rate_2mer_min<-rep(0,times=10)

for (num in 1:10){
train_foreground<-paste("foreground_train_",num,".csv",sep="")
train_background<-paste("background_train_",num,".csv",sep="")
test_foreground<-paste("foreground_test_",num,".csv",sep="")
test_background<-paste("background_test_",num,".csv",sep="")

foreground_train <- read.csv(train_foreground,header = F)
foreground_train[,17]<-1
background_train <- read.csv(train_background,header = F)
background_train[,17]<-0
train_set<-rbind(foreground_train,background_train)
attach(train_set)
## classification mode
# default with factor response:
train_err_rate0<-rep(0,times=50)
train_FP_rate0<-rep(0,times=50)
train_FN_rate0<-rep(0,times=50)
err_rate_2mer<-rep(0,times=50)
FP_rate0<-rep(0,times=50)
FN_rate0<-rep(0,times=50)
for (copt in 1:50){
model <- svm(as.factor(train_set[,17]) ~ ., data = train_set[,1:16],kernel = "linear",type = "C-classification",cost = copt, scale = T)
print(model)

#test with training data
pred <- predict(model, train_set[,1:16],decision.values = T,probability = F)

# Check accuracy:
train_set[,18]<-pred
train_err_rate<-0
train_FP_rate<-0
train_FN_rate<-0
for (i in 1:nrow(train_set)){
  if(train_set[i,18] != train_set[i,17]){
    train_err_rate <- train_err_rate+1
    if(train_set[i,18]==1)
      train_FP_rate<-train_FP_rate+1
    else
      train_FN_rate<-train_FN_rate+1    
  }
}
train_err_rate0[copt]<-train_err_rate/nrow(train_set)
train_FP_rate0[copt]<-train_FP_rate/sum(train_set[,18]==0)
train_FN_rate0[copt]<-train_FN_rate/sum(train_set[,18]==1)

# test with test data
foreground_test <- read.csv(test_foreground,header = F)
foreground_test[,17]<-1
background_test <- read.csv(test_background,header = F)
background_test[,17]<-0
test_set<-rbind(foreground_test,background_test)
pred <- predict(model, test_set[,1:16],decision.values = T,probability = F)
# Check accuracy:
test_set[,18]<-pred
err_rate<-0
FP_rate<-0
FN_rate<-0
for (i in 1:nrow(test_set)){
  if(test_set[i,18] != test_set[i,17]){
    err_rate <- err_rate+1
    if(test_set[i,18]==1)
      FP_rate<-FP_rate+1
    else
      FN_rate<-FN_rate+1    
  }
}
err_rate_2mer[copt]<-err_rate/nrow(test_set)
FP_rate0[copt]<-FP_rate/sum(test_set[,18]==0)
FN_rate0[copt]<-FN_rate/sum(test_set[,18]==1)
}

# visualize (classes by color, SV by crosses):
copt<-1:50
plot(copt, err_rate_2mer,type="l")
min_num[num]<-which( err_rate_2mer == min(err_rate_2mer) )
test_err_rate_2mer_min[num]<-err_rate_2mer[min_num[num]]
train_err_rate_2mer_min[num]<-train_err_rate0[min_num[num]]
}
