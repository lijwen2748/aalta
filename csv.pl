#!/usr/bin/perl

use File::Find;
use Class::CSV;

$timeout = 60;# seconds

sub create_csv 
{  
	
	$dir = $_[0];
	$csv = Class::CSV->new(
				#fields => [qw/Type Solve Total Result/]
  				fields => [qw/Type Encode Solve Total Result/]
      		);
    my @content;
	find(\&wanted, "$dir");
	
	foreach(@content)
	{
   		if(-f $_)
   		{
   			if ($_ =~ /data.csv/)
   			{
   				next;
   			}
   	  		my $formulaType = substr ($_, index ($_, "/") + 1, rindex ($_, ".") - length ($_)); #.alaska-ltlfic3 (-14) .alaska-aalta (-13)
   	  		
      		open(FD,"$_")||die("Can not open the file $_!\n");
      		$line=<FD>;
      		chomp $line;
      		if($line == "")
      		{
   		  		if($line =~ /^0/)
   		  		{
  			  		my @data = split("\t\t", $line);
  			  		#$csv->add_line ([$formulaType, $data[0], $data[1]]);
   			  		$csv->add_line ([$formulaType, $data[0], $data[1], $data[0]+$data[1], $data[2]]);
   		  		}
   		  		else
   		  		{
   			  		my @data = split("\t\t", "unknow		unknow		unknow");
   			  		#$csv->add_line ([$formulaType, "unknow", "unknow"]);
   			  		$csv->add_line ([$formulaType, "unknow", "unknow", $timeout, "unknow"]);
   		  		}
 	  		}
 	  		else
 	  		{
 	  			my @data = split("\t\t", $line);
 	  			if ($data[0] =~ /unknow/ || $data[1] =~ /unknow/)
 	  			{
 	  				$csv->add_line ([$formulaType, $data[0], $data[1], $timeout, $data[2]]);
 	  				#$csv->add_line ([$formulaType, $data[0], $data[1]]);
 	  			}
 	  			else
 	  			{
 	  				$csv->add_line ([$formulaType, $data[0], $data[1], $data[0]+$data[1], $data[2]]);
 	  				#$csv->add_line ([$formulaType, $data[0], $data[1]]);
 	  			}
 	  		}
   		}
	}
	open(OUT, ">$dir/data.csv") or die "cannot open the file $dir/data.csv!";
	print (OUT $csv->string());
	close (OUT);
sub wanted
{
  push @content, $File::Find::name;
  return;
}
}

sub main 
{
	my $dir = $_[0];
	create_csv ($dir);
}


$work_directory = $ARGV[0];
main ("$work_directory");
exit;



