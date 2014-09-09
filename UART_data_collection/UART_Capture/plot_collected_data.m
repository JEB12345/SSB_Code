

fileID = fopen('cutecom.log');
data_mat = fread(fileID);
data_vec = zeros(1,16);
for i= 1:30
    if (data_mat(i) == 2 && data_mat(i+1) == 139 &&...
        data_mat(i+2) == 0 && data_mat(i+3) == 0)
    mat_idx = i+5;
    break;
    end
end

data_cell = cell(1,floor(length(data_mat)/16));


for k = 1:floor(length(data_mat)/16)
    for j = mat_idx:(mat_idx+15)  
        data_vec(j-mat_idx+1) = data_mat(j);
    end
    data_cell{1,k} = data_vec';
    mat_idx = mat_idx + 16;
    
    if (mat_idx >= length(data_mat)-16)
       break;
    end
end

m=1;state_one_data = zeros(1,floor(length(data_mat)/16));
for m = 1:floor(length(data_mat)/16)-2
state_one_data(m) = bitshift(data_cell{m}(4),16)+...
    bitshift(data_cell{m}(5),8)+data_cell{m}(6);

end

figure(1)
plot(state_one_data)
xlabel('Index of Data Packet')
ylabel('Strain Gauge Data (State 1)')
axis([0,floor(length(data_mat)/16),0,2^24-1])

n=1;state_two_data = zeros(1,floor(length(data_mat)/16));
for n = 1:floor(length(data_mat)/16)-2
state_two_data(n) = bitshift(data_cell{n}(9),16)+...
    bitshift(data_cell{n}(10),8)+data_cell{n}(11);
end


% %figure(2)
% hold
% plot(state_two_data)
% xlabel('Index of Data Packet')
% ylabel('Strain Gauge Data (State 2)')
% %axis([0,floor(length(data_mat)/16),0,2^24-1])

fclose(fileID);
