setwd("C:/Users/I311161/Desktop/gencode/whole gene/transcripts/k_mer/2/1")
library(e1071)
library(MASS)
library(corpcor)
library(statmod)
library(tgp)
library(mlegp)
library(lhs)
library(penalizedSVM)

foreground_train <- read.csv("foreground_train.csv",header = F)
foreground_train[,17]<-1
background_train <- read.csv("background_train.csv",header = F)
background_train[,17]<-0
train_set<-as.matrix(rbind(foreground_train,background_train))


## classification mode
# default with factor response:
x<-train_set[,1:16]
y<-train_set[,17]
model_train<-scadsvc(x,y=y,lambda=0.01)

  
#test with training data
pred <- findgacv.scad(train_set[,17],model=model_train)
  
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
  train_err_rate0<-train_err_rate/nrow(train_set)
  train_FP_rate0<-train_FP_rate/sum(train_set[,18]==0)
  train_FN_rate0<-train_FN_rate/sum(train_set[,18]==1)
  
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
err_rate_2mer<-err_rate/nrow(test_set)
FP_rate0<-FP_rate/sum(test_set[,18]==0)
FN_rate0<-FN_rate/sum(test_set[,18]==1)


