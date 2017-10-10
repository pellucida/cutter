## cutter 

Print selected fields from input lines to standard output.

Input lines are broken into fields using the specified
field delimiter (default is <em>tab</em>.)
The fields are numbered 1,2,... and those to be printed are selected 
by a comma separated of field numbers and ranges of field numbers.
The fields can be repeated and ranges can be in both increasing
or decreasing order.
<pre>
	cutter -f <i>LIST</i> 

where <i>LIST</i> is
	n	n<sup>th</sup> field, counted from 1
	n-	n<sup>th</sup> field to end of line
	n-m	from n<sup>th</sup> to m<sup>th</sup> field
	-m	from the last field to the m<sup>th</sup> field (reversed)

	If m &gt; n then the fields are output in reverse order.
</pre>

## Examples
<pre>
	cut -d: -f-1 /etc/passwd	# reverse order
	cut -d: -f1,3,1 /etc/passwd	# field 1 repeated
	cut -d: -f1-,-1 /etc/passwd	# forwards and reversed
</pre>

## AUTHOR
James Sainsbury <toves@sdf.lonestar.org>

## LICENSE
Creative Commons CC0
http://creativecommons.org/publicdomain/zero/1.0/legalcode
