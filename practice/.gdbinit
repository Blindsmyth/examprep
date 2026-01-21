# Helper function to print 8-bit binary with leading zeros
define print8bit
  python
val = gdb.parse_and_eval('(unsigned char)(' + $arg0 + ')')
print(format(int(val), '08b'))
  end
end

# Display command that shows 8-bit binary
define display8bit
  display
  python
import gdb
class BinaryDisplay(gdb.Command):
    def __init__(self):
        super(BinaryDisplay, self).__init__("display8bit", gdb.COMMAND_USER)
    
    def invoke(self, arg, from_tty):
        val = gdb.parse_and_eval('(unsigned char)(' + arg + ')')
        print(format(int(val), '08b'))
BinaryDisplay()
  end
end


