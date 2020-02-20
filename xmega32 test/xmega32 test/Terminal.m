%warning('warning', 'MATLAB:serial:fread:unsuccessfulRead');
port = serial('COM7', 'BaudRate', 9600, 'DataBits', 8, 'StopBits', 1, 'Parity', 'None', 'timeout', 4);
fopen(port);
disp('open');
i = 0;
flag = 0;
lastwarn('');
while(~flag)
    
    a = fread(port, 1, 'int16');
%     fprintf(port, 'i');
    disp(a);
    i = i + 1;
%     pause(1);
    if (strcmp(lastwarn,'Unsuccessful read: The specified amount of data was not returned within the Timeout period..'))
        break
    end
end

fclose(port);
disp('closed');