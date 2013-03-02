clc;
clf;
close('all');
clear all;
load fusion-analyzer-data.log
%--------------------------------------------------------------------------------------------------------
fig2Handle = figure(2);
set(fig2Handle, 'Position', [100, 100, 600, 1000]);
%-------------------------
subplot(3,1,1)
% axis control and adjustment
[ax1] = axescheck(fusion_analyzer_data(:,15), fusion_analyzer_data(:,1));
ax1 = newplot(ax1);
set(ax1,'XGrid','on');
set(ax1,'YGrid','on');
if ~ishold(ax1)
  [minx1,maxx1] = minmax(fusion_analyzer_data(:,15));
  [miny1,maxy1] = minmax(fusion_analyzer_data(:,1));
  axis(ax1,[minx1 maxx1 miny1 maxy1])
end
title('Maps values during simulation');
ylabel('Map 1 values')
xlabel('Data points')
hc1 =  line('parent',ax1, 'linestyle','-','erase','xor','xdata',fusion_analyzer_data(1,15),'ydata',fusion_analyzer_data(1,1));
ha1 = line('parent',ax1,'linestyle','-','erase','none','xdata',[],'ydata',[]);
%-------------------------
subplot(3,1,2)
% axis control and adjustment
[ax2] = axescheck(fusion_analyzer_data(:,15), fusion_analyzer_data(:,2));
ax2 = newplot(ax2);
set(ax2,'XGrid','on');
set(ax2,'YGrid','on');
if ~ishold(ax2)
  [minx2,maxx2] = minmax(fusion_analyzer_data(:,15));
  [miny2,maxy2] = minmax(fusion_analyzer_data(:,2));
  axis(ax2,[minx2 maxx2 miny2 maxy2])
end
ylabel('Map 2 values')
xlabel('Data points')
hc2 =  line('parent',ax2,'linestyle','-','erase','xor','xdata',fusion_analyzer_data(1,15),'ydata',fusion_analyzer_data(1,2));
ha2 = line('parent',ax2,'linestyle','-','erase','none','xdata',[],'ydata',[]);
%-------------------------
subplot(3,1,3)
% axis control and adjustment
[ax3] = axescheck(fusion_analyzer_data(:,1), fusion_analyzer_data(:,2));
ax3 = newplot(ax3);
if ~ishold(ax3)
  [minx3,maxx3] = minmax(fusion_analyzer_data(:,1));
  [miny3,maxy3] = minmax(fusion_analyzer_data(:,2));
  axis(ax3,[minx3 maxx3 miny3 maxy3])
end
t = -1.0:1.0;
plot(t, 3*t, '-m');
set(ax3,'XGrid','on');
set(ax3,'YGrid','on');
hc3 =  line('parent',ax3,'linestyle','-','erase','xor','xdata',fusion_analyzer_data(1,1),'ydata',fusion_analyzer_data(1,2));
ha3 = line('parent',ax3,'linestyle','-','erase','none','xdata',[],'ydata',[]);
title('M2 dependency on M1');
xlabel('M1 values');
ylabel('M2 values');
% small pause to start recording with external device
pause(5); % s
% dynamic plot simulataneously in all subplots
for i=2:length(fusion_analyzer_data(:,15))
    j = i-1:i;
    set(hc1,'xdata', fusion_analyzer_data(i,15), 'ydata', fusion_analyzer_data(i,1));
    set(ha1,'xdata', fusion_analyzer_data(j,15), 'ydata', fusion_analyzer_data(j,1));
    set(hc2,'xdata', fusion_analyzer_data(i,15), 'ydata', fusion_analyzer_data(i,2));
    set(ha2,'xdata', fusion_analyzer_data(j,15), 'ydata', fusion_analyzer_data(j,2));
    set(hc3,'xdata', fusion_analyzer_data(i,1), 'ydata', fusion_analyzer_data(i,2));
    set(ha3,'xdata', fusion_analyzer_data(j,1), 'ydata', fusion_analyzer_data(j,2));
    drawnow;
end

%--------------------------------------------------------------------------------------------------------
fig3Handle = figure(3);
set(fig3Handle, 'Position', [900, 900, 600, 1200]);
subplot(4,1,1)
% axis control and adjustment
[ax4] = axescheck(fusion_analyzer_data(:,15), fusion_analyzer_data(:,3));
ax4 = newplot(ax4);
set(ax4,'XGrid','on');
set(ax4,'YGrid','on');
if ~ishold(ax4)
  [minx4,maxx4] = minmax(fusion_analyzer_data(:,15));
  [miny4,maxy4] = minmax(fusion_analyzer_data(:,3));
  axis(ax4,[minx4 maxx4 miny4 maxy4])
end
title('Maps values during simulation');
hc4 =  line('parent',ax4, 'linestyle','-','erase','xor','xdata',fusion_analyzer_data(1,15),'ydata',fusion_analyzer_data(1,3));
ha4 = line('parent',ax4,'linestyle','-','erase','none','xdata',[],'ydata',[]);
ylabel('Map 3 values')
xlabel('Data points')

%-------------
subplot(4,1,2)
% axis control and adjustment
[ax5] = axescheck(fusion_analyzer_data(:,15), fusion_analyzer_data(:,4));
ax5 = newplot(ax5);
set(ax5,'XGrid','on');
set(ax5,'YGrid','on');
if ~ishold(ax5)
  [minx5,maxx5] = minmax(fusion_analyzer_data(:,15));
  [miny5,maxy5] = minmax(fusion_analyzer_data(:,4));
  axis(ax5,[minx5 maxx5 miny5 maxy5])
end
hc5 =  line('parent',ax5, 'linestyle','-','erase','xor','xdata',fusion_analyzer_data(1,15),'ydata',fusion_analyzer_data(1,4));
ha5 = line('parent',ax5,'linestyle','-','erase','none','xdata',[],'ydata',[]);
ylabel('Map 4 values')
xlabel('Data points')
%-------------
subplot(4,1,3)
% axis control and adjustment
[ax6] = axescheck(fusion_analyzer_data(:,15), fusion_analyzer_data(:,5));
ax6 = newplot(ax6);
set(ax6,'XGrid','on');
set(ax6,'YGrid','on');
if ~ishold(ax6)
  [minx6,maxx6] = minmax(fusion_analyzer_data(:,15));
  [miny6,maxy6] = minmax(fusion_analyzer_data(:,5));
  axis(ax6,[minx6 maxx6 miny6 maxy6])
end
hc6 = line('parent',ax6, 'linestyle','-','erase','xor','xdata',fusion_analyzer_data(1,15),'ydata',fusion_analyzer_data(1,5));
ha6 = line('parent',ax6,'linestyle','-','erase','none','xdata',[],'ydata',[]);
ylabel('Map 5 values')
xlabel('Data points')
%------------
subplot(4,1,4)
% axis control and adjustment
[ax7] = axescheck(fusion_analyzer_data(:,15), fusion_analyzer_data(:,6));
ax7 = newplot(ax7);
set(ax7,'XGrid','on');
set(ax7,'YGrid','on');
if ~ishold(ax7)
  [minx7,maxx7] = minmax(fusion_analyzer_data(:,15));
  [miny7,maxy7] = minmax(fusion_analyzer_data(:,6));
  axis(ax7,[minx7 maxx7 miny7 maxy7])
end
hc7 =  line('parent',ax7, 'linestyle','-','erase','xor','xdata',fusion_analyzer_data(1,15),'ydata',fusion_analyzer_data(1,6));
ha7 = line('parent',ax7,'linestyle','-','erase','none','xdata',[],'ydata',[]);
ylabel('Map 6 values')
xlabel('Data points')
% small pause to start recording with external device
pause(5); % s
% loop and dynamically shouw map convergence
for i=2:length(fusion_analyzer_data(:,15))
    j = i-1:i;
    set(hc4,'xdata', fusion_analyzer_data(i,15), 'ydata', fusion_analyzer_data(i,3));
    set(ha4,'xdata', fusion_analyzer_data(j,15), 'ydata', fusion_analyzer_data(j,3));
    set(hc5,'xdata', fusion_analyzer_data(i,15), 'ydata', fusion_analyzer_data(i,4));
    set(ha5,'xdata', fusion_analyzer_data(j,15), 'ydata', fusion_analyzer_data(j,4));
    set(hc6,'xdata', fusion_analyzer_data(i,15), 'ydata', fusion_analyzer_data(i,5));
    set(ha6,'xdata', fusion_analyzer_data(j,15), 'ydata', fusion_analyzer_data(j,5));
    set(hc7,'xdata', fusion_analyzer_data(i,15), 'ydata', fusion_analyzer_data(i,6));
    set(ha7,'xdata', fusion_analyzer_data(j,15), 'ydata', fusion_analyzer_data(j,6));
    drawnow;
end

