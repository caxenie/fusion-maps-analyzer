load fusion-analyzer-data.log
LOOP_TIME = 1; %ms
TO_S = 10000;
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
subplot(2,1,2)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,8))
ylabel('Map 2 error to R1')
xlabel('Time(s)')
grid on

% second relationship between M2, M3 and M4
figure(3);
subplot(3,1,1)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,9))
ylabel('Map 2 error to R2')
xlabel('Time(s)')
grid on
subplot(3,1,2)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,10))
ylabel('Map 3 error to R2')
xlabel('Time(s)')
grid on
subplot(3,1,3)
plot(fusion_analyzer_data(:,15)*LOOP_TIME/TO_S, fusion_analyzer_data(:,11))
ylabel('Map 4 error to R2')
xlabel('Time(s)')
grid on

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