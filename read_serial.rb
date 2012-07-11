
require 'serialport'

sp = SerialPort.new "/dev/tty.usbmodemfd1231", 115200

sleep 2.0

ctr = 0

loop do
  sp.write ctr.to_s[-1]
  sleep 0.5
  print sp.getc
  ctr += 1
end
