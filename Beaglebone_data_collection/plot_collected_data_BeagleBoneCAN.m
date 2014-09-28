% This script opens data collected from the SUPERball sensorboard over
% the beaglebone black, as sniffed over CAN (then dumped to the BBB and copied to a local computer.)
% @author Drew Sabelhaus
% 9-27-14

clc; close all; clear all;

% The path of the log file to open
data_raw_string = fileread('data_logs/step_inputs_9-27-14_1634.log');

% this regular expression matches 2 hex digits, followed by a space, eight times in a row.
regexp_data_sensor_chunk = '(\w{2}\s){8}';
data_sensor_chunks = regexp(data_raw_string, regexp_data_sensor_chunk, 'match');

% Parse the bytes into their proper location
num_samples = size(data_sensor_chunks,2);
% 4 bytes per sensor sample, 8 bytes per packet. We're only using one sensor right now.
data_filtered = zeros(num_samples, 4);
% a temporary holding space for efficiency
temp_output = cell(1,8);

% this regexp matches two hex digits
regexp_byte = '(\w{2})';

for packet=1:num_samples
    % Run another regexp
    temp_output = regexp(data_sensor_chunks{packet}, regexp_byte, 'match');
    % Sort the bytes into the data_hex array, and convert them in the process
    % NOTE that we're throwing away the last four bytes here, as is desired.
    for byte=1:4
        data_filtered(packet, byte) = hex2dec(temp_output(byte));
        % Note that we don't need to swap the bit ordering within the individual bytes.
    end
end

% Finally, flip the ordering of the bytes, and concatenate them together into a single integer sample.
data_completed = zeros(num_samples,1);
for i=1:num_samples
    % Add the bytes to this (the i-th) sample, in reverse order, since the first is least significant...
    % Note that we ignore the last byte of zeros: they wouldn't add anything anyway.
    data_completed(i) = data_filtered(i,1) + bitshift(data_filtered(i,2),8) + bitshift(data_filtered(i,3),16);
end

% Finally, plot data, with labels.
plot(data_completed);
title('Data collected over BeagleBone, Sensor 1');
xlabel('Sample Number (Index)');
ylabel('Sample Value, Bits (voltage)');
