term<-c("egypt","jordan","israel","saudi")
term_vec<-foreach(i=1:length(all_score_frames),.combine=rbind) %do%
{
  score_row<-rep(0,length(term))
  for(z in 1:length(score_row))
  {
    sel_score<-all_score_frames[[i]][all_score_frames[[i]]$term==term[z],"score"]
    sel_score[is.na(sel_score)]<-0
    if(length(sel_score)==0)
      sel_score<-0
    score_row[z]<-round(sel_score,5)
  }
  as.numeric(c(date_max_list[i],score_row))
}
term_vec<-as.data.frame(term_vec)
names(term_vec)<-c("year",term)

term_df <- melt(term_vec, id.vars="year")
term_means<-sapply(all_score_frames,function(x) mean(x$score))

text_size<-40
ggplot(data=term_df,aes(x=year, y=value, colour=variable))+geom_line(size=1) + geom_line(aes(x = as.numeric(date_max_list), y = term_means), colour = "black",size=1.5) + ylab("sentiment") + opts(title = expression("US Sentiment (+/-) Over Time"),legend.text=theme_text(size=text_size),legend.title=theme_text(size=0),plot.title=theme_text(size=text_size),axis.text.y=theme_text(size=text_size),axis.text.x=theme_text(size=text_size),axis.title.y=theme_text(size=text_size,angle=90),axis.title.x=theme_text(size=text_size),legend.key.size=unit(2,"cm"))