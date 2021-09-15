#!/usr/bin/env perl
use strict;
use warnings;

# Asking the name to the user
print "Hello there!\n";
print "Enter your name: ";
chomp (my $name  = <STDIN>);

# Writing the name to a file
open (my $file, ">>", "name.txt") or die("Can't open name.txt $!");
print $file $name."\n";
