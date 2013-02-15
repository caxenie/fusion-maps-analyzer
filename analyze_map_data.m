clc;
clf;
close('all');
clear all;
load fusion-analyzer-data.log
TO_S = 11.1;
%--------------------------------------------------------------------------------------------------------
figure(1);
subplot(3,1,1)
title('Maps values during simulation')
%plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,1))
grid on
ylabel('Map 1 values')
xlabel('Time(s)')
hold on 
h1 = plot(fusion_analyzer_data(1,15)/TO_S, fusion_analyzer_data(1,1),'g-') ;

subplot(3,1,2)
%plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,2))
ylabel('Map 2 values')
xlabel('Time(s)')
grid on
hold on
h2 = plot(fusion_analyzer_data(1,15)/TO_S, fusion_analyzer_data(1,2),'r-') ;

subplot(3,1,3)
t = -1:1;
plot(t, 3*t, '-m');
hold on;
h3 = plot(fusion_analyzer_data(1,1),fusion_analyzer_data(1,2),'b-') ;
grid on;
title('M2 dependency on M1');
xlabel('M1 values');
ylabel('M2 values');
% dynamic plot simulataneously in all subplots
for i=2:length(fusion_analyzer_data(:,1))
  xd1 = get(h1,'xdata') ;
  yd1 = get(h1,'ydata') ;
  xd2= get(h2,'xdata') ;
  yd2 = get(h2,'ydata') ;
  xd3 = get(h3,'xdata') ;
  yd3 = get(h3,'ydata') ;
  set(h1,'xdata',[xd1(:) ; fusion_analyzer_data(i,15)/TO_S],'ydata',[yd1(:) ; fusion_analyzer_data(i,1)]) ;
  set(h2,'xdata',[xd2(:) ; fusion_analyzer_data(i,15)/TO_S],'ydata',[yd2(:) ; fusion_analyzer_data(i,2)]) ;
  set(h3,'xdata',[xd3(:) ; fusion_analyzer_data(i,1)],'ydata',[yd3(:) ; fusion_analyzer_data(i,2)]) ;
  drawnow;
  %pause(0.06);
end

%--------------------------------------------------------------------------------------------------------
figure(2);
subplot(4,1,1)
title('Maps values during simulation');
hold on;
h4 = plot(fusion_analyzer_data(1,15)/TO_S, fusion_analyzer_data(1,3));
ylabel('Map 3 values')
xlabel('Time(s)')
grid on

%-------------
subplot(4,1,2)
hold on;
h5 = plot(fusion_analyzer_data(1,15)/TO_S, fusion_analyzer_data(1,4));
ylabel('Map 4 values')
xlabel('Time(s)')
grid on
%-------------
subplot(4,1,3)
hold on
h6 = plot(fusion_analyzer_data(1,15)/TO_S, fusion_analyzer_data(1,5));
ylabel('Map 5 values')
xlabel('Time(s)')
grid on
%------------
subplot(4,1,4)
hold on;
h7 = plot(fusion_analyzer_data(1,15)/TO_S, fusion_analyzer_data(1,6));
ylabel('Map 6 values')
xlabel('Time(s)')
grid on

for i=2:length(fusion_analyzer_data(:,1))
  xd4 = get(h4,'xdata') ;
  yd4 = get(h4,'ydata') ;
  xd5= get(h5,'xdata') ;
  yd5 = get(h5,'ydata') ;
  xd6 = get(h6,'xdata') ;
  yd6 = get(h6,'ydata') ;
  xd7 = get(h7,'xdata') ;
  yd7 = get(h7,'ydata') ;
  set(h4,'xdata',[xd4(:) ; fusion_analyzer_data(i,15)/TO_S],'ydata',[yd4(:) ; fusion_analyzer_data(i,3)]) ;
  set(h5,'xdata',[xd5(:) ; fusion_analyzer_data(i,15)/TO_S],'ydata',[yd5(:) ; fusion_analyzer_data(i,4)]) ;
  set(h6,'xdata',[xd6(:) ; fusion_analyzer_data(i,15)/TO_S],'ydata',[yd6(:) ; fusion_analyzer_data(i,5)]) ;
  set(h7,'xdata',[xd7(:) ; fusion_analyzer_data(i,15)/TO_S],'ydata',[yd7(:) ; fusion_analyzer_data(i,6)]) ;
  drawnow;
  pause(0.06);
end

%--------------------------------------------------------------------------------------------------------
% per relation errors
% first relation between M1 and M2
figure(3);
subplot(2,1,1)
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,7))
ylabel('Map 1 error to R1')
xlabel('Time(s)')
grid on
subplot(2,1,2);
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,8));
ylabel('Map 2 error to R1');
xlabel('Time(s)');
grid on
%--------------------------------------------------------------------------------------------------------
% second relationship between M2, M3 and M4
figure(4);
subplot(3,1,1)
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,9))
ylabel('Map 2 error to R2');
xlabel('Time(s)');
grid on;
subplot(3,1,2)
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,10))
ylabel('Map 3 error to R2');
xlabel('Time(s)');
grid on;
subplot(3,1,3)
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,11))
ylabel('Map 4 error to R2');
xlabel('Time(s)');
grid on;
%--------------------------------------------------------------------------------------------------------
% third relationship between M4, M5, M6
figure(5);
subplot(3,1,1)
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,12))
ylabel('Map 4 error to R3')
xlabel('Time(s)')
grid on
subplot(3,1,2)
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,13))
ylabel('Map 5 error to R3')
xlabel('Time(s)')
grid on
subplot(3,1,3)
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,14))
ylabel('Map 6 error to R3')
xlabel('Time(s)')
grid on
%--------------------------------------------------------------------------------------------------------
% analize the first relationship R1: M2 = 3*M1
% analize the (M1, M2) dependency 
figure(6);
plot(fusion_analyzer_data(:,15)/TO_S, 3*fusion_analyzer_data(:,1));
hold on;
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,2), '-r');
title('The dependency between M1 and M2');
grid on;
legend('3*M1 data', 'M2 data');
xlabel('Time(s)');

%--------------------------------------------------------------------------------------------------------
% analize the second relationship R2: M3 = M2*M4
% analize the (M2, M3, M4) dependency 
figure(7);
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,2).*fusion_analyzer_data(:,4));
hold on;
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,3), '-r');
title('The dependency between M2, M3, and M4');
legend('M2*M4 data', 'M3 data');
grid on;
xlabel('Time(s)');

%--------------------------------------------------------------------------------------------------------
% analize the second relationship R3: M4 = M5 + 2*M6
% analize the (M4, M5, M6) dependency 
figure(8);
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,5)+(2*fusion_analyzer_data(:,6)));
hold on;
plot(fusion_analyzer_data(:,15)/TO_S, fusion_analyzer_data(:,4), '-r');
title('The dependency between M4, M5, and M6');
legend('M5+2*M6 data', 'M4 data');
grid on;
xlabel('Time(s)');  




