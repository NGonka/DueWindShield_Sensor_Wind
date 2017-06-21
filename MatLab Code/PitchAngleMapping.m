function step = PitchAngleMapping(gamma)

% function step = PitchAngleMapping(gamma) delivers the absolute step number corresponding
% to the desired pitch angle gamma, where step = 0 corresponds to the shaft front position
% xS is the position of the shaft, where:
% xS = 0mm <=> minimum pitch angle <=> gamma = -10° <=> shaft in the front position
% xS = 20mm <=> maximum pitch angle <=> gamma = 50° <=> shaft 20mm to the rear
% (xS = 30mm is the service position for mounting of rotor blades)

if gamma < -10 || gamma > 50
    error('pitch angle out of range')
end

%% Definitions geometry
R = 3; % [mm] radius of bolt center in blade root
r = 1; % [mm] radius of bolt
beta = 8.53076561; % [deg] angle of channel in shaft
alfa = 20 - gamma; % [deg] conversion of pitch angle to angle between x axis and bolt center / blade center
alfa0 = 30; % [deg] starting value of alfa corresponding to xS = 0

%% Definitions linear actuator
leadPerFullStep = 0.0025; % [mm/1.8°] Spindel AA Adrive CanStack NEMA8
stepMode = 1; % 1/2 = half step, 1/4 = quater step, ...
lead = leadPerFullStep*stepMode; % [mm/step]

%% Calculation
xS = R*(sind(alfa0)-sind(alfa))/tand(beta);
step = round(xS/lead);
