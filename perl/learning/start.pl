#!/usr/bin/env perl

# modules
use strict; 
use warnings;

sub main() {
    
    print("\nProgram is starting\n");

    my @files = ('/Users/mlacroix/Documents/demo.mov',
                '/Users/mlacroix/Documents/console.log',
                'Nothing.nothing'
                );

    foreach my $file(@files){
        if(-f $file){
            print("Found file: $file\n");
        }else{
            print("File not found: $file\n");
        }
    }

}

main();