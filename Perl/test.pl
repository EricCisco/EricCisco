#!/usr/bin/perl
#Eric Cisco

open my $file, "<","UG_Test_File.txt";
<$file>;
my $DNA = <$file>;
close($file);


$RC = $DNA;
chomp $RC;
$RC = reverse $RC;
$RC =~ tr/ACGTacgt/TGCAtgca/;
$RNA = $DNA;
$RNA =~ s/T/U/g;
$A = "GGACTATTTTGGGATT";
$B = "TTAGATTGATTCCTCA";
($ThirdPart) = $DNA =~ /$A(.*)$B/; 
($Before) = $DNA =~ /(.*)$A/;
($After) = $DNA =~ /$B(.*)/;


my $output = 'output.txt';
open(FH, '>',$output);
print FH "Reverse Compliment: $RC\n\n";
print FH "RNA Sequence: $RNA\n";
print FH "Sub-String: $ThirdPart\n\n";
close(FH);

open my $HTML, '>', 'output.html' or die $!;
print $HTML <<'_END_HEADER_';
<html>
<head><title></title></head>
<body>
<pre>
_END_HEADER_
open my $IN, '<', 'output.txt' or die $!;
while(my $line = <$IN>)
{
	print $HTML $line;
}
print $HTML 'DNA Sequence: ';
print $HTML $Before;
print $HTML '<font color="blue">';
print $HTML $A;
print HTML '</font>';
print $HTML '<font color="red">'; 
print $HTML $ThirdPart;
print $HTML '</font>';
print $HTML '<font color="blue">'; 
print $HTML $B;
print $HTML '</font>';
print $HTML '<font color="black">';
print $HTML $After;
print $HTML '</font>';

print $HTML '</pre></body></html>';
close $HTML or die $!;
