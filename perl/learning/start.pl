#!/usr/bin/env perl

# modules
use strict; 
use warnings;

sub loop() {
# Loop example
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

sub readStuff(){
# Reading stuff from a file and insert it into another
    my $textFile = 'aText.txt';
    my $newFile = 'outputText.txt';
    open(INPUT,'<',$textFile);
    open(OUTPUT,'>',$newFile);
    while(my $line = <INPUT>){
        if($line =~ /^I/){ # REGEXP example
            print(OUTPUT "$line\n");
        }
    }
    close(INPUT);
    close(OUTPUT);

    die "Input file $textFile killed\n";
}

sub main(){
    readStuff();
}

main();