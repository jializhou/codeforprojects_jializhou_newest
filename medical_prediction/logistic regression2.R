library(epicalc)
hf_0<-read.csv("newdata.csv",header=T)#load the csv.file
hf_0<-na.exclude(hf_0)#exclude obervations with missing data
hf_0<-hf_0[which(hf_0$ASOURCE!=4),]
hf_0<-hf_0[which(hf_0$RACE!=5),]
hf_0<-hf_0[which(hf_0$HISPANIC_X!=3),]
row_0=nrow(hf_0)
err_rate0<-rep(0,times=50)
FP_rate0<-rep(0,times=50)
FN_rate0<-rep(0,times=50)
auc0<-rep(0,times=50)

for ( k in 1:50){
set.seed(k)
###### under sampling ########
pos_0<-hf_0[which(hf_0$readmission_30==1),]
neg_0<-hf_0[which(hf_0$readmission_30==0),]
pos_row<-sample(1:nrow(pos_0),nrow(pos_0),replace=FALSE)
neg_row<-sample(1:nrow(neg_0),nrow(pos_0),replace=FALSE)
pos<-pos_0[pos_row,]
neg<-neg_0[neg_row,]
hf0<-rbind(pos,neg)

####training set#######
row=ceiling(0.8*nrow(hf0))
hf_row<-sample(1:nrow(hf0),row,replace=FALSE)

hf<- hf0[hf_row, ]
hf2<- hf


####change the variable to the desired type#######
hf2$readmission_30<-factor(hf$readmission_30)
hf2$AGE<-as.integer(hf$AGE)
for(i in 3:9){
hf2[,i]<-factor(hf[,i])
}
hf2$LOS<-as.integer(hf$LOS)
hf2$MEDINCSTQ<-factor(hf$MEDINCSTQ)
hf2$NCHRONIC<-as.integer(hf$NCHRONIC)
hf2$NPR<-as.integer(hf$NPR)
hf2$PL_CBSA<-factor(hf$PL_CBSA)
hf2$RACE<-factor(hf$RACE)
for (i in 16:38){
  hf2[,i]<-factor(hf[,i])
}

#####build the orginal model#######
hf.logist<-glm(hf2$readmission_30 ~ hf2$AGE+hf2$ASOURCE+hf2$AWEEKEND+hf2$DISPUNIFORM+hf2$DNR+hf2$FEMALE+hf2$HCUP_ED
                   +hf2$HISPANIC_X+hf2$LOS+hf2$MEDINCSTQ+hf2$NCHRONIC+hf2$NPR+hf2$PL_CBSA+hf2$RACE+hf2$CM_ALCOHOL
                   +hf2$CM_ANEMDEF+hf2$CM_ARTH+hf2$CM_BLDLOSS+hf2$CM_CHRNLUNG+hf2$CM_COAG+hf2$CM_DEPRESS
                   +hf2$CM_DM+hf2$CM_DMCX+hf2$CM_HTN_C+hf2$CM_HYPOTHY+hf2$CM_LIVER+hf2$CM_LYTES
                   +hf2$CM_METS+hf2$CM_NEURO+hf2$CM_OBESE+hf2$CM_PARA+hf2$CM_PERIVASC+hf2$CM_PSYCH+hf2$CM_RENLFAIL+hf2$CM_TUMOR+hf2$CM_VALVE+hf2$CM_WGHTLOSS,
data=hf2,family='binomial'(link="logit"))


######conduct stepwise model selection##########
step.hf.logist<-step(hf.logist, direction=c('both'), k=2)

##### test set #######
hf1<-hf0[-hf_row, ]
hf2<-hf1
####change the variable to the desired type#######
hf2$readmission_30<-factor(hf1$readmission_30)
hf2$AGE<-as.integer(hf1$AGE)
for(i in 3:9){
hf2[,i]<-factor(hf1[,i])
}
hf2$LOS<-as.integer(hf1$LOS)
hf2$MEDINCSTQ<-factor(hf1$MEDINCSTQ)
hf2$NCHRONIC<-as.integer(hf1$NCHRONIC)
hf2$NPR<-as.integer(hf1$NPR)
hf2$PL_CBSA<-factor(hf1$PL_CBSA)
hf2$RACE<-factor(hf1$RACE)
for (i in 16:38){
  hf2[,i]<-factor(hf1[,i])
}
library(ROCR)
#####evaluate the model by examining the predictive value and actual observation############
predict.value<-predict(step.hf.logist,newdata=hf2,type="response")
predict.scores <- prediction(predict.value,hf1$readmission_30)
predict.auc0 <- performance(predict.scores, "auc")
auc0[k]<-predict.auc0@y.values

test0<-cbind(hf1, predict.value)

pos1<-test0[which(test0$predict.value>=0.6),]
pos1$predict.value<-rep(1,times=nrow(pos1))
neg1<-test0[which(test0$predict.value<0.6),]
neg1$predict.value<-rep(0,times=nrow(neg1))
test<-rbind(pos1,neg1)
for (i in 1:nrow(hf1))
{

		if (test$predict.value[i]!=test$readmission_30[i])
		{
		err_rate0[k]=err_rate0[k]+1
		if (test$predict.value[i]==1)
		FP_rate0[k]=FP_rate0[k]+1
		else
		FN_rate0[k]=FN_rate0[k]+1
		}
}
err_rate0[k]=err_rate0[k]/nrow(test)
FP_rate0[k]=FP_rate0[k]/sum(test$readmission_30==0)
FN_rate0[k]=FN_rate0[k]/sum(test$readmission_30==1)
}

data<-cbind(FP_rate0,FN_rate0,err_rate0,auc0)
write.csv(data,"logit0.6.csv",row.names=TRUE)
