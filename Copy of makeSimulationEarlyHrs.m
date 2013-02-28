function makeSimulationEarlyHrs(fileName)

global XLIM;
global YLIM;
XLIM=[0,3.2];
YLIM=[0,3.2];
global titleFont;

titleFont=16;

%read the population response data without antibodies
data=xlsread(fileName);
n=size(data,2);

noise=0.2;
popifn1 = log10(data(1,:)+normrnd(0,noise,1,n)); %actually 5 hours
popddx1 = log10(data(2,:));
popifn2 = log10(data(3,:)+normrnd(0,noise,1,n));
popddx2 = log10(data(4,:));
popifn3 = log10(data(5,:)+normrnd(0,noise,1,n));
popddx3 = log10(data(6,:));
popifn4 = log10(data(7,:)+normrnd(0,noise,1,n));
popddx4 = log10(data(8,:));

subplot(2,2,1);
plotContour(popifn1, popddx1, '1 hours', '', 'DDX58 induction');
setAxes;

subplot(2,2,2);
plotContour(popifn2, popddx2, '2 hours', '', '');
setAxes;

subplot(2,2,3);
plotContour(popifn3, popddx3, '3 hours', 'IFNB1 induction', 'DDX58 induction');
setAxes;

subplot(2,2,4);
plotContour(popifn4, popddx4, '4 hours', 'IFNB1 induction', '');
setAxes;

end

function plotContour(ifndata, ddxdata, Title, Xlabel, Ylabel)
global titleFont;
labelFont=12;
grey=[0 0 0];
%grey=[.5 .5 .5];
%numBins=10;
%interpolations=1;
%contours=10;
%Xbins=linspace(0,4,numBins);
%Ybins=linspace(0,4,numBins);

plot(ifndata, ddxdata,'.','color',grey);
%hold on;
%[H,x,y]=hist2d(ifndata,ddxdata,Xbins,Ybins);
%H=H/sum(sum(H));
%n=length(x(1,:));
%H=interp2(H,interpolations);
%X=linspace(min(x(1,:)),max(x(1,:)),(2^interpolations)*(n-1)+1);
%Y=linspace(min(y(:,1)),max(y(:,1)),(2^interpolations)*(n-1)+1);
%contour(X,Y,H,contours);
hold off;
title(Title,'FontSize',titleFont);
xlabel(Xlabel,'FontSize',labelFont);
ylabel(Ylabel,'FontSize',labelFont);
end

function setAxes()
axes1=gca;
TickLabel={'0.1','1','10','100','1000','10000'};
Tick=-1:4;
global YLIM;
global XLIM;
set(axes1,'YTickLabel',TickLabel);
set(axes1,'YTick',Tick);
set(axes1,'XTickLabel',TickLabel);
set(axes1,'XTick',Tick);
set(axes1,'YLIM',YLIM);
set(axes1,'XLIM',XLIM);
end
