#!/usr/bin/env perl

use strict;
use warnings;

# An array @family holds a list of family member names. The first hash %shoe_color 
# contains favorite shoe color per person name. The second hash %shoe_size contains shoe size per person name.

# Evaluate and print the favorite shoe color and shoe size per each family member. 
# For shoe sizes 10 and above, add the word 'large' to the output line.

# Output lines should be in the format: "Homer wears large brown shoes size 12".

my @family = ('Jake','Paul','Sandy','Sarah','Mamma','Papa');
my %shoe_size = ($family[0]=>7,$family[1]=>10,$family[2]=>11,$family[3]=>4,$family[4]=>12,$family[5]=>15);
my %shoe_color = ($family[0]=>'Brown',$family[1]=>'Black',$family[2]=>'Beige',$family[3]=>'Blue',$family[4]=>'Beens',$family[5]=>'Bully');

sub main(){
    foreach my $member(@family){
        if($shoe_size{$member} >= 10){
            print("$member wears large $shoe_color{$member} of size $shoe_size{$member} \n");
        }else{
            print("$member wears small $shoe_color{$member} of size $shoe_size{$member} \n");
        }
    }
}

main();