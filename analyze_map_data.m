clear all; close all;
load fusion-analyzer-data.log
LOOP_TIME = 1; %ms
TO_S = 1000;
decay_time = 1:39;
figure(1);set(gcf, 'color', 'w'); 
ax(1) = subplot(12,4,[1,5]);
 title('Mapsval during simulation')
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,1), 'LineWidth', 2 )
box off;  disp('M1val' )
xlabel('Time(s)')
grid off;
%-------------
ax(2) = subplot(12,4,[9,13]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,2), 'LineWidth', 2 )
box off;  disp('M2val' )
xlabel('Time(s)')
grid off;
%-------------
ax(3) = subplot(12,4,[17,21]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,3), 'LineWidth', 2 )
box off;  disp('M3val' )
xlabel('Time(s)')
grid off;
%-------------
ax(4) = subplot(12,4,[25,29]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,4), 'LineWidth', 2 )
box off;  disp('M4val' )
xlabel('Time(s)')
grid off;
%-------------
ax(5) = subplot(12,4,[33,37]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,5), 'LineWidth', 2 )
box off;  disp('M5val' )
xlabel('Time(s)')
grid off;
%------------
ax(6) = subplot(12,4,[41,45]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,6), 'LineWidth', 2 )
box off;  disp('M6val' )
xlabel('Time(s)')
grid off;
% per relation errors
% first relation between M1 and M2
ax(7) = subplot(12,4,[3,7]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,7), 'LineWidth', 2 )
box off;  disp('M1errR1' )
xlabel('Time(s)')
grid off;
ax(8) = subplot(12,4,[11,15]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,8), 'LineWidth', 2 )
box off;  disp('M2errR1' )
xlabel('Time(s)')
grid off;

% second relationship between M2, M3 and M4
ax(9) = subplot(12,4,[12,16]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,9), 'LineWidth', 2 )
box off;  disp('M2errR2' )
xlabel('Time(s)')
grid off;
ax(10) = subplot(12,4,[19,23]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,10), 'LineWidth', 2 )
box off;  disp('M3errR2' )
xlabel('Time(s)')
grid off;
ax(11) = subplot(12,4,[27,31]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,11), 'LineWidth', 2 )
box off;  disp('M4errR2' )
xlabel('Time(s)')
grid off;

% third relationship between M4, M5, M6
ax(12) = subplot(12,4,[28,32]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,12), 'LineWidth', 2 )
box off;  disp('M4errR3' )
xlabel('Time(s)')
grid off;
ax(13) = subplot(12,4,[35,39]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,13), 'LineWidth', 2 )
box off;  disp('M5errR3' )
xlabel('Time(s)')
grid off;
ax(14) = subplot(12,4,[43,47]);
plot(fusion_analyzer_data(decay_time,15)*LOOP_TIME/TO_S, fusion_analyzer_data(decay_time,14), 'LineWidth', 2 )
box off;  disp('M6errR3' )
xlabel('Time(s)')
grid off;
