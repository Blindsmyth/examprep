# GDB helper script for displaying 8-bit binary with leading zeros
# Load with: source gdb_helpers.gdb
# Then use: display8b mask
#           display8b octet

define display8b
  set $display8b_expr = $arg0
  display
  python
import gdb

class Binary8Display:
    def __init__(self, expr):
        self.expr = expr
        self.num = len(gdb.display_list())
    
    def __call__(self):
        try:
            val = gdb.parse_and_eval('(unsigned char)(' + self.expr + ')')
            print('{:%d}: %s = %08b' % (self.num, self.expr, int(val)))
        except:
            pass

# Store display object
if not hasattr(gdb, '_binary8_displays'):
    gdb._binary8_displays = []

disp = Binary8Display('$display8b_expr')
gdb._binary8_displays.append(disp)

# Hook into stop events
def on_stop(event):
    for disp in getattr(gdb, '_binary8_displays', []):
        disp()

if not hasattr(gdb, '_binary8_hook_set'):
    gdb.events.stop.connect(on_stop)
    gdb._binary8_hook_set = True
  end
end

document display8b
Display an 8-bit binary value with leading zeros.
Usage: display8b VARIABLE
Example: display8b mask
end

