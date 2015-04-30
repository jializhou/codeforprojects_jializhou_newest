setwd("C:/Users/I311161/Desktop/gencode/whole gene/transcripts/k_mer/2/1")
library(rpart)
library(ROCR)

##training set##
foreground_train <- read.csv("foreground_train.csv",header = F)
foreground_train[,17]<-1
background_train <- read.csv("background_train.csv",header = F)
background_train[,17]<-0
train_set<-rbind(foreground_train,background_train)
attach(train_set)
## classification mode
# default with factor response:
train_err_rate0<-rep(0,times=50)
train_FP_rate0<-rep(0,times=50)
train_FN_rate0<-rep(0,times=50)
err_rate_2mer<-rep(0,times=50)
test_FP_rate0<-rep(0,times=50)
test_FN_rate0<-rep(0,times=50)
for (copt in 1:1){
  model<-rpart(as.factor(train_set[,17]) ~ train_set[,1]+train_set[,2]+train_set[,3]+train_set[,4]+train_set[,5]
               +train_set[,6]+train_set[,7]+train_set[,8]+train_set[,9]+train_set[,10]
               +train_set[,11]+train_set[,12]+train_set[,13]+train_set[,14]+train_set[,15]+train_set[,16],
               data=train_set,method="class",control=rpart.control(cp=0))
  
#puned tree model##
#model_pruned<-prune(model,cp=model$cptable[which.min(model$cptable[,"xerror"]),"CP"])

#test with training data
  pred <- predict(model_pruned, newdata=train_set,type = "prob")
  scores_train<-prediction(pred[,2],train_set[,17])
  auc_train<-performance(scores_train,"auc")
  auc_score_train<-auc_train@y.values

  pred_train<-predict(model_pruned,newdata=train_set, type="class")
  # Check accuracy:
  train_set[,18]<-pred_train
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

pred_auc_test <- predict(model_pruned, newdata=test_set,type = "prob")
scores_test<-prediction(pred_auc_test[1:nrow(test_set),2],test_set[,17])
auc_test<-performance(scores_test,"auc")
auc_score_test<-auc_test@y.values

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
plot(copt, test_err_rate_2mer,type="l")
