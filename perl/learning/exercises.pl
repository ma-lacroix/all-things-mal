# Some exercises and tries from learn-perl.org - nothing spectacular yet.

#!/usr/bin/env perl

use strict;
use warnings;

sub trying_hashes(){
    my @family = ('Jake','Paul','Sandy','Sarah','Mamma','Papa');
    my %shoe_size = ($family[0]=>7,$family[1]=>10,$family[2]=>11,$family[3]=>4,$family[4]=>12,$family[5]=>15);
    my %shoe_color = ($family[0]=>'Brown',$family[1]=>'Black',$family[2]=>'Beige',$family[3]=>'Blue',$family[4]=>'Beens',$family[5]=>'Bully');
    foreach my $member(@family){
        if($shoe_size{$member} >= 10){
            print("$member wears large $shoe_color{$member} of size $shoe_size{$member} \n");
        }else{
            print("$member wears small $shoe_color{$member} of size $shoe_size{$member} \n");
        }
    }
}

sub some_loops(){
    for (my $count = 0; $count < 10; $count ++){
        print("I have $count friends today.\n");
    }
    
    my @NUMBERS = (951,402,984,651,360,69,408,319,601,485,980,507,725,
                547,544,615,83,165,141,501,263,617,865,575,219,390,
                237,412,566,826,248,866,950,626,949,687,217,815,67,
                104,58,512,24,892,894,767,553,81,379,843,831,445,742,
                717,958,609,842,451,688,753,854,685,93,857,440,380,
                126,721,328,753,470,743,527);

    foreach my $num(@NUMBERS){
        last if ($num == 237);
        if($num%2==0){
            print("Number: $num\n");
        }
    }
}

sub calc_average(@) {
    # get total number of arguments passed
    my $total_args = scalar(@_);
    my $sum = 0;
    # sum up all arguments
    foreach my $arg (@_){
       $sum += $arg;
    }
    # calculate print average
    my $average = $sum / $total_args;
    print "Average of list [ @_ ] is: $average\n";
 }

# Exercise
# Create two subroutines min() and max() which accept an array as input and calculate
#  the minimum and maximum numeric value of their arguments respectively.

# Then, for each given array @car_prices and @flight_prices, calculate and print the 
# difference between the maximum and minimum values.

sub min {
# bubble sort to get min array value
    my $min_value = $_[0];

    for (my $i = 1; $i < @_;$i++){
        if($min_value>$_[$i]){
            $min_value = $_[$i];
        }
    }
    return $min_value;
}

sub max {
# bubble sort to get max array value
    # my @max_array = @_;
    my $max_value = $_[0];
    for (my $i = 1; $i < @_;$i++){
        if($max_value<$_[$i]){
            $max_value = $_[$i];
        }
    }
    return $max_value;
}

sub diff {
# diff between min and max of array
    my $dif = $_[1]-$_[0];
    print("The difference between min and max is: $dif\n");
}

sub main(){
    my @car_prices = (100, 250, 95, 1300, 4534, 102, 100, 97);
    my @flight_prices = (85.20, 79.99, 45.30, 130, 45.34, 110.25, 100, 917);
    print("Cars: \n");
    diff(min(@car_prices),max(@car_prices));
    print("Flights: \n");
    diff(min(@flight_prices),max(@flight_prices));
}

main();