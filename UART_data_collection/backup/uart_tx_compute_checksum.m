function checksum = uart_tx_compute_checksum(packet)
% Compute the checksum of a packet, same as in the sensorboard code.
% author Drew Sabelhaus 8-7-14
% @param packet: 16-byte vector, the packet.
% @return checksum: the calculated checksum.

checksum = uint8(0);
% iterate over each byte of the packet,
% noting that the length of the packet is encoded as the second element in
% the packet itself.
for i=1:packet(2)+1
    
end
    
end