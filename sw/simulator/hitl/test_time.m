clc;
close all
figure;
grid on;
hold on;
plot(ap_time-ap_time(1),'b-o')
plot(timeLogger, 'r-o')
plot(timeStartup, 'c-o')
legend('ap time','log time', 'vn time')