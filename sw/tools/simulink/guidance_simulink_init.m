%
% Settings for the simulink guidance control loops
%

%% Time
PERIODIC_FREQUENCY = 1; % [Hz]
PORT_DIMENSIONS = 2; % x and y position

%% Limits
MAX_POS_ERR = 16*bitshift(1,8);
MAX_SPEED_ERR = 16*bitshift(1,19);

traj_max_bank = deg2rad(20)*bitshift(1,12); % 20deg is default max
total_max_bank = deg2rad(45)*bitshift(1,12); % 45 is total max
max_integrator_trim = traj_max_bank*bitshift(1,16); % integrator limits

%% Gains
PGAIN = 50;
DGAIN = 80;
IGAIN = 20;
AGAIN = 70;
VGAIN = 0;