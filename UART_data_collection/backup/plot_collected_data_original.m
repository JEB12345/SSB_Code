% This script opens data collected from the SUPERball sensorboard over
% UART, as a binary file, and parses and plots that data.
% @author Roya Firoozi, Drew Sabelhaus

clear all; clc;
figure;

% The path of the log file to open
fileID = fopen('logs/cutecom.log');
% Import everything
data_mat = fread(fileID);

% A 16-bit (byte?) vector of data
data_vec = zeros(1,16);

% Find the starting point in the data: ignore any partial bytes or partial
% packets we received at the beginning of the file.
% For the first 30 bytes...
for i= 1:30
    % We look for the end of one packet. Those bytes are 0x02, 0x8b (139),
    % then two bytes of zeros.
    if (data_mat(i) == 2 && data_mat(i+1) == 139 &&...
        data_mat(i+2) == 0 && data_mat(i+3) == 0)
            % The start of the next packet is 5 bytes after the 0x02.
            mat_idx = i+5;
            % As soon as we find the end of the first packet, stop looking
            break;
    end
end

% A cell array to store our samples, once they've been parsed.
data_cell = cell(1,floor(length(data_mat)/16));

% Parse the data from data_mat into data_cell
% For every whole packet (16 bytes), we have one data sample, so divide
% length by 16.
for k = 1:floor(length(data_mat)/16)
    % Starting at the first intact packet we found, store those values into
    % a vector
    for j = mat_idx:(mat_idx+15)  
        data_vec(j-mat_idx+1) = data_mat(j);
    end
    % Move that vector into our cell array
    data_cell{1,k} = data_vec';
    % Increment the packet index
    mat_idx = mat_idx + 16;
    
    % It's very possible that we received an incomplete packet at the end,
    % so we want to ignore that one also.
    if (mat_idx >= length(data_mat)-16)
       break;
    end
end

% Generate the vector of data values for the first sensor, from data_cell.
state_one_data = zeros(1,floor(length(data_mat)/16));
for m = 1:floor(length(data_mat)/16)-2
state_one_data(m) = bitshift(data_cell{m}(4),16)+...
    bitshift(data_cell{m}(5),8)+data_cell{m}(6);

end

% Plot the first sensor's values.
plot(state_one_data)
xlabel('Index of Data Packet')
ylabel('Strain Gauge Data (State 1)')
axis([0,floor(length(data_mat)/16),0,2^24-1])

% Generate the vector of data values from the second sensor.
state_two_data = zeros(1,floor(length(data_mat)/16));
for n = 1:floor(length(data_mat)/16)-2
state_two_data(n) = bitshift(data_cell{n}(9),16)+...
    bitshift(data_cell{n}(10),8)+data_cell{n}(11);
end

% Plot the second sensor's values.
%{
figure
plot(state_two_data)
xlabel('Index of Data Packet')
ylabel('Strain Gauge Data (State 2)')
axis([0,floor(length(data_mat)/16),0,2^24-1])
%}

% Always remember to close() anything you open()!
fclose(fileID);
