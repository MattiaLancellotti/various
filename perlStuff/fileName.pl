#!/usr/bin/env perl
use strict;
use warnings 'all';

open(my $file, "<", "name.txt") or die("Can't open name.txt: $!");
my $name = <$file>;
printf("Hello mate $name\n");
