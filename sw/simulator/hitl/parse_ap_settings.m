clear all
%%
close all
clc;
%%
rc_mode = bitand(bitshift(ap_settings,-2), 3);


ap_mode = bitand(bitshift(ap_settings,-4),3);

lateral_mode = bitand(bitshift(ap_settings,-6),3);

%% PITCH
figure
ax(1) = subplot(3,1,1);
plot(ap_time, COMMAND_PITCH);
grid on
legend('COMMAND PITCH')

ax(2) = subplot(3,1,2);
plot(ap_time, ap_mode);
grid on
legend('AP MODE')

ax(3) = subplot(3,1,3);
plot(ap_time, Pitch*57.2);
grid on
legend('Pitch')

linkaxes(ax,'x');

%% ROLL
figure
ax(1) = subplot(3,1,1);
plot(ap_time, COMMAND_ROLL,'b-o');
grid on
legend('COMMAND ROLL')

ax(2) = subplot(3,1,2);
plot(ap_time, ap_mode);
grid on
legend('AP MODE')

ax(3) = subplot(3,1,3);
plot(ap_time, Yaw*57.2,'b-o');
grid on
legend('Roll')

linkaxes(ax,'x');

%%
close all
figure
hold on;
grid on;
plot(ap_time(636:end)-ap_time(1),'b-');
plot(timeStartup(636:end)+20,'r-')
plot(timeLogger(636:end),'c-')
ylabel('[s]')
legend('ap_time','timeStartup','timeLogger')
%%
figure;
plot(timeStartup(636:end)-timeLogger(636:end)+20)
x_time = timeStartup(636:end)-timeLogger(636:end)+20;
mean(x_time)
%%
figure;
x_time = (timeStartup(636:end)+20)-(ap_time(636:end)-ap_time(1));
plot(x_time)

%%
figure;
plot(ap_time, 'b-o');
grid on; hold on;
plot(timeLogger, 'r-o');
plot(timeStartup, 'c-o');
legend('ap time','logger','startup')