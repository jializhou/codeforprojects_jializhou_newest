setwd("C:/Users/I311161/Desktop/gencode/whole gene/transcripts/k_mer/group4/2mer")
library(randomForest)
library(ROCR)
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
err_rate_2mer<-rep(0,times=50)
test_FP_rate0<-rep(0,times=50)
test_FN_rate0<-rep(0,times=50)
for (copt in 1:50){
  model<-randomForest(x=train_set[,1:16],y=as.factor(train_set[,17]),data=train_set,proximity=T,importance=T,ntree=100+8*copt,oob.prox=T)
  #model<-tuneRF(x=train_set[,1:16],y=as.factor(train_set[,17]),stepFactor = 2, improve = 0.05,
  #              trace = TRUE, plot = TRUE, doBest = TRUE)
  #display results of random forest
  #print(model)
  #determine important variables
  #importance(model)

  
  #test with training data
  train_err_rate0[copt]<-mean(model$err.rate[,1])
  
  # test with test data
  foreground_test <- read.csv(test_foreground,header = F)
  foreground_test[,17]<-1
  background_test <- read.csv(test_background,header = F)
  background_test[,17]<-0
  test_set<-rbind(foreground_test,background_test)
  
  
  pred_test<-predict(model,newdata=test_set, type="class")
  # Check accuracy:
  test_set[,18]<-pred_test[1:nrow(test_set)]
  test_err_rate<-0
  test_FP_rate<-0
  test_FN_rate<-0
  for (i in 1:nrow(test_set)){
    if(test_set[i,18] != test_set[i,17]){
      test_err_rate <- test_err_rate+1
      if(test_set[i,18]==1)
        test_FP_rate<-test_FP_rate+1
      else
        test_FN_rate<-test_FN_rate+1    
    }
  }
  err_rate_2mer[copt]<-test_err_rate/nrow(test_set)
  test_FP_rate0[copt]<-test_FP_rate/sum(test_set[,18]==0)
  test_FN_rate0[copt]<-test_FN_rate/sum(test_set[,18]==1)
}


# visualize (classes by color, SV by crosses):
copt<-1:50
plot(copt, err_rate_2mer,type="l")
min_num[num]<-which( err_rate_2mer == min(err_rate_2mer) )
test_err_rate_2mer_min[num]<-err_rate_2mer[min_num[num]]
train_err_rate_2mer_min[num]<-train_err_rate0[min_num[num]]
}
