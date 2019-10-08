%% convert mat into .csv

sensors_data = load('GNSSaidedINS_data.mat')

% GNSS
GNSS = sensors_data.in_data.GNSS.pos_ned;
t_GNSS = sensors_data.in_data.GNSS.t;

Sensor_GNSS = [t_GNSS,GNSS']

writematrix(Sensor_GNSS,'GNSS_data.csv') 

% Accelerometers
ACC = sensors_data.in_data.IMU.acc;
GYRO = sensors_data.in_data.IMU.gyro;
t_IMU= sensors_data.in_data.IMU.t;

Sensor_ACC = [t_IMU,ACC']
Sensor_GYRO = [t_IMU,GYRO']

writematrix(Sensor_ACC,'ACC_data.csv')

writematrix(Sensor_GYRO,'GYRO_data.csv')




