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

% analize the first relationship R1: M2 = 3*M1
% analize the (M1, M2) dependency to check
figure(5);
plot(fusion_analyzer_data(:,1), fusion_analyzer_data(:,2));
legend('Net data relationship', 'Analytic relationship');
title('The dependency between M1 and M2 and the relationship curve');
xlabel('M1');
ylabel('M2');
grid on;
minM1 = min(fusion_analyzer_data(:,1));
minM2 = min(fusion_analyzer_data(:,2));
maxM1 = max(fusion_analyzer_data(:,1));
maxM2 = max(fusion_analyzer_data(:,2));
minFct = min(minM1, minM2);
maxFct = max(maxM1, maxM2);
t = minFct:1:maxFct;
hold on;
plot(t, 3*t, '-r');


% analize the second relationship R2: M3 = M2*M4
% analize the (M2, M3, M4) dependency to check
figure(6);
plot3(fusion_analyzer_data(:,2), fusion_analyzer_data(:,4), fusion_analyzer_data(:,3));
legend('Net data relationship', 'Analytic relationship');
title('The dependency between M2, M3, and M4 and the relationship curve');
xlabel('M2');
ylabel('M4');
zlabel('M3');
grid on;
minM2 = min(fusion_analyzer_data(:,2));         
maxM2 = max(fusion_analyzer_data(:,2));
minM3 = min(fusion_analyzer_data(:,3));
maxM3 = max(fusion_analyzer_data(:,3));
minM4 = min(fusion_analyzer_data(:,4));
maxM4 = max(fusion_analyzer_data(:,4));
minFct = min([minM2, minM3, minM4]);
maxFct = max([maxM2, maxM3, maxM4]);
t1 = minFct:1:maxFct;
t2 = minFct:1:maxFct;
hold on;
plot3(t1, t2, (t1.*t2)/maxFct, '-r');



% analize the second relationship R3: M4 = M5 + 2*M6
% analize the (M4, M5, M6) dependency to check
figure(7);
plot3(fusion_analyzer_data(:,5), fusion_analyzer_data(:,6), fusion_analyzer_data(:,4));
legend('Net data relationship', 'Analytic relationship');
title('The dependency between M5, M6, and M4 and the relationship curve');
xlabel('M5');
ylabel('M6');
zlabel('M4');
grid on;
minM5 = min(fusion_analyzer_data(:,5));
maxM5 = max(fusion_analyzer_data(:,5));
minM6 = min(fusion_analyzer_data(:,6));
maxM6 = max(fusion_analyzer_data(:,6));
minM4 = min(fusion_analyzer_data(:,4));
maxM4 = max(fusion_analyzer_data(:,4));
minFct = min([minM5, minM6, minM4]);
maxFct = max([maxM5, maxM6, maxM4]);
t1 = minFct:1:maxFct;
t2 = minFct:1:maxFct;
hold on;
plot3(t1, t2, t1 + 2*t2, '-r');
