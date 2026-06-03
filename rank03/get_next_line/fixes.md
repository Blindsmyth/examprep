

what we need
stash, buffer, line, newline

bytes_read, line_len, res_len

while(!newline)

read into buffer
handle:
if failed read, free stash + return
null terminate
EOF -> break loop
append buffer to stash
look for newline

stash empty? 
-> free and return

if(newline)
malloc with line_len
check if malloc succeeded
extract line into stash with memcpy
nullterminate
update buffer with rest / rest_len
free stash and return line
	/* EOF with no \n: return the last "line" (stash), clear buffer for next call */



