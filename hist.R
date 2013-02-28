x<-read.table("Out_final_concentration_results.txt",sep="\t")
pdf("hist1.pdf",width=11,height=8.5)
nc<-sqrt(ncol(x))
par(mfrow=c(3,4))
for(i in 1:12){
    hist(as.numeric(x[i,]),xlab="",main="",nclass=nc)
}
dev.off()