clc;
clf;
close('all');
clear all;
load fusion-analyzer-data.log
LOOP_TIME = 1; %ms
TO_S = 1000000;
figure(1);
subplot(6,1,1)
title('Maps values during simulation')
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,1))
ylabel('Map 1 values')
xlabel('Time(s)')
grid on
%-------------
subplot(6,1,2)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,2))
ylabel('Map 2 values')
xlabel('Time(s)')
grid on
%-------------
subplot(6,1,3)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,3))
ylabel('Map 3 values')
xlabel('Time(s)')
grid on

%-------------
subplot(6,1,4)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,4))
ylabel('Map 4 values')
xlabel('Time(s)')
grid on
%-------------
subplot(6,1,5)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,5))
ylabel('Map 5 values')
xlabel('Time(s)')
grid on
%------------
subplot(6,1,6)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,6))
ylabel('Map 6 values')
xlabel('Time(s)')
grid on
% per relation errors
% first relation between M1 and M2
figure(2);
subplot(2,1,1)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,7))
ylabel('Map 1 error to R1')
xlabel('Time(s)')
grid on
subplot(2,1,2);
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,8));
ylabel('Map 2 error to R1');
xlabel('Time(s)');
grid on

% second relationship between M2, M3 and M4
figure(3);
subplot(3,1,1)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,9))
ylabel('Map 2 error to R2');
xlabel('Time(s)');
grid on;
subplot(3,1,2)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,10))
ylabel('Map 3 error to R2');
xlabel('Time(s)');
grid on;
subplot(3,1,3)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,11))
ylabel('Map 4 error to R2');
xlabel('Time(s)');
grid on;

% third relationship between M4, M5, M6
figure(4);
subplot(3,1,1)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,12))
ylabel('Map 4 error to R3')
xlabel('Time(s)')
grid on
subplot(3,1,2)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,13))
ylabel('Map 5 error to R3')
xlabel('Time(s)')
grid on
subplot(3,1,3)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,14))
ylabel('Map 6 error to R3')
xlabel('Time(s)')
grid on

% analize the first relationship R1: M2 = 3*M1
% analize the (M1, M2) dependency 
figure(5);
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, 3*fusion_analyzer_data(:,1));
hold on;
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,2), '-r');
title('The dependency between M1 and M2');
grid on;
legend('3*M1 data', 'M2 data');
xlabel('Time(s)');


% analize the second relationship R2: M3 = M2*M4
% analize the (M2, M3, M4) dependency 
figure(6);
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,2).*fusion_analyzer_data(:,4));
hold on;
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,3), '-r');
title('The dependency between M2, M3, and M4');
legend('M2*M4 data', 'M3 data');
grid on;
xlabel('Time(s)');


% analize the second relationship R3: M4 = M5 + 2*M6
% analize the (M4, M5, M6) dependency 
figure(7);
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,5)+(2*fusion_analyzer_data(:,6)));
hold on;
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,4), '-r');
title('The dependency between M4, M5, and M6');
legend('M5+2*M6 data', 'M4 data');
grid on;
xlabel('Time(s)');  

% analize map to map dependencies 
% relationship 1: M2 = 3*M1
figure(8);
plot(fusion_analyzer_data(:,1), fusion_analyzer_data(:,2), '-b');
title('M2 dependency on M1');
xlabel('M1 values');
ylabel('M2 values');
grid on;
hold on;
% add the analytical solution to check the error 
global_min = min([min(fusion_analyzer_data(:,1)) , min(fusion_analyzer_data(:,2))]);
global_max = max([max(fusion_analyzer_data(:,1)) , max(fusion_analyzer_data(:,2))]);
t = 0:0.1:global_max;
plot(t, 3*t, '-r');
legend('Simulation data', 'Analytic curve');


