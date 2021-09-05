#!/usr/bin/env perl
use strict;
use warnings;

# Asking the name to the user
print("Hello there! Please enter your name: ");
chomp(my $name = <stdin>);
printf("Hello mate $name, I'm writing this down.\n");

# Writing the name to a file
open(my $file, ">", "name.txt") or die("Can't open name.txt $!");
print $file $name;

