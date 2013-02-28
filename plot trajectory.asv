C=load('Out_singleCells_concentrations.txt');
IFN=C(1:3:size(C,1),:);
RIG=C(2:3:size(C,1),:);
boundRs=C(3:3:size(C,1),:);
R=load('Out_singleCells_rates.txt');
R_ifn=R(5:8:size(R,1),:);
R_rig=R(1:8:size(R,1),:);

%for cellNo=76:96;
%plot(IFN(:,cellNo),RIG(:,cellNo));
cellNo=31;
%scatter(IFN(:,cellNo),RIG(:,cellNo),15,R_ifn(:,cellNo));
%scatter(IFN(:,cellNo),R_rig(:,cellNo));%,15,RIG(:,cellNo));
T=(0:size(RIG,1)-1)*10;
scatter3(IFN(:,cellNo),R_rig(:,cellNo),RIG(:,cellNo),50,T(:));
view([0,0,1]);
hold on; plot3(IFN(:,cellNo),R_rig(:,cellNo),RIG(:,cellNo)); hold off;
%text(IFN(:,cellNo),R_rig(:,cellNo),strcat('t=',num2str(T(:))));
%text(IFN(:,cellNo),R_rig(:,cellNo),strcat('RIG=',num2str(RIG(:,cellNo)),', t=',num2str(T(:))));
%ylim([0,500]);
%xlim([4,19]);
%hold on;
%end

%hold off;