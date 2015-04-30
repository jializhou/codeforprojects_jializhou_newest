setwd("C:/Users/I311161/Desktop/gencode/whole gene/transcripts/k_mer/2/1")
library(e1071)

foreground_train <- read.csv("foreground_train.csv",header = F)
background_train <- read.csv("background_train.csv",header = F)
train_set<-rbind(foreground_train,background_train)
## classification mode
# default with factor response:
train_err_rate0<-rep(0,times=500)
train_FP_rate0<-rep(0,times=500)
train_FN_rate0<-rep(0,times=500)
err_rate_2mer<-rep(0,times=500)
FP_rate0<-rep(0,times=500)
FN_rate0<-rep(0,times=500)
for (copt in 1:500){
  index<-1:nrow(train_set)
  train_pos_index<-sample(index,trunc(length(index)*0.5),replace=F)
  train_set[train_pos_index,17]<-1
  train_set[-train_pos_index,17]<-0
  attach(train_set)
  model <- svm(as.factor(train_set[,17]) ~ ., data = train_set[,1:16],kernel = "linear",type = "C-classification", scale = T)
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
  foreground_test <- read.csv("foreground_test.csv",header = F)
  foreground_test[,17]<-1
  background_test <- read.csv("background_test.csv",header = F)
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
hist(err_rate_2mer,breaks=20, xlim=c(0.3,0.7))
sum(err_rate_2mer<0.403)/500