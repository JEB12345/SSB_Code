% This script opens data collected from the SUPERball sensorboard over
% UART, as a binary file, and parses and plots that data.
% @author Roya Firoozi, Drew Sabelhaus

clc; clear all;
figure;

% The path of the log file to open
%fileID = fopen('logs/cutecom_offset_MultiBend.log');
%fileID = fopen('logs/cutecom_weird1.log');
fileID = fopen('UART_Capture/Motor_Mount_Strain_Gauge_Tests/sensor12_noload.log');

% Import everything
data_mat = fread(fileID);

% A 16-byte vector of data
data_vec = zeros(1,16);

% We look for the end of one packet. Those bytes are 0x02, 0x8b (139),
% then two bytes of zeros.
% End-of-packet bytes:
end_of_packet = [2; 139; 0; 0];
%beginning_of_packet = [255; 255; 14];

% For debugging: to detect dramatic changes in packet values
prev_packet_value = 0;
current_packet_value = 0;
packet_delta_max = 1000000;

% Find the starting point in the data: ignore any partial bytes or partial
% packets we received at the beginning of the file.
% For the first 30 bytes...
for i= 1:30
    if ( isequal(data_mat(i:(i+3)), end_of_packet) )
        % The start of the next packet is 5 bytes after the 0x02.
        mat_idx = i+5;
        % As soon as we find the end of the first packet, stop looking
        break;
    end
end

% A cell array to store our samples, once they've been parsed.
% NOTE that this is how many packets we'd expect to have, if everything is
% transmitted properly. Its size is adjusted below if we throw out packets.
data_cell = cell(1,floor(length(data_mat)/16));

% Initialization: set prev_packet_value to the first packet.
for j = mat_idx:(mat_idx+15)  
    data_vec(j-mat_idx+1) = data_mat(j);
end
prev_packet_value = bitshift(data_vec(4),16)+...
        bitshift(data_vec(5),8)+data_vec(6);

% Parse the data from data_mat into data_cell
% For every whole packet (16 bytes), we have one data sample, so divide
% length by 16.
for k = 1:floor(length(data_mat)/16)
    % First, check for proper number of bytes in this packet. Right now, just do this by
    % checking where the end of the packet is expected to be, same as
    % above.
    if( ~isequal(data_mat((mat_idx+11):(mat_idx+14)), end_of_packet))
        %'broken packet found at index'
        %mat_idx
        % Throw out this packet. We can afford to lose some data, we've got
        % redundancy.
        % Search for a new starting point
        mat_idx = mat_idx + 16;
        for i=mat_idx:mat_idx+30
            if( isequal(data_mat(i:(i+3)), end_of_packet) )
                mat_idx = i+5;
                break;
            end
        end
        'fixed a broken packet - misaligned'
    end
    
    % Starting at the first intact packet we found, store those values into
    % a vector
    for j = mat_idx:(mat_idx+15)  
        data_vec(j-mat_idx+1) = data_mat(j);
    end
    % Move that vector into our cell array
    data_cell{1,k} = data_vec';
    
    % Calculate the value of the first sensor output of this packet
    current_packet_value = bitshift(data_cell{k}(4),16)+...
        bitshift(data_cell{k}(5),8)+data_cell{k}(6);
    % If there is a large jump: output the packet number and mat_idx
    if ( abs(current_packet_value - prev_packet_value) > packet_delta_max)
        'Large difference found at mat_idx:'
        mat_idx
        'Prev was:'
        prev_packet_value
        'Current is:'
        current_packet_value
    end
    
    % Update packet value for next iteration
    prev_packet_value = current_packet_value;
    
    % Increment the packet index
    mat_idx = mat_idx + 16;
    
    % It's very possible that we received an incomplete packet at the end,
    % so we want to ignore that one also.
    if (mat_idx >= length(data_mat)-16)
       break;
    end
end

% Now, if we've removed packets, automatically shrink the size of
% data_cell to the new packet number.
% First, find our new end point:
found_endpoint = 0;
endpoint = length(data_cell);

while( ~found_endpoint)
    % Check if this is really the new endpoint
    if( ~isempty(data_cell{endpoint}) )
        % We've found our end! This is the first cell entry, counting
        % backwards from the end of the cell array, that has values in it.
        found_endpoint = 1;
    else
        % Still empty. Increment:
        endpoint = endpoint - 1;
    end
end

% Then, readjust the size of data_cell:
data_cell = data_cell(1:endpoint);
num_data_points = length(data_cell);

% Generate the vector of data values for the first sensor, from data_cell.
%state_one_data = zeros(1,floor(length(data_mat)/16));
state_one_data = zeros(1,num_data_points);
for m = 1:num_data_points
    state_one_data(m) = bitshift(data_cell{m}(4),16)+...
        bitshift(data_cell{m}(5),8)+data_cell{m}(6);
end

% Plot the first sensor's values.
plot(state_one_data)
xlabel('Index of Data Packet')
ylabel('Strain Gauge Data (State 1)')
axis([0,floor(length(data_mat)/16),0,2^24-1])

% Generate the vector of data values from the second sensor.
state_two_data = zeros(1,num_data_points);
for n = 1:length(data_cell)
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
