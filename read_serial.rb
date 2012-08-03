require 'serialport'

$sp = SerialPort.new "/dev/tty.usbmodemfd121", 115200

def ws(str)
  print "[#{str}]"
  $sp.write(str)
end

def rs
  retries = 5
  begin
    str = $sp.read_nonblock(1024)
    print "<#{str}>"
  rescue Exception => ex
    unless retries > 0
      sleep 0.01
      retries -= 1
      retry
    end
    p ex
  end
end

sleep 2.0

ctr = 0

loop do
  ws("hello")
  sleep 0.5
  ws("hello")
  sleep 0.5
  ws("hello")
  sleep 0.5
  rs()
  ctr += 1
  print "\n"
end
