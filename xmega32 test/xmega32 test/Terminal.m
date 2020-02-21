%warning('warning', 'MATLAB:serial:fread:unsuccessfulRead');
port = serial('COM1', 'BaudRate', 9600, 'DataBits', 8, 'StopBits', 1, 'Parity', 'None', 'timeout', 4);
fopen(port);
disp('open');
i = 0;
flag = 0;
lastwarn('');
buff = 11;
strformat = 'a %d b %d c %d';
a = [];
while(~flag)
    if (port.bytesAvailable >= (buff - 1))
        a = fscanf(port, '%c', buff);
        disp(a);
    end
    if (strcmp(lastwarn,'Unsuccessful read: A timeout occurred before the Terminator was reached or SIZE values were available..'))
        break
    end
    if (~isempty(a))
        sscanf(a, strformat)
        a = [];
    end
end
fclose(port);
disp('closed');