#!/usr/bin/perl -w

use strict;

my $line = <>;
chomp($line);

my @ws = split(/,/, $line);
my @os = ();
foreach my $ws (@ws) {
	unshift(@os, $ws);
}

print join(",", @os), ",\n";
